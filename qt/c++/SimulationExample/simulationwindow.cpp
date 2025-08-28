#include "simulationwindow.h"
#include <QRandomGenerator>
#include <QPen>
#include <QBrush>

// 粒子类实现
Particle::Particle(qreal x, qreal y, qreal radius, QColor color)
    : QGraphicsEllipseItem(x, y, radius*2, radius*2), radius(radius), vx(0), vy(0)
{
    setBrush(QBrush(color));
    setPen(QPen(Qt::black, 1));
}

void Particle::setVelocity(qreal vx, qreal vy)
{
    this->vx = vx;
    this->vy = vy;
}

void Particle::updatePosition(qreal gravity, qreal sceneWidth, qreal sceneHeight)
{
    // 应用重力加速度
    vy += gravity;

    // 更新位置
    qreal newX = x() + vx;
    qreal newY = y() + vy;

    // 边界碰撞检测 - 左右边界
    if (newX <= 0) {
        newX = 0;
        vx = -vx * 0.8;  // 能量损失
    } else if (newX + 2*radius >= sceneWidth) {
        newX = sceneWidth - 2*radius;
        vx = -vx * 0.8;
    }

    // 边界碰撞检测 - 上下边界
    if (newY <= 0) {
        newY = 0;
        vy = -vy * 0.8;
    } else if (newY + 2*radius >= sceneHeight) {
        newY = sceneHeight - 2*radius;
        vy = -vy * 0.8;
    }

    setPos(newX, newY);
}

// 仿真窗口类实现
SimulationWindow::SimulationWindow(QWidget *parent)
    : QWidget(parent), isRunning(false), gravity(0.5),
    sceneWidth(800), sceneHeight(600)
{
    // 创建场景和视图
    scene = new QGraphicsScene(0, 0, sceneWidth, sceneHeight, this);
    scene->setBackgroundBrush(QBrush(QColor(240, 240, 240)));

    view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 创建定时器
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &SimulationWindow::updateSimulation);
    timer->setInterval(30);  // 约33fps

    // 创建控制组件
    createControls();

    // 布局设置
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(view);

    QHBoxLayout *controlsLayout = new QHBoxLayout();
    controlsLayout->addWidget(addParticleBtn);
    controlsLayout->addWidget(startPauseBtn);
    controlsLayout->addWidget(gravityLabel);
    controlsLayout->addWidget(gravitySlider);

    mainLayout->addLayout(controlsLayout);

    setLayout(mainLayout);
    resize(sceneWidth + 20, sceneHeight + 100);
}

SimulationWindow::~SimulationWindow()
{
    for (Particle *p : particles) {
        delete p;
    }
}

void SimulationWindow::createControls()
{
    // 添加粒子按钮
    addParticleBtn = new QPushButton("添加粒子", this);
    connect(addParticleBtn, &QPushButton::clicked, this, &SimulationWindow::onAddParticleClicked);

    // 开始/暂停按钮
    startPauseBtn = new QPushButton("开始", this);
    connect(startPauseBtn, &QPushButton::clicked, this, &SimulationWindow::onStartPauseClicked);

    // 重力滑块
    gravityLabel = new QLabel("重力: " + QString::number(gravity), this);
    gravitySlider = new QSlider(Qt::Horizontal, this);
    gravitySlider->setRange(1, 20);
    gravitySlider->setValue(gravity * 10);
    connect(gravitySlider, &QSlider::valueChanged, this, &SimulationWindow::onGravityChanged);
}

void SimulationWindow::updateSimulation()
{
    // 更新所有粒子位置
    for (Particle *p : particles) {
        p->updatePosition(gravity, sceneWidth, sceneHeight);
    }
}

void SimulationWindow::onAddParticleClicked()
{
    // 随机生成粒子属性
    QRandomGenerator *rand = QRandomGenerator::global();
    qreal radius = rand->bounded(10, 30);

    // 生成 [radius, sceneWidth - radius) 范围内的x坐标
    qreal xMin = radius;
    qreal xMax = sceneWidth - radius;
    qreal x = xMin + (xMax - xMin) * rand->generateDouble();  // 关键修正

    // 生成 [radius, sceneHeight - radius) 范围内的y坐标
    qreal yMin = radius;
    qreal yMax = sceneHeight - radius;
    qreal y = yMin + (yMax - yMin) * rand->generateDouble();  // 关键修正

    // 随机颜色
    QColor color(rand->bounded(50, 255), rand->bounded(50, 255), rand->bounded(50, 255));

    // 创建粒子并添加到场景
    Particle *p = new Particle(x, y, radius, color);
    p->setVelocity(rand->bounded(-3, 4), rand->bounded(-2, 3));  // 随机初速度
    scene->addItem(p);
    particles.push_back(p);
}

void SimulationWindow::onStartPauseClicked()
{
    isRunning = !isRunning;
    if (isRunning) {
        timer->start();
        startPauseBtn->setText("暂停");
    } else {
        timer->stop();
        startPauseBtn->setText("开始");
    }
}

void SimulationWindow::onGravityChanged(int value)
{
    gravity = value / 10.0;
    gravityLabel->setText("重力: " + QString::number(gravity, 'f', 1));
}
