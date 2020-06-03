#pragma once

#include <sstream>
#include <ostream>

#include <QString>

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

inline std::ostream& operator<<( std::ostream& out, const QString& s ) {
    out << s.toStdString();
    return out;
}
