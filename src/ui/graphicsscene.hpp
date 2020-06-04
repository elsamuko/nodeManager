#pragma once

#include <QGraphicsScene>

class GraphicsRectItem;
class GraphicsLineItem;

class GraphicsScene : public QGraphicsScene {
        Q_OBJECT
    public:
        enum class Mode { Move, Connect };
        explicit GraphicsScene( QObject* parent = nullptr );

        //! toggles mouse mode between moving/connecting nodes
        void setMode( Mode m ) { mode = m; }

        void addNode();

    protected:
        virtual void mousePressEvent( QGraphicsSceneMouseEvent* mouseEvent ) override;
        virtual void mouseMoveEvent( QGraphicsSceneMouseEvent* mouseEvent ) override;
        virtual void mouseReleaseEvent( QGraphicsSceneMouseEvent* mouseEvent ) override;

    private:
        //! \returns QList with all nodes under \param pos
        QList<GraphicsRectItem*> nodesAt( const QPointF& pos ) const;

    private:
        //! temporary drawn line while connecting nodes
        QGraphicsLineItem* line = nullptr;
        QList<GraphicsRectItem*> nodes;
        QList<GraphicsLineItem*> connections;
        Mode mode = Mode::Move;
};
