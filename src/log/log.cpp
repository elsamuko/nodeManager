#include "log/log.hpp"

#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <mutex>
#include <cstring>

#ifndef _WIN32
#include <unistd.h>
#include <sys/syscall.h>
#else
#include <Windows.h>
#endif

namespace  {
std::mutex m;
std::string threadId() {
    std::stringstream ss;
    ss.width( 8 );
#ifdef __APPLE__
    uint64_t tid = 0;;
    pthread_threadid_np( nullptr, &tid );
#endif
#ifdef __linux__
    long tid = syscall( SYS_gettid );
#endif
#ifdef _WIN32
    DWORD tid = GetCurrentThreadId();
#endif
    ss << std::hex << tid;
    return ss.str();
}
}

Logger::Logger( const char* file, int line, const char* function ) {
    timestamp();
    out << " " << threadId() << " ";
    out.fill( ' ' );
    out.width( 25 );

    const char* pos = strrchr( file, '/' );

    if( !pos ) { pos = strrchr( file, '\\' ); }

    if( !pos ) { pos = "/nofile"; }

    out << ( pos + 1 ) << " ";
    out.width( 25 );
    out << function << "(";
    out.width( 4 );
    out.setf( std::ios::right );
    out << line << "): ";
    intendation = out.tellp();
}

Logger::~Logger() {

    m.lock();

    std::string line;
    std::string whitespaces( intendation, ' ' );

    if( std::getline( out, line ) ) {
        std::cout << line << std::endl;

        while( std::getline( out, line ) ) {
            std::cout << whitespaces << line << std::endl;
        }
    }

    m.unlock();
}

void Logger::timestamp() {

    auto tp = std::chrono::system_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>( tp.time_since_epoch() );
    size_t modulo = ms.count() % 1000;

    time_t seconds = std::chrono::duration_cast<std::chrono::seconds>( ms ).count();

    out << std::put_time( std::gmtime( &seconds ), "%T." );

    // ms
    out.fill( '0' );
    out.width( 3 );
    out << modulo;
}
