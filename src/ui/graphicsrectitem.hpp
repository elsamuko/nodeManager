#pragma once

#include <functional>

#include <QGraphicsRectItem>

#include "ui/graphicstypes.hpp"

class GraphicsRectItem : public QGraphicsRectItem {
    public:
        explicit GraphicsRectItem( const qint64 id, QGraphicsItem* parent = nullptr );
        virtual int type() const override { return static_cast<int>( CustomGraphicsTypes::NodeType ); }
        void setOnMoveCallback( const QGraphicsItem* sender, const std::function<void()>& func ) { onMoveCallbacks.emplace( sender, func ); }
        qint64 getId() const { return id; }

    protected:
        virtual QVariant itemChange( GraphicsItemChange change, const QVariant& value ) override;

    private:
        qint64 id;
        std::map<const QGraphicsItem*, std::function<void()>> onMoveCallbacks;
};
