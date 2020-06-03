#include "ui/graphicsrectitem.hpp"

GraphicsRectItem::GraphicsRectItem( QGraphicsItem* parent ) :
    QGraphicsRectItem( parent ) {

    setRect( QRect( 0, 0, 100, 100 ) );
    setFlag( QGraphicsItem::ItemIsMovable, true );
    setFlag( QGraphicsItem::ItemIsSelectable, true );
}
