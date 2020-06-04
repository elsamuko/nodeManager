#include "ui/graphicslineitem.hpp"

#include <QPen>

GraphicsLineItem::GraphicsLineItem( GraphicsRectItem* startItem, GraphicsRectItem* endItem, QGraphicsItem* parent ) :
    QGraphicsLineItem( parent ),
    startRect( startItem ),
    endRect( endItem ) {

    setPen( QPen( Qt::red, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin ) );

    update();

    startRect->setOnMoveCallback( this, [this] { update(); } );
    endRect->setOnMoveCallback( this, [this] { update(); } );
}

void GraphicsLineItem::update() {
    QLineF line( mapFromItem( startRect, startRect->boundingRect().width() / 2, startRect->boundingRect().height() / 2 ),
                 mapFromItem( endRect, endRect->boundingRect().width() / 2, endRect->boundingRect().height() / 2 ) );
    setLine( line );
}
