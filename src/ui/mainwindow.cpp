#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QStandardPaths>

#include "ui/graphicsscene.hpp"
#include "persistence.hpp"

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

void MainWindow::on_actionSave_As_triggered() {
    QString documentsFolder = QStandardPaths::writableLocation( QStandardPaths::DocumentsLocation );
    QString filename = QFileDialog::getSaveFileName( this, "Saving to json", documentsFolder, "JSON (*.json *.JSON)" );

    if( filename.isEmpty() ) {
        return;
    }

    QJsonObject json = scene->toJson();

    if( persistence::save( filename, json ) ) {
        ui->statusbar->showMessage( "Saved to " + filename, 3000 );
    } else {
        ui->statusbar->showMessage( "Could not save to " + filename, 3000 );
    }
}

void MainWindow::on_actionOpen_triggered() {
    QString documentsFolder = QStandardPaths::writableLocation( QStandardPaths::DocumentsLocation );
    QString filename = QFileDialog::getOpenFileName( this, "Loading from json", documentsFolder, "JSON (*.json *.JSON)" );

    if( filename.isEmpty() ) {
        return;
    }

    auto opt = persistence::load( filename );

    if( opt ) {
        scene->fromJson( *opt );
        ui->statusbar->showMessage( "Loaded from " + filename, 3000 );
    } else {
        ui->statusbar->showMessage( "Could not load from " + filename, 3000 );
    }
}

void MainWindow::on_buttonClear_clicked() {
    scene->clearNodes();
}
