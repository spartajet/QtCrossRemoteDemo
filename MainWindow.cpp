//
// Created by guoxi on 2024/1/15.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MianWindow.h" resolved

#include "MainWindow.h"
#include "ui_MianWindow.h"
#include "widgets/ledtestwidget.h"




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MianWindow) {
    ui->setupUi(this);
#if __arm__
    this->setWindowState(Qt::WindowFullScreen);
#else
    this->resize(800,400);
#endif

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onItemClick(const QModelIndex &index) {
    this->ui->stackedWidget->setCurrentIndex(index.row());
}

void MainWindow::onLedInitialButtonClick() {

}

void MainWindow::onLedControlButtonClick() {

}

