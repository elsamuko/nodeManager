#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "ui/graphicsscene.hpp"

MainWindow::MainWindow( QWidget* parent )
    : QMainWindow( parent )
    , ui( new Ui::MainWindow )
    , scene( new GraphicsScene( this ) ) {

    ui->setupUi( this );
    ui->graphicsView->setScene( scene );
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_buttonAddNode_clicked() {
    LOG( "Adding node" );
}

void MainWindow::on_actionQuit_triggered() {
    LOG( "Quitting..." );
    qApp->quit();
}
