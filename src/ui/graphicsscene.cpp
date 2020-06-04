#include "ui/graphicsscene.hpp"

#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>

#include "ui/graphicsrectitem.hpp"
#include "ui/graphicslineitem.hpp"

GraphicsScene::GraphicsScene( QObject* parent ) : QGraphicsScene( parent ) {}

void GraphicsScene::addNode() {
    GraphicsRectItem* rect = new GraphicsRectItem();
    size_t offset = nodes.size() * 10;
    rect->setPos( width() / 2 + offset, height() / 2 + offset );
    addItem( rect );
    nodes.push_back( rect );
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

        QList<GraphicsRectItem*> startNodes = nodesAt( line->line().p1() );
        QList<GraphicsRectItem*> endNodes = nodesAt( line->line().p2() );

        removeItem( line );
        delete line;

        if( !startNodes.empty() && !endNodes.empty() && startNodes.first() != endNodes.first() ) {
            LOG( "Adding connection" );
            GraphicsLineItem* connection = new GraphicsLineItem( startNodes.first(), endNodes.first() );
            addItem( connection );
            connections.push_back( connection );
        }

    } else {
        QGraphicsScene::mouseMoveEvent( mouseEvent );
        QGraphicsScene::mouseReleaseEvent( mouseEvent );
    }
}

QList<GraphicsRectItem*> GraphicsScene::nodesAt( const QPointF& pos ) const {

    QList<GraphicsRectItem*> filtered;
    QList<QGraphicsItem*> underPos = items( pos );

    for( QGraphicsItem* item : underPos ) {
        if( item->type() == static_cast<int>( CustomGraphicsTypes::NodeType ) ) {
            filtered.push_back( static_cast<GraphicsRectItem*>( item ) );
        }
    }

    return filtered;
}
