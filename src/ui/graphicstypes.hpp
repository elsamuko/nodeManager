#pragma once

#include <QGraphicsItem>

//! types for custom QGraphicsItem objects
//! \sa GraphicsScene::nodesAt
enum class CustomGraphicsTypes : int {
    NodeType = QGraphicsItem::UserType + 1,
    LineType = QGraphicsItem::UserType + 2
};
