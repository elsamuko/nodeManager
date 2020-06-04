#pragma once

#include <functional>

#include <QGraphicsRectItem>

#include "ui/graphicstypes.hpp"

class GraphicsRectItem : public QGraphicsRectItem {
    public:
        explicit GraphicsRectItem( size_t id, QGraphicsItem* parent = nullptr );
        virtual int type() const override { return static_cast<int>( CustomGraphicsTypes::NodeType ); }
        void setOnMoveCallback( const QGraphicsItem* sender, const std::function<void()>& func ) { onMoveCallbacks.emplace( sender, func ); }
        size_t getId() const { return id; }

    protected:
        virtual QVariant itemChange( GraphicsItemChange change, const QVariant& value ) override;

    private:
        size_t id;
        std::map<const QGraphicsItem*, std::function<void()>> onMoveCallbacks;
};
