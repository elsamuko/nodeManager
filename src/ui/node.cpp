#include "ui/node.hpp"

Node::Node( const qint64 id, QGraphicsItem* parent ) :
    QGraphicsRectItem( parent ),
    id( id ) {

    setRect( QRect( 0, 0, 100, 100 ) );
    setFlag( QGraphicsItem::ItemIsMovable, true );
    setFlag( QGraphicsItem::ItemIsSelectable, true );
    setFlag( QGraphicsItem::ItemSendsGeometryChanges, true );
}

QVariant Node::itemChange( GraphicsItemChange change, const QVariant& value ) {
    if( change == ItemPositionChange ) {
        for( const auto& cb : onMoveCallbacks ) {
            cb.second();
        }
    }

    return QGraphicsRectItem::itemChange( change, value );
}
