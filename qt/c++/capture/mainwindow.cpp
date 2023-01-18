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
#include <QThread>
#include <QTime>

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
    this->setWindowTitle("摄像头工具");
    this->resize(640, 480);

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
    this->setWindowTitle("摄像头工具");  // 窗口名称
    this->resize(640, 480);             // 窗口大小
    QWidget *widget = new QWidget();
    this->setCentralWidget(widget);     // 居中显示

    qDebug("本地共有%d个摄像头。", QCameraInfo::availableCameras().count());

    camera = new QCamera(this);
    //camera = new QCamera(cameraList.at(comboBox->currentIndex()));
    camera->setCaptureMode(QCamera::CaptureStillImage);
    cameraImageCapture = new QCameraImageCapture(camera);
    cameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);

    // 摄像头显示区域
    cameravierfinder = new QCameraViewfinder(this);
    camera->setViewfinder(cameravierfinder);

    cameraList = QCameraInfo::availableCameras();
    for (int i = 0; i < cameraList.size(); i++) {
        qDebug() << cameraList.at(i).deviceName();  // 获取设备名称
        qDebug() << cameraList.at(i).description(); // 设备描述信息
        qDebug() << cameraList.at(i).position();
        qDebug() << "###############";
    }
    for (QList<QCameraInfo>::iterator it = cameraList.begin(); it != cameraList.end(); it++) {
        qDebug("device name : %s", qPrintable(it->deviceName()));
        qDebug("device description : %s", qPrintable(it->description()));
        qDebug("device position : %d", it->position());
    }

    // 摄像头名称下拉框
    cameraNameCB = new QComboBox();
    foreach (QCameraInfo cameraInfo, cameraList) {
        cameraNameCB->addItem(cameraInfo.description());
    }

    // 摄像头格式下拉框
    cameraFormatCB = new QComboBox();
    camera->start();
    pixelFormats = camera->supportedViewfinderPixelFormats();
    qDebug() << "ViewfinderPixelFormats sizes.len = " << pixelFormats.length();
    foreach (QVideoFrame::PixelFormat pixelFormat, pixelFormats) {
        qDebug() << "pixelFormat = " << pixelFormat;
        QString pixelFormatStr = "";
        switch (pixelFormat) {
        case QVideoFrame::Format_Jpeg:
            pixelFormatStr = "Format_Jpeg";
            break;
        case QVideoFrame::Format_YUYV:
            pixelFormatStr = "Format_YUYV";
            break;
        default:
            break;
        }
        cameraFormatCB->addItem(pixelFormatStr);
    }

    // 摄像头分辨率下拉框
    cameraResolutionCB = new QComboBox();
    resolutions = camera->supportedViewfinderResolutions();
    qDebug() << "ViewfinderResolutions sizes.len = " << resolutions.length();
    foreach (QSize resolution, resolutions) {
        qDebug() << "Resolution size = " << resolution;
        QString res = QString("%1 x %2").arg(resolution.width()).arg(resolution.height());
        cameraResolutionCB->addItem(res);
    }
    camera->stop();

    // 摄像头操作按钮
    QPushButton *openBtn = new QPushButton("打开", this);
    QPushButton *closeBtn = new QPushButton("关闭", this);
    QPushButton *captureBtn = new QPushButton("捕获", this);
    QPushButton *saveBtn = new QPushButton("保存", this);
    QPushButton *baichengBtn = new QPushButton("白城驾考中心", this);
    QPushButton *exitBtn = new QPushButton("退出", this);

    // 摄像头捕获区域
    displayLabel = new QLabel(this);
    displayLabel->setFixedSize(150, 150);
    displayLabel->setScaledContents(true);

    // 状态栏显示当前摄像头名称、分辨率和格式
    statusbarName = new QLabel("名称: null",this);
    statusbarName->setMinimumWidth(150);
    statusbarFormat = new QLabel("格式: null",this);
    statusbarFormat->setMinimumWidth(150);
    statusbarResolution = new QLabel("分辨率: null",this);
    statusbarResolution->setMinimumWidth(150);
    statusbarBaiCheng = new QLabel("白城计数: 0", this);
    statusbarBaiCheng->setMinimumWidth(150);
    ui->statusbar->addWidget(statusbarName);
    ui->statusbar->addWidget(statusbarFormat);
    ui->statusbar->addWidget(statusbarResolution);
    ui->statusbar->addWidget(statusbarBaiCheng);

    QVBoxLayout *rightLayout = new QVBoxLayout();
    rightLayout->addWidget(displayLabel);
    rightLayout->addWidget(cameraNameCB);
    rightLayout->addWidget(cameraFormatCB);
    rightLayout->addWidget(cameraResolutionCB);
    rightLayout->addWidget(openBtn);
    rightLayout->addWidget(closeBtn);
    rightLayout->addWidget(captureBtn);
    rightLayout->addWidget(saveBtn);
    rightLayout->addWidget(baichengBtn);
    rightLayout->addWidget(exitBtn);

    //
    mainlayout = new QHBoxLayout();
    mainlayout->addWidget(cameravierfinder);
    mainlayout->addLayout(rightLayout);

    // 绑定事件槽函数
    connect(openBtn, SIGNAL(clicked()), this, SLOT(openBtnResponded()));
    connect(closeBtn, SIGNAL(clicked()), this, SLOT(closeBtnResponded()));
    connect(captureBtn, SIGNAL(clicked()), this, SLOT(captureBtnResponded()));
    connect(saveBtn, SIGNAL(clicked()), this, SLOT(saveBtnResponded()));
    connect(baichengBtn, SIGNAL(clicked()), this, SLOT(baichengBtnResponded()));
    connect(exitBtn, SIGNAL(clicked()), this, SLOT(exitBtnResponded()));
    (void)QObject::connect(cameraImageCapture, SIGNAL(imageCaptured(int, QImage)), this, SLOT(cameraImageCaptured(int, QImage)));

    centralWidget()->setLayout(mainlayout);
}

