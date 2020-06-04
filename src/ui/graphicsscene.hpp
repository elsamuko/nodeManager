#pragma once

#include <QGraphicsScene>

class GraphicsRectItem;
class GraphicsLineItem;

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

        void addNode( GraphicsRectItem* node = nullptr );

        QJsonObject toJson() const;

    protected:
        virtual void mousePressEvent( QGraphicsSceneMouseEvent* mouseEvent ) override;
        virtual void mouseMoveEvent( QGraphicsSceneMouseEvent* mouseEvent ) override;
        virtual void mouseReleaseEvent( QGraphicsSceneMouseEvent* mouseEvent ) override;

    private:
        //! \returns QList with all nodes under \param pos
        QList<GraphicsRectItem*> nodesAt( const QPointF& pos ) const;
        //! \returns the connections, a node is connected to
        QList<GraphicsLineItem*> connectionsForNode( const GraphicsRectItem* node ) const;
        //! removes cons from connections
        void clearConnections( const QList<GraphicsLineItem*>& cons );

    private:
        //! temporary drawn line while connecting nodes
        QGraphicsLineItem* line = nullptr;
        QList<GraphicsRectItem*> nodes;
        QList<GraphicsLineItem*> connections;
        Mode mode = Mode::Move;
};
