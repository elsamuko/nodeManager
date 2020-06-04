#include "graphics/graphicsscene.hpp"

#include <QJsonObject>
#include <QJsonArray>
#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>

#include "graphics/node.hpp"
#include "graphics/connection.hpp"

GraphicsScene::GraphicsScene( QObject* parent ) : QGraphicsScene( parent ) {}

GraphicsScene::~GraphicsScene() {
    clearNodes();
}

QList<Connection*> GraphicsScene::connectionsForNode( const Node* node ) const {
    QList<Connection*> filtered;

    for( Connection* connection : connections ) {
        if( connection->connectedTo( node ) ) {
            filtered.push_back( connection );
        }
    }

    return filtered;
}

void GraphicsScene::clearNodes() {
    for( Node* node : nodes ) {

        // delete connections for this node first
        clearConnections( connectionsForNode( node ) );

        removeItem( node );
        delete node;
    }

    nodes.clear();
}

void GraphicsScene::clearConnections( const QList<Connection*>& cons ) {
    for( Connection* connection : cons ) {
        removeItem( connection );
        connections.removeOne( connection );
        delete connection;
    }

}

void GraphicsScene::addNode( Node* node ) {
    if( !node ) {
        node = new Node( nodes.size() );
        size_t offset = nodes.size() * 10;
        node->setPos( width() / 2 + offset, height() / 2 + offset );
    }

    LOG( "Adding node " << node->getId() );
    addItem( node );
    nodes.push_back( node );
}

void GraphicsScene::addConnection( Connection* connection ) {
    LOG( "Adding connection " << connection->getId() );
    addItem( connection );
    connections.push_back( connection );
}

QJsonObject GraphicsScene::toJson() const {
    QJsonObject all;
    QJsonArray jsonNodes;
    QJsonArray jsonConnections;

    for( Node* node : nodes ) {
        QJsonObject one;
        one["id"] = node->getId();
        one["x"] = node->x();
        one["y"] = node->y();
        jsonNodes.append( one );
    }

    all["nodes"] = jsonNodes;

    for( Connection* connection : connections ) {
        QJsonObject one;
        one["id"] = connection->getId();
        one["start"] = connection->getIdStart();
        one["end"] = connection->getIdEnd();
        jsonConnections.append( one );
    }

    all["connections"] = jsonConnections;
    return all;
}

void GraphicsScene::fromJson( const QJsonObject& all ) {

#define CONTINUE_ON( B ) if( ( B ) ) { continue; }

    if( all.contains( "nodes" ) && all["nodes"].isArray() ) {
        clearNodes();
        QJsonArray jsonNodes = all["nodes"].toArray();

        for( QJsonValueRef ref : jsonNodes ) {
            QJsonObject obj = ref.toObject();

            CONTINUE_ON( !obj.contains( "id" ) )
            CONTINUE_ON( !obj.contains( "x" ) )
            CONTINUE_ON( !obj.contains( "y" ) )

            int id = obj["id"].toInt( -1 );
            int x = obj["x"].toInt( -1 );
            int y = obj["y"].toInt( -1 );

            CONTINUE_ON( id == -1 )
            CONTINUE_ON( id >= jsonNodes.size() )
            CONTINUE_ON( x == -1 )
            CONTINUE_ON( y == -1 )

            Node* node = new Node( id );
            node->setPos( x, y );
            addNode( node );
        }
    }

    std::sort( nodes.begin(), nodes.end(), []( const Node * left, const Node * right ) {
        return left->getId() < right->getId();
    } );

    if( all.contains( "connections" ) && all["connections"].isArray() ) {
        QJsonArray jsonConnections = all["connections"].toArray();

        for( QJsonValueRef ref : jsonConnections ) {
            QJsonObject obj = ref.toObject();

            CONTINUE_ON( !obj.contains( "id" ) )
            CONTINUE_ON( !obj.contains( "start" ) )
            CONTINUE_ON( !obj.contains( "end" ) )

            int id = obj["id"].toInt( -1 );
            int start = obj["start"].toInt( -1 );
            int end = obj["end"].toInt( -1 );

            CONTINUE_ON( id == -1 )
            CONTINUE_ON( id >= jsonConnections.size() )
            CONTINUE_ON( start < 0 )
            CONTINUE_ON( start >= nodes.size() )
            CONTINUE_ON( end < 0 )
            CONTINUE_ON( end >= nodes.size() )
            CONTINUE_ON( start == end )
            CONTINUE_ON( nodes[start]->getId() != start )
            CONTINUE_ON( nodes[end]->getId() != end )

            Connection* node = new Connection( id, nodes[start], nodes[end] );
            addConnection( node );
        }
    }

    std::sort( connections.begin(), connections.end(), []( const Connection * left, const Connection * right ) {
        return left->getId() < right->getId();
    } );

#undef CONTINUE_ON
}

void GraphicsScene::mousePressEvent( QGraphicsSceneMouseEvent* mouseEvent ) {
    if( mode == Mode::Connect ) {
        line = new QGraphicsLineItem( QLineF( mouseEvent->scenePos(),
                                              mouseEvent->scenePos() ) );
        addItem( line );
    } else {
        QGraphicsScene::mousePressEvent( mouseEvent );
    }
}

void GraphicsScene::mouseMoveEvent( QGraphicsSceneMouseEvent* mouseEvent ) {
    if( line && mode == Mode::Connect ) {
        QLineF newLine( line->line().p1(), mouseEvent->scenePos() );
        line->setLine( newLine );
    } else {
        QGraphicsScene::mouseMoveEvent( mouseEvent );
    }
}

void GraphicsScene::mouseReleaseEvent( QGraphicsSceneMouseEvent* mouseEvent ) {

    if( line && mode == Mode::Connect ) {

        QList<Node*> startNodes = nodesAt( line->line().p1() );
        QList<Node*> endNodes = nodesAt( line->line().p2() );

        removeItem( line );
        delete line;

        if( !startNodes.empty() && !endNodes.empty() && startNodes.first() != endNodes.first() ) {
            Connection* connection = new Connection( connections.size(), startNodes.first(), endNodes.first() );
            addConnection( connection );
        }

    } else {
        QGraphicsScene::mouseMoveEvent( mouseEvent );
        QGraphicsScene::mouseReleaseEvent( mouseEvent );
    }
}

QList<Node*> GraphicsScene::nodesAt( const QPointF& pos ) const {

    QList<Node*> filtered;
    QList<QGraphicsItem*> underPos = items( pos );

    for( QGraphicsItem* item : underPos ) {
        if( item->type() == static_cast<int>( CustomGraphicsTypes::NodeType ) ) {
            filtered.push_back( static_cast<Node*>( item ) );
        }
    }

    return filtered;
}