// 打开摄像头
void MainWindow::openBtnResponded()
{
    qDebug() << cameraNameCB->currentIndex();   //camera index
    qDebug() << cameraNameCB->currentText();    //camera name

    // 获取到要打开的设备的名称
    QCameraInfo CameraInfo = cameraList.at(cameraNameCB->currentIndex());
    qDebug() << "state: " << camera->state();
    //if (camera->state() == QCamera::ActiveState) {
    //    camera->stop();
    //}
    camera->start();
    qDebug() << "state: " << camera->state();

    QString cameraName = cameraNameCB->currentText();
    int resolutionWidth = resolutions.at(cameraResolutionCB->currentIndex()).width();
    int resolutionHeight = resolutions.at(cameraResolutionCB->currentIndex()).height();
    QVideoFrame::PixelFormat pixelFormat = pixelFormats.at(cameraFormatCB->currentIndex());

    QCameraViewfinderSettings set;
    set.setResolution(resolutionWidth, resolutionHeight);
    set.setPixelFormat(pixelFormat);
    camera->setViewfinderSettings(set);
    qDebug() << resolutionWidth << resolutionHeight << pixelFormat << endl;

    // 更新状态栏
    statusbarName->setText(QString("名称: %1").arg(cameraName));
    QString pixelFormatStr = "";
    switch (pixelFormat) {
    case QVideoFrame::Format_Jpeg:
        pixelFormatStr = "Format_Jpeg";
        break;
    case QVideoFrame::Format_YUYV:
        pixelFormatStr = "Format_YUYV";
        break;
    default:
        break;
    }
    statusbarFormat->setText(QString("格式: %1").arg(pixelFormatStr));
    statusbarResolution->setText(QString("分辨率: %1 x %2").arg(resolutionWidth).arg(resolutionHeight));
}

void MainWindow::closeBtnResponded()
{
    camera->stop();
}

void MainWindow::captureBtnResponded()
{
    cameraImageCapture->capture();
}

// 保存按钮槽函数
void MainWindow::saveBtnResponded()
{
    const QPixmap *pixmap = displayLabel->pixmap();
    if (pixmap) {
        pixmap->save("./capture.jpg");
    }
}

bool MainWindow::sleep(unsigned int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    return true;
}

// 白城驾考中心按钮槽函数
void MainWindow::baichengBtnResponded()
{
    QVideoFrame::PixelFormat pixelFormat = QVideoFrame::Format_YUYV;
    QList<QSize> resolutions = {QSize(160, 120), QSize(320, 240), QSize(160,120)};

    camera->start();
    int taskCount = 0;
    while (true) {
        QCameraViewfinderSettings set;
        set.setPixelFormat(pixelFormat);

        for (int i = 0; i < resolutions.size(); i++) {
            set.setResolution(resolutions.at(i).width(), resolutions.at(i).height());
            camera->setViewfinderSettings(set);

            // 更新状态栏
            QString cameraName = cameraNameCB->currentText();
            statusbarName->setText(QString("名称: %1").arg(cameraName));
            QString pixelFormatStr = "Format_YUYV";
            statusbarFormat->setText(QString("格式: %1").arg(pixelFormatStr));
            statusbarResolution->setText(QString("分辨率: %1 x %2").arg(resolutions.at(i).width()).arg(resolutions.at(i).height()));

            if (i == resolutions.size() - 1) {
                sleep(60000);   // 睡眠60秒
            } else {
                sleep(1000);    // 睡眠1秒
            }
        }
        taskCount++;
        statusbarBaiCheng->setText(QString("白城计数: %1").arg(taskCount));
    }
}

// 退出按钮槽函数
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

