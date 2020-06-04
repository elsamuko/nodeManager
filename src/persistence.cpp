#include "persistence.hpp"

#include <QFile>
#include <QTextStream>
#include <QJsonDocument>

std::optional<QByteArray> fromFile( const QString& filename ) {
    std::optional<QByteArray> content;
    QFile file( filename );

    if( file.open( QIODevice::ReadOnly ) ) {
        content = file.readAll();
        file.close();
    } else {
        LOG( "Could not open " << filename );
    }

    return content;
}

bool toFile( const QString& filename, const QByteArray& content ) {
    bool ok = false;
    QFile file( filename );

    if( file.open( QIODevice::WriteOnly ) ) {
        file.write( content );
        file.close();
        ok = true;
    } else {
        LOG( "Could not open " << filename );
    }

    return ok;
}

bool persistence::save( const QString& filename, const QJsonObject& json ) {
    QByteArray content = QJsonDocument( json ).toJson();
    bool rv = toFile( filename, content );
    return rv;
}

std::optional<QJsonObject> persistence::load( const QString& filename ) {
    LOG( "Loading from " << filename.toStdString() );
    std::optional<QByteArray> content = fromFile( filename );

    if( content.value_or( QByteArray() ).isEmpty() ) { LOG( "Empty json" ); return {}; }

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson( content.value_or( QByteArray() ), &error );

    if( error.error != QJsonParseError::NoError ) { LOG( "Could not parse json: " << error.errorString() ); return {}; }

    QJsonObject json = doc.object();
    return json;
}
