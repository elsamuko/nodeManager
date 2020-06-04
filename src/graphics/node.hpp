#pragma once

#include <functional>

#include <QGraphicsRectItem>

#include "graphics/graphicstypes.hpp"

class Node : public QGraphicsRectItem {
    public:
        explicit Node( const qint64 id, QGraphicsItem* parent = nullptr );
        virtual int type() const override { return static_cast<int>( CustomGraphicsTypes::NodeType ); }
        //! add callback, which is called, if Node is moved
        void setOnMoveCallback( const QGraphicsItem* sender, const std::function<void()>& func ) { onMoveCallbacks.emplace( sender, func ); }
        void removeOnMoveCallback( const QGraphicsItem* sender ) { onMoveCallbacks.erase( sender ); }
        qint64 getId() const { return id; }

    protected:
        //! \note calls onMoveCallbacks
        virtual QVariant itemChange( GraphicsItemChange change, const QVariant& value ) override;

    private:
        qint64 id;
        std::map<const QGraphicsItem*, std::function<void()>> onMoveCallbacks;
};
