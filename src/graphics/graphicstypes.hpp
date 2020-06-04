#pragma once

#include <QGraphicsItem>

//! types for custom QGraphicsItem objects
//! \sa GraphicsScene::nodesAt
enum class CustomGraphicsTypes : int {
    NodeType = QGraphicsItem::UserType + 1,
    ConnectionType = QGraphicsItem::UserType + 2
};
