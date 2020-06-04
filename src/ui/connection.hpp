#pragma once

#include <QGraphicsLineItem>

#include "ui/node.hpp"
#include "ui/graphicstypes.hpp"

class Connection : public QGraphicsLineItem {
    public:
        explicit Connection( const qint64 id, Node* startItem, Node* endItem, QGraphicsItem* parent = nullptr );
        ~Connection();
        virtual int type() const override { return static_cast<int>( CustomGraphicsTypes::ConnectionType ); }
        qint64 getId() const { return id; }
        qint64 getIdStart() const { return startRect->getId(); }
        qint64 getIdEnd() const { return endRect->getId(); }
        bool connectedTo( const Node* node ) const;

    private:
        //! updates itself from new positions of startRect and endRect
        void update();

        qint64 id;
        Node* startRect;
        Node* endRect;
};
