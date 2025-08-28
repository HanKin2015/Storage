#ifndef SIMULATIONWINDOW_H
#define SIMULATIONWINDOW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QLabel>
#include <vector>
#include <QGraphicsEllipseItem>

// 定义粒子类
class Particle : public QGraphicsEllipseItem
{
public:
    Particle(qreal x, qreal y, qreal radius, QColor color);

    void setVelocity(qreal vx, qreal vy);
    void updatePosition(qreal gravity, qreal sceneWidth, qreal sceneHeight);

private:
    qreal vx;  // x方向速度
    qreal vy;  // y方向速度
    qreal radius;
};

// 仿真窗口类
class SimulationWindow : public QWidget
{
    Q_OBJECT

public:
    SimulationWindow(QWidget *parent = nullptr);
    ~SimulationWindow();

private slots:
    void updateSimulation();
    void onAddParticleClicked();
    void onStartPauseClicked();
    void onGravityChanged(int value);

private:
    QGraphicsView *view;
    QGraphicsScene *scene;
    QTimer *timer;
    QPushButton *addParticleBtn;
    QPushButton *startPauseBtn;
    QSlider *gravitySlider;
    QLabel *gravityLabel;

    std::vector<Particle*> particles;
    bool isRunning;
    qreal gravity;
    qreal sceneWidth;
    qreal sceneHeight;

    void createControls();
};

#endif // SIMULATIONWINDOW_H
