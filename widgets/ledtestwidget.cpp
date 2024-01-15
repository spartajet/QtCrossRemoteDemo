//
// Created by guoxi on 2024/1/15.
//

// You may need to build the project (run Qt uic code generator) to get "ui_LedTestWidget.h" resolved

#include "ledtestwidget.h"
#include "ui_LedTestWidget.h"


LedTestWidget::LedTestWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::LedTestWidget) {
    ui->setupUi(this);
}

LedTestWidget::~LedTestWidget() {
    delete ui;
}
