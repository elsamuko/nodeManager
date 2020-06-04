#pragma once

#include <QGraphicsLineItem>

#include "ui/graphicsrectitem.hpp"
#include "ui/graphicstypes.hpp"

class GraphicsLineItem : public QGraphicsLineItem {
    public:
        explicit GraphicsLineItem( const qint64 id, GraphicsRectItem* startItem, GraphicsRectItem* endItem, QGraphicsItem* parent = nullptr );
        virtual int type() const override { return static_cast<int>( CustomGraphicsTypes::LineType ); }
        qint64 getId() const { return id; }

    private:
        //! updates itself from new positions of startRect and endRect
        void update();

        qint64 id;
        GraphicsRectItem* startRect;
        GraphicsRectItem* endRect;
};
