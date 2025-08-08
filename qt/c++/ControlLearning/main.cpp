#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Qt控件展示学习程序");
    Widget w;
    w.show();

    return a.exec();
}
