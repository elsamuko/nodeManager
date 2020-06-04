#include "ui/graphicslineitem.hpp"

#include <QPen>

GraphicsLineItem::GraphicsLineItem( const qint64 id, GraphicsRectItem* startItem, GraphicsRectItem* endItem, QGraphicsItem* parent ) :
    QGraphicsLineItem( parent ),
    id( id ),
    startRect( startItem ),
    endRect( endItem ) {

    setPen( QPen( Qt::red, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin ) );

    update();

    startRect->setOnMoveCallback( this, [this] { update(); } );
    endRect->setOnMoveCallback( this, [this] { update(); } );
}

GraphicsLineItem::~GraphicsLineItem() {
    startRect->removeOnMoveCallback( this );
    endRect->removeOnMoveCallback( this );
}

bool GraphicsLineItem::connectedTo( const GraphicsRectItem* node ) const {
    return ( node == startRect ) || ( node == endRect );
}

void GraphicsLineItem::update() {
    QLineF line( mapFromItem( startRect, startRect->boundingRect().width() / 2, startRect->boundingRect().height() / 2 ),
                 mapFromItem( endRect, endRect->boundingRect().width() / 2, endRect->boundingRect().height() / 2 ) );
    setLine( line );
}
