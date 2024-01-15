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

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onItemDoubleClick(QListWidgetItem *item) {
    LedTestWidget *ledTestWidget=new LedTestWidget(this);
    this->contentGridLayout.addWidget(ledTestWidget);
    this->ui->widget->setLayout(&this->contentGridLayout);
}
