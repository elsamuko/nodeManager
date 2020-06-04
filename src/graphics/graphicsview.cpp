#include "graphics/graphicsview.hpp"

#include <QApplication>
#include <QWheelEvent>

GraphicsView::GraphicsView( QWidget* parent ) :
    QGraphicsView( parent ) {
}

void GraphicsView::wheelEvent( QWheelEvent* event ) {
    if( QApplication::keyboardModifiers() == Qt::ControlModifier ) {
        if( event->delta() > 0 ) {
            scale( 1.05, 1.05 );
        } else {
            scale( 0.95, 0.95 );
        }
    } else {
        QGraphicsView::wheelEvent( event );
    }
}
