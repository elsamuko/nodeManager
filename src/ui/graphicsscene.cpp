#include "ui/graphicsscene.hpp"

#include <QGraphicsLineItem>
#include <QGraphicsSceneMouseEvent>

#include "ui/graphicsrectitem.hpp"

GraphicsScene::GraphicsScene( QObject* parent ) : QGraphicsScene( parent ) {}

void GraphicsScene::addNode() {
    GraphicsRectItem* rect = new GraphicsRectItem();
    rect->setPos( width() / 2, height() / 2 );
    addItem( rect );
}

void GraphicsScene::mousePressEvent( QGraphicsSceneMouseEvent* mouseEvent ) {
    if( mode == Mode::Connect ) {
        line = new QGraphicsLineItem( QLineF( mouseEvent->scenePos(),
                                              mouseEvent->scenePos() ) );
        addItem( line );
    } else {
        QGraphicsScene::mousePressEvent( mouseEvent );
    }
}

void GraphicsScene::mouseMoveEvent( QGraphicsSceneMouseEvent* mouseEvent ) {
    if( line && mode == Mode::Connect ) {
        QLineF newLine( line->line().p1(), mouseEvent->scenePos() );
        line->setLine( newLine );
    } else {
        QGraphicsScene::mouseMoveEvent( mouseEvent );
    }
}

void GraphicsScene::mouseReleaseEvent( QGraphicsSceneMouseEvent* mouseEvent ) {
    QGraphicsScene::mouseReleaseEvent( mouseEvent );
}
