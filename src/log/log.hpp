#pragma once

#include <sstream>
#include <ostream>

#ifdef QT_CORE_LIB
#include <QDebug>
#include <QString>
#endif // QT_CORE_LIB

class Logger {
    public:
        Logger( const char* file, int line, const char* function );
        ~Logger();
        template <class T>
        std::ostream& operator<<( const T& t ) {
            out << t;
            return out;
        }

    private:
        void timestamp();

    private:
        size_t intendation = 0;
        std::stringstream out;
};

#define LOG( A ) Logger(__FILE__, __LINE__, __FUNCTION__) << A;

#ifdef QT_CORE_LIB

inline std::ostream& operator<<( std::ostream& out, const QString& s ) {
    out << s.toStdString();
    return out;
}

void customMessageHandler( QtMsgType type, const QMessageLogContext& context, const QString& message );

#endif // QT_CORE_LIB
