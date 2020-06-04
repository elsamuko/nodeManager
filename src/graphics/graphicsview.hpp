#pragma once

#include <QGraphicsView>

class GraphicsView : public QGraphicsView {
        Q_OBJECT
    public:
        explicit GraphicsView( QWidget* parent = 0 );

    protected:
        virtual void wheelEvent( QWheelEvent* event ) override;

};
