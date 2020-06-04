#pragma once

#include <QGraphicsRectItem>

#include "ui/graphicstypes.hpp"

class GraphicsRectItem : public QGraphicsRectItem {
    public:
        explicit GraphicsRectItem( QGraphicsItem* parent = nullptr );
        virtual int type() const override { return static_cast<int>( CustomGraphicsTypes::NodeType ); }
};
