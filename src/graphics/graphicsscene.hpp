#pragma once

#include <QGraphicsScene>

class Node;
class Connection;

class GraphicsScene : public QGraphicsScene {
        Q_OBJECT
    public:
        enum class Mode { Move, Connect };
        explicit GraphicsScene( QObject* parent = nullptr );
        ~GraphicsScene();

        //! toggles mouse mode between moving/connecting nodes
        void setMode( Mode m ) { mode = m; }

        //! removes all nodes and connections
        void clearNodes();

        void addNode( Node* node = nullptr );

        QJsonObject toJson() const;
        void fromJson( const QJsonObject& all );

    protected:
        virtual void mousePressEvent( QGraphicsSceneMouseEvent* mouseEvent ) override;
        virtual void mouseMoveEvent( QGraphicsSceneMouseEvent* mouseEvent ) override;
        virtual void mouseReleaseEvent( QGraphicsSceneMouseEvent* mouseEvent ) override;

    private:
        //! \returns QList with all nodes under \param pos
        QList<Node*> nodesAt( const QPointF& pos ) const;
        //! \returns the connections, a node is connected to
        QList<Connection*> connectionsForNode( const Node* node ) const;
        //! removes cons from connections
        void clearConnections( const QList<Connection*>& cons );
        void addConnection( Connection* connection );

    private:
        //! temporary drawn line while connecting nodes
        QGraphicsLineItem* line = nullptr;
        QList<Node*> nodes;
        QList<Connection*> connections;
        Mode mode = Mode::Move;
};
