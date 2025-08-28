#include "simulationwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SimulationWindow w;
    w.setWindowTitle("物理仿真Demo - 物体下落与碰撞");
    w.show();

    return a.exec();
}
