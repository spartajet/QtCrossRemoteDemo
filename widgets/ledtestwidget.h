//
// Created by guoxi on 2024/1/15.
//

#ifndef LEDTESTWIDGET_H
#define LEDTESTWIDGET_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class LedTestWidget; }
QT_END_NAMESPACE

class LedTestWidget : public QWidget {
Q_OBJECT

public:
    explicit LedTestWidget(QWidget *parent = nullptr);
    ~LedTestWidget() override;

private:
    Ui::LedTestWidget *ui;
};


#endif //LEDTESTWIDGET_H
