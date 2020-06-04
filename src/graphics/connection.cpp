#include "graphics/connection.hpp"

#include <QPen>

Connection::Connection( const qint64 id, Node* startItem, Node* endItem, QGraphicsItem* parent ) :
    QGraphicsLineItem( parent ),
    id( id ),
    startRect( startItem ),
    endRect( endItem ) {

    setPen( QPen( Qt::red, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin ) );

    update();

    startRect->setOnMoveCallback( this, [this] { update(); } );
    endRect->setOnMoveCallback( this, [this] { update(); } );
}

Connection::~Connection() {
    startRect->removeOnMoveCallback( this );
    endRect->removeOnMoveCallback( this );
}

bool Connection::connectedTo( const Node* node ) const {
    return ( node == startRect ) || ( node == endRect );
}

void Connection::update() {
    QLineF line( mapFromItem( startRect, startRect->boundingRect().width() / 2, startRect->boundingRect().height() / 2 ),
                 mapFromItem( endRect, endRect->boundingRect().width() / 2, endRect->boundingRect().height() / 2 ) );
    setLine( line );
}
