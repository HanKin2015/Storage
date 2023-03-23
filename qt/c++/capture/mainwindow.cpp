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
    , cameraImageCapture(NULL)
    , isExit(true)
{
    ui->setupUi(this);
    cameraLog("摄像头工具打开");
    Init();
    //InitLayout();
}

// 废弃的函数
void MainWindow::InitLayout()
{
    this->setWindowTitle("摄像头工具");  // 窗口名称
    this->resize(640, 480);             // 窗口大小
    this->setWindowIcon(QIcon(APP_LOGO_FILE_PATH)); // 图标

    // 创建帮助菜单
    QMenu *help_menu = ui->menubar->addMenu(tr("help(&H)"));
    QAction *document_action = help_menu->addAction(tr("&document"));
    QAction *update_log_action = help_menu->addAction(tr("&update log"));
    QAction *about_action = help_menu->addAction(tr("&about"));
    connect(about_action, SIGNAL(triggered()), this, SLOT(AboutActionClicked()));
    connect(document_action, SIGNAL(triggered()), this, SLOT(DocumentActionClicked()));
    connect(update_log_action, SIGNAL(triggered()), this, SLOT(UpdateLogActionClicked()));

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
    this->setWindowIcon(QIcon(APP_LOGO_FILE_PATH)); // 图标
    QWidget *widget = new QWidget();
    this->setCentralWidget(widget);     // 居中显示

    // 创建帮助菜单
    QMenu *help_menu = ui->menubar->addMenu(tr("help(&H)"));
    QAction *document_action = help_menu->addAction(tr("&document"));
    QAction *update_log_action = help_menu->addAction(tr("&update log"));
    QAction *about_action = help_menu->addAction(tr("&about"));
    connect(about_action, SIGNAL(triggered()), this, SLOT(AboutActionClicked()));
    connect(document_action, SIGNAL(triggered()), this, SLOT(DocumentActionClicked()));
    connect(update_log_action, SIGNAL(triggered()), this, SLOT(UpdateLogActionClicked()));

    cameraLog(QString("本地共有 %1 个摄像头").arg(QCameraInfo::availableCameras().count()));

    // 为了获取摄像头分辨率创建
    camera = new QCamera(this);
    //camera = new QCamera(cameraList.at(comboBox->currentIndex()));

    // 摄像头显示区域
    cameravierfinder = new QCameraViewfinder(this);
    camera->setViewfinder(cameravierfinder);
    cameravierfinder->resize(QSize(100, 30));
    QVBoxLayout *innerLayout = new QVBoxLayout;
    innerLayout->addWidget(cameravierfinder);
    groupBox = new QGroupBox("Camera Viewfinder");
    groupBox->setLayout(innerLayout);

    cameraList = QCameraInfo::availableCameras();
    for (int i = 0; i < cameraList.size(); i++) {
        cameraLog(QString("设备名称: %1").arg(cameraList.at(i).deviceName()));  // 获取设备名称
        cameraLog(QString("设备描述信息: %1").arg(cameraList.at(i).description())); // 设备描述信息
        cameraLog(QString("设备positon: %1").arg(cameraList.at(i).position()));
        cameraLog("###########################");
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
    cameraLog(QString("ViewfinderPixelFormats sizes.len = %1").arg(pixelFormats.length()));
    foreach (QVideoFrame::PixelFormat pixelFormat, pixelFormats) {
        cameraLog(QString("pixelFormat = %1").arg(pixelFormat));
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
    cameraLog(QString("ViewfinderResolutions sizes.len = %1").arg(resolutions.length()));
    foreach (QSize resolution, resolutions) {
        QString res = QString("%1 x %2").arg(resolution.width()).arg(resolution.height());
        cameraLog(QString("Resolution size = %1").arg(res));
        cameraResolutionCB->addItem(res);
    }
    camera->stop();
    delete camera;
    camera = NULL;
    cameravierfinder->setVisible(false);
    //qDebug() << cameravierfinder->size();

    // 摄像头操作按钮
    QPushButton *openBtn = new QPushButton("打开", this);
    QPushButton *closeBtn = new QPushButton("关闭", this);
    QPushButton *captureBtn = new QPushButton("捕获", this);
    QPushButton *saveBtn = new QPushButton("保存", this);
    baichengBtn = new QPushButton("开启白城驾考中心自动测试", this);
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
    mainlayout->addWidget(groupBox);
    mainlayout->addLayout(rightLayout);

    // 绑定事件槽函数
    connect(openBtn, SIGNAL(clicked()), this, SLOT(openBtnResponded()));
    connect(closeBtn, SIGNAL(clicked()), this, SLOT(closeBtnResponded()));
    connect(captureBtn, SIGNAL(clicked()), this, SLOT(captureBtnResponded()));
    connect(saveBtn, SIGNAL(clicked()), this, SLOT(saveBtnResponded()));
    connect(baichengBtn, SIGNAL(clicked()), this, SLOT(baichengBtnResponded()));
    connect(exitBtn, SIGNAL(clicked()), this, SLOT(exitBtnResponded()));
    centralWidget()->setLayout(mainlayout);
}

// 打开摄像头
void MainWindow::openBtnResponded()
{
    qDebug() << cameraNameCB->currentIndex();   //camera index
    qDebug() << cameraNameCB->currentText();    //camera name

    if (camera) {
        qDebug() << "state: " << camera->state();
        if (camera->state() == QCamera::ActiveState) {
            camera->stop();
        }
        delete camera;
        camera = NULL;
    }

    // 获取到要打开的设备的名称
    QCameraInfo CameraInfo = cameraList.at(cameraNameCB->currentIndex());
    camera = new QCamera(CameraInfo);
    camera->setViewfinder(cameravierfinder);
    if (!cameravierfinder->isVisible()) {
        cameravierfinder->setVisible(true);
    }
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

    //camera->setCaptureMode(QCamera::CaptureVideo);
    if (camera->isCaptureModeSupported(QCamera::CaptureStillImage)) {
        qDebug() << "Still image capture is supported";
    } else {
        qDebug() << "Still image capture is not supported";
    }
    if (camera->isCaptureModeSupported(QCamera::CaptureVideo)) {
        qDebug() << "Video capture is supported";
    } else {
        qDebug() << "Video image capture is not supported";
    }
    if (cameraImageCapture != NULL) {
        (void)QObject::disconnect(cameraImageCapture, SIGNAL(imageCaptured(int, const QImage&)), this, SLOT(onImageCaptured(int, const QImage&)));
        (void)QObject::disconnect(cameraImageCapture, SIGNAL(imageSaved(int, const QString&)), this, SLOT(onImageSaved(int, const QString&)));
    }

    if (cameraImageCapture) {
        delete cameraImageCapture;
        cameraImageCapture = NULL;
    }
    cameraImageCapture = new QCameraImageCapture(camera);
    cameraImageCapture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
    camera->setCaptureMode(QCamera::CaptureStillImage);
    (void)QObject::connect(cameraImageCapture, SIGNAL(imageCaptured(int, const QImage&)), this, SLOT(onImageCaptured(int, const QImage&)));
    (void)QObject::connect(cameraImageCapture, SIGNAL(imageSaved(int, const QString&)), this, SLOT(onImageSaved(int, const QString&)));

    statusbarFormat->setText(QString("格式: %1").arg(pixelFormatStr));
    statusbarResolution->setText(QString("分辨率: %1 x %2").arg(resolutionWidth).arg(resolutionHeight));
}

// 关闭按钮槽函数
void MainWindow::closeBtnResponded()
{
    cameraLog("点击关闭按钮");
    camera->stop();
    cameravierfinder->setVisible(false);
    //cameravierfinder->hide();
}

// 捕获按钮槽函数
void MainWindow::captureBtnResponded()
{
    cameraLog("点击捕获按钮");
    cameraImageCapture->capture();
}

// 保存按钮槽函数
void MainWindow::saveBtnResponded()
{
    cameraLog("点击保存按钮");
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

// 判断设备是否存在
bool MainWindow::deviceExist(const QCameraInfo &cameraInfo) const
{
    QList<QCameraInfo> cameraInfoList = QCameraInfo::availableCameras();
    for (int i = 0; i < cameraInfoList.count(); i++) {
        if (cameraInfo.deviceName() == cameraInfoList.at(i).deviceName())
            return true;
    }

    return false;
}

// 日志打印
void MainWindow::cameraLog(QString msg)
{
    // 同时打印在窗口
    qDebug("%s", msg.toStdString().c_str());
    //qDebug() << msg << endl;

    // 创建文件对象
    QFile file(APP_LOG_FILE_PATH);

    // 打开文件，追加写方式
    bool openOk = file.open(QIODevice::Append);
    if (openOk) {
        // 创建数据流，和file文件关联
        // 往数据流中写数据，相当于往文件里写数据
        QTextStream stream(&file);

        //指定编码
        stream.setCodec("UTF-8");

        QDateTime dateTime;
        dateTime = QDateTime::currentDateTime();

        stream << dateTime.toString("yyyy-MM-dd hh:mm:ss ddd") << " [DEBUG]: " << msg << endl;
        file.close();
    }
}

// 白城驾考中心按钮槽函数
void MainWindow::baichengBtnResponded()
{
    if (!isExit) {
        baichengBtn->setText("开启白城驾考中心自动测试");
        cameraLog("白城驾考中心自动测试结束");
        cameravierfinder->setVisible(false);
        isExit = true;
    } else {
        baichengBtn->setText("关闭白城驾考中心自动测试");
        isExit = false;
        cameraLog("白城驾考中心自动测试开始");
        if (!cameravierfinder->isVisible()) {
            cameravierfinder->setVisible(true);
        }
        camera->start();
        statusbarBaiCheng->setText(QString("白城计数: 0"));
    }

    // 获取到要打开的设备的名称
    QCameraInfo CameraInfo = cameraList.at(cameraNameCB->currentIndex());
    QVideoFrame::PixelFormat pixelFormat = QVideoFrame::Format_YUYV;
    QList<QSize> resolutions = {QSize(160, 120), QSize(320, 240), QSize(160,120)};
    long long taskCount = 0;
    bool isAbnormal = false;
    // 如果写成true会在窗口关闭后一直在执行（任务管理器依然存在进程，并且exe文件删除不掉），正常退出会有exited with code 0字样
    while (!isExit) {
        qDebug() << camera->status() << ' ' << camera->state();
        if (taskCount % 1000 == 0) {
            // 一段时间后打印一次当前摄像头状态
            cameraLog(QString("taskCount: %1, status: %2, state: %3").arg(taskCount).arg(camera->status()).arg(camera->state()));
        }
        if (camera->status() == QCamera::UnloadedStatus || camera->status() == QCamera::UnavailableStatus) {
            // 记录第一次异常时间点
            if (!isAbnormal) {
                cameraLog(QString("摄像头出现异常状态taskCount: %1, status: %2, state: %3").arg(taskCount).arg(camera->status()).arg(camera->state()));
                isAbnormal = true;
            }

            if (deviceExist(CameraInfo)) {
                camera->stop();
                camera->start();
                cameraLog(QString("摄像头异常状态恢复, 恢复之前taskCount: %1, status: %2, state: %3").arg(taskCount).arg(camera->status()).arg(camera->state()));
                isAbnormal = false; // 恢复异常
            } else {
                if (camera->status() == QCamera::ActiveStatus) {
                    camera->stop();
                    camera->unload();
                }
            }
        }

        QCameraViewfinderSettings set;
        set.setPixelFormat(pixelFormat);    // 设置摄像头格式

        for (int i = 0; i < resolutions.size(); i++) {
            set.setResolution(resolutions.at(i).width(), resolutions.at(i).height());
            camera->setViewfinderSettings(set); // 设置摄像头分辨率

            // 更新状态栏
            QString cameraName = cameraNameCB->currentText();
            statusbarName->setText(QString("名称: %1").arg(cameraName));
            QString pixelFormatStr = "Format_YUYV";
            statusbarFormat->setText(QString("格式: %1").arg(pixelFormatStr));
            statusbarResolution->setText(QString("分辨率: %1 x %2").arg(resolutions.at(i).width()).arg(resolutions.at(i).height()));

            if (i == resolutions.size() - 1) {
                sleep(3000);    // 睡眠3秒
            } else {
                sleep(1000);    // 睡眠1秒
            }
        }
        taskCount++;
        statusbarBaiCheng->setText(QString("白城计数: %1").arg(taskCount));
    }
    if (camera->state() == QCamera::ActiveState) {
        camera->stop();
    }
}

// 退出按钮槽函数
void MainWindow::exitBtnResponded()
{
    this->close();  // 会调用退出事件closeEvent
}

void MainWindow::onImageCaptured(int id, const QImage image)
{
    cameraLog("收到捕获消息信号，开始捕获图像");
    qDebug("%d", id);
    //qDebug() << id << endl;
    displayLabel->setPixmap(QPixmap::fromImage(image));
}

void MainWindow::onImageSaved(int id, const QString content)
{
    cameraLog("收到保存消息信号，开始保存图像");
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 重写退出事件
void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox close_mb(QMessageBox::Warning, "",tr("Are you sure exit?"));
    //close_mb.setWindowTitle("你舍得离开吗");
    close_mb.setWindowFlag(Qt::FramelessWindowHint);
    close_mb.setAttribute(Qt::WA_ShowModal, true);

    close_mb.setStandardButtons(QMessageBox::Ok|QMessageBox::Cancel);
    close_mb.setButtonText (QMessageBox::Ok,QString(tr("yes")));
    close_mb.setButtonText (QMessageBox::Cancel,QString(tr("no")));
    if(close_mb.exec() == QMessageBox::Ok)
    {
        if (camera) {
            if (camera->status() == QCamera::ActiveStatus) {
                camera->stop();
                camera->unload();
            }
            delete camera;
            camera = NULL;
        }
        isExit = true;
        event->accept();
        cameraLog("摄像头工具关闭");
    }
    else
    {
        event->ignore();
    }
    return ;
}
