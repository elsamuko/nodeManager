#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include "log/log.hpp"

MainWindow::MainWindow( QWidget* parent )
    : QMainWindow( parent )
    , ui( new Ui::MainWindow ) {
    ui->setupUi( this );
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_buttonAddNode_clicked() {
    LOG( "Adding node" );
}