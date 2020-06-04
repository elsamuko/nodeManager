#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "ui/graphicsscene.hpp"

MainWindow::MainWindow( QWidget* parent )
    : QMainWindow( parent )
    , ui( new Ui::MainWindow )
    , scene( new GraphicsScene( this ) ) {

    ui->setupUi( this );
    scene->setSceneRect( QRectF( 0, 0, 1000, 1000 ) );
    ui->graphicsView->setScene( scene );
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_buttonAddNode_clicked() {
    scene->addNode();
}

void MainWindow::on_actionQuit_triggered() {
    LOG( "Quitting..." );
    qApp->quit();
}

void MainWindow::on_buttomMove_clicked() {
    LOG( "Switching to move mode" );
    scene->setMode( GraphicsScene::Mode::Move );
}

void MainWindow::on_buttonConnect_clicked() {
    LOG( "Switching to connect mode" );
    scene->setMode( GraphicsScene::Mode::Connect );
}
