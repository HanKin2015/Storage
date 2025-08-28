#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 设置全局字体，确保中文显示正常
    QFont font("SimHei", 9);
    a.setFont(font);

    MainWindow w;
    w.show();
    return a.exec();
}
