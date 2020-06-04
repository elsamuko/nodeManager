#pragma once

#include <functional>

#include <QGraphicsRectItem>

#include "ui/graphicstypes.hpp"

class GraphicsRectItem : public QGraphicsRectItem {
    public:
        explicit GraphicsRectItem( QGraphicsItem* parent = nullptr );
        virtual int type() const override { return static_cast<int>( CustomGraphicsTypes::NodeType ); }
        void setOnMoveCallback( const QGraphicsItem* sender, const std::function<void()>& func ) { onMoveCallbacks.emplace( sender, func ); }

    protected:
        virtual QVariant itemChange( GraphicsItemChange change, const QVariant& value ) override;

    private:
        std::map<const QGraphicsItem*, std::function<void()>> onMoveCallbacks;
};
