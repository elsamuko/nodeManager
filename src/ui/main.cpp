#include <QApplication>

#include "ui/mainwindow.hpp"

int main( int argc, char* argv[] ) {
    LOG( "Starting" );

    int rv = 0;
    {
        QApplication a( argc, argv );
        MainWindow w;
        w.show();
        rv = a.exec();
    }

    LOG( "Exiting with status " << rv );
    return rv;
}
