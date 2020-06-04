#pragma once

#include <QGraphicsLineItem>

#include "ui/graphicsrectitem.hpp"
#include "ui/graphicstypes.hpp"

class GraphicsLineItem : public QGraphicsLineItem {
    public:
        explicit GraphicsLineItem( GraphicsRectItem* startItem, GraphicsRectItem* endItem, QGraphicsItem* parent = nullptr );
        virtual int type() const override { return static_cast<int>( CustomGraphicsTypes::LineType ); }

    private:
        //! updates itself from new positions of startRect and endRect
        void update();

        GraphicsRectItem* startRect;
        GraphicsRectItem* endRect;
};
