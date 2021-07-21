#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QCoreApplication>
#include <QDebug>
#include <QComboBox>
#include <QList>
#include <QCameraInfo>
#include <QListData>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Init();
    //InitLayout();
}

void MainWindow::InitLayout()
{
    this->setWindowTitle("摄像头捕获");
    this->resize(600, 400);

    QPushButton *captureBtn = new QPushButton("捕获", this);
    QPushButton *saveBtn = new QPushButton("保存", this);
    QPushButton *exitBtn = new QPushButton("退出", this);

    displayLabel = new QLabel();
    displayLabel->setFixedSize(150, 150);
    displayLabel->setScaledContents(true);

    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->addWidget(displayLabel);
    rightLayout->addWidget(captureBtn);
    rightLayout->addWidget(saveBtn);
    rightLayout->addWidget(exitBtn);

    //QWidget *widget = new QWidget();
    //this->setCentralWidget(widget);
    centralWidget()->setLayout(rightLayout);
}

void MainWindow::Init()
{
    //https://blog.csdn.net/weixin_44307528/article/details/104766533
    this->setWindowTitle("摄像头捕获");
    this->resize(600, 400);
    QWidget *widget = new QWidget();
    this->setCentralWidget(widget);

    cameraList = QCameraInfo::availableCameras();
    for (int i = 0; i < cameraList.size(); i++) {
        qDebug() << cameraList.at(i).deviceName(); //获取设备名称
        qDebug() << cameraList.at(i).description();
        qDebug() << cameraList.at(i).position();
        qDebug() << "###############";
    }

    for (QList<QCameraInfo>::iterator it = cameraList.begin(); it != cameraList.end(); it++) {
        qDebug("device name : %s", qPrintable(it->deviceName()));
        qDebug("device description : %s", qPrintable(it->description()));
        qDebug("device position : %d", it->position());
    }

    comboBox = new QComboBox();
    int cameraCnt = cameraList.size();
    for (int i = 0; i < cameraCnt; i++) {
        comboBox->addItem(cameraList.at(i).description());
    }

    QPushButton *openBtn = new QPushButton("打开", this);
    QPushButton *closeBtn = new QPushButton("关闭", this);
    QPushButton *captureBtn = new QPushButton("捕获", this);
    QPushButton *saveBtn = new QPushButton("保存", this);
    QPushButton *exitBtn = new QPushButton("退出", this);

    displayLabel = new QLabel(this);
    displayLabel->setFixedSize(150, 150);
    displayLabel->setScaledContents(true);

    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->addWidget(displayLabel);
    rightLayout->addWidget(comboBox);
    rightLayout->addWidget(openBtn);
    rightLayout->addWidget(closeBtn);
    rightLayout->addWidget(captureBtn);
    rightLayout->addWidget(saveBtn);
    rightLayout->addWidget(exitBtn);

    camera = new QCamera(this);
    //camera = new QCamera(cameraList.at(comboBox->currentIndex()));
    camera->setCaptureMode(QCamera::CaptureStillImage);
    cameraImageCapture = new QCameraImageCapture(camera);
    cameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    cameravierfinder = new QCameraViewfinder(this);
    camera->setViewfinder(cameravierfinder);

    mainlayout = new QHBoxLayout();
    mainlayout->addWidget(cameravierfinder);
    mainlayout->addLayout(rightLayout);

    connect(openBtn, SIGNAL(clicked()), this, SLOT(openBtnResponded()));
    connect(closeBtn, SIGNAL(clicked()), this, SLOT(closeBtnResponded()));
    connect(captureBtn, SIGNAL(clicked()), this, SLOT(captureBtnResponded()));
    connect(saveBtn, SIGNAL(clicked()), this, SLOT(saveBtnResponded()));
    connect(exitBtn, SIGNAL(clicked()), this, SLOT(exitBtnResponded()));
    (void)QObject::connect(cameraImageCapture, SIGNAL(imageCaptured(int, QImage)), this, SLOT(cameraImageCaptured(int, QImage)));

    centralWidget()->setLayout(mainlayout);
}

void MainWindow::openBtnResponded()
{
    qDebug() << comboBox->currentIndex();   //camera index
    qDebug() << comboBox->currentText();    //camera name
    //获取到要打开的设备的名称
    QCameraInfo CameraInfo = cameraList.at(comboBox->currentIndex());
    camera->start();
}

void MainWindow::closeBtnResponded()
{
    camera->stop();
}

void MainWindow::captureBtnResponded()
{
    cameraImageCapture->capture();
}

void MainWindow::saveBtnResponded()
{
    const QPixmap *pixmap = displayLabel->pixmap();
    if (pixmap) {
        pixmap->save("./a.jpg");
    }
}

void MainWindow::exitBtnResponded()
{
    camera->stop();
    this->close();
}

void MainWindow::cameraImageCaptured(int id, QImage image)
{
    qDebug("%d", id);
    //qDebug() << id << endl;
    displayLabel->setPixmap(QPixmap::fromImage(image));
}














MainWindow::~MainWindow()
{
    delete ui;
}

