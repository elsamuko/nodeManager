#pragma once

#include <optional>

#include <QString>
#include <QJsonObject>

namespace persistence {
bool save( const QString& filename, const QJsonObject& json );
std::optional<QJsonObject> load( const QString& filename );
}
