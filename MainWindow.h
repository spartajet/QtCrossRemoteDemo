//
// Created by guoxi on 2024/1/15.
//

#ifndef MIANWINDOW_H
#define MIANWINDOW_H

#include <qlistwidget.h>
#include <QMainWindow>
#include <QGridLayout>


QT_BEGIN_NAMESPACE

namespace Ui {
    class MianWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    ~MainWindow() override;

private:
    Ui::MianWindow *ui;
    QGridLayout contentGridLayout;

private slots:
    void onItemClick(const QModelIndex &index);
    void onLedInitialButtonClick();
    void onLedControlButtonClick();
};


#endif //MIANWINDOW_H
