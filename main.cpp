#include <QApplication>
#include <QPushButton>
#include "MainWindow.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();
    return QApplication::exec();
}
