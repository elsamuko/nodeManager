#include "ui/graphicsrectitem.hpp"

GraphicsRectItem::GraphicsRectItem( QGraphicsItem* parent ) :
    QGraphicsRectItem( parent ) {

    setRect( QRect( 0, 0, 100, 100 ) );
    setFlag( QGraphicsItem::ItemIsMovable, true );
    setFlag( QGraphicsItem::ItemIsSelectable, true );
    setFlag( QGraphicsItem::ItemSendsGeometryChanges, true );
}

QVariant GraphicsRectItem::itemChange( GraphicsItemChange change, const QVariant& value ) {
    if( change == ItemPositionChange ) {
        for( const auto& cb : onMoveCallbacks ) {
            cb.second();
        }
    }

    return QGraphicsRectItem::itemChange( change, value );
}
