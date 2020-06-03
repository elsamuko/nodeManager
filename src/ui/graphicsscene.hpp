#pragma once

#include <QGraphicsScene>

class GraphicsScene : public QGraphicsScene {
        Q_OBJECT
    public:
        explicit GraphicsScene( QObject* parent = nullptr );
};
