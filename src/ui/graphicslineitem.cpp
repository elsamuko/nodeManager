#include "ui/graphicslineitem.hpp"

#include <QPen>

GraphicsLineItem::GraphicsLineItem( GraphicsRectItem* startItem, GraphicsRectItem* endItem, QGraphicsItem* parent ) :
    QGraphicsLineItem( parent ),
    startRect( startItem ),
    endRect( endItem ) {

    setPen( QPen( Qt::red, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin ) );
    setLine( QLineF( startItem->pos(), endItem->pos() ) );

}
