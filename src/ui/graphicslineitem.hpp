#pragma once

#include <QGraphicsLineItem>

#include "ui/graphicsrectitem.hpp"
#include "ui/graphicstypes.hpp"

class GraphicsLineItem : public QGraphicsLineItem {
    public:
        explicit GraphicsLineItem( size_t id, GraphicsRectItem* startItem, GraphicsRectItem* endItem, QGraphicsItem* parent = nullptr );
        virtual int type() const override { return static_cast<int>( CustomGraphicsTypes::LineType ); }
        size_t getId() const { return id; }

    private:
        //! updates itself from new positions of startRect and endRect
        void update();

        size_t id;
        GraphicsRectItem* startRect;
        GraphicsRectItem* endRect;
};
