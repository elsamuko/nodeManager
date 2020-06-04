#pragma once

#include <QGraphicsScene>

class GraphicsScene : public QGraphicsScene {
        Q_OBJECT
    public:
        enum class Mode { Move, Connect };
        explicit GraphicsScene( QObject* parent = nullptr );

        //! toggles mouse mode between moving/connecting nodes
        void setMode( Mode m ) { mode = m; }

        void addNode();

    protected:
        void mousePressEvent( QGraphicsSceneMouseEvent* mouseEvent ) override;
        void mouseMoveEvent( QGraphicsSceneMouseEvent* mouseEvent ) override;
        void mouseReleaseEvent( QGraphicsSceneMouseEvent* mouseEvent ) override;

    private:
        //! temporary drawn line while connecting nodes
        QGraphicsLineItem* line = nullptr;

        Mode mode = Mode::Move;
};
