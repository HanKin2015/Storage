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
#include <fstream>
#include <sstream>

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

// 获取摄像头指定格式分辨率
#if 1
void  MainWindow::getResolutions(QCamera *camera, QVideoFrame::PixelFormat pixelFormat)
{
    qDebug("%s:%d", __FUNCTION__, __LINE__);

    // 获取要打开的设备的名称
    QCameraInfo CameraInfo = cameraList.at(cameraNameCB->currentIndex());
    if (!camera) {
        camera = new QCamera(CameraInfo);
    }

    camera->start();
    // 获取摄像头支持的视图设置
    QList<QCameraViewfinderSettings> viewfinderSettings = camera->supportedViewfinderSettings();

    resolution_list.clear();
    // 遍历视图设置列表，找到指定格式的分辨率
    foreach (const QCameraViewfinderSettings& settings, viewfinderSettings)
    {
        // 指定需要的格式，例如：QVideoFrame::Format_RGB32
        if (settings.pixelFormat() == pixelFormat)
        {
            // 获取分辨率
            QSize resolution = settings.resolution();
            //qDebug() << "Resolution: " << resolution.width() << "x" << resolution.height();
            resolution_list.append(resolution);
        }
    }
    camera->stop();
    delete camera;
    camera = NULL;
    return;
}
#endif

#if 0
// 没有想通为何不行
void MainWindow::getResolutions(QCamera *camera, QVideoFrame::PixelFormat pixelFormat)
{
    qDebug("%s:%d", __FUNCTION__, __LINE__);

    // 获取要打开的设备的名称
    QCameraInfo CameraInfo = cameraList.at(cameraNameCB->currentIndex());
    if (!camera) {
        camera = new QCamera(CameraInfo);
    }

    camera->start();
    QCameraViewfinderSettings set;
    qDebug("pixelFormat = %d", pixelFormat);
    set.setPixelFormat(pixelFormat);
    camera->setViewfinderSettings(set);

    resolution_list = camera->supportedViewfinderResolutions();
    qDebug("resolution_list size = %d", resolution_list.size());
    camera->stop();
    delete camera;
    camera = NULL;
    return;
}
#endif

// 格式变化随之分辨率列表变化
void MainWindow::comboBoxIndexChanged(int index)
{
    QComboBox *comboBox = qobject_cast<QComboBox*>(sender());
    if (comboBox) {
        QString selectedText = comboBox->currentText();
        qDebug() << "下拉框改变，当前选中的文本为：" << selectedText;
    }

    qDebug() << "下拉框改变，当前选中的索引为：" << index;

    getResolutions(camera, pixelFormats.at(index));
    cameraResolutionCB->clear();
    foreach (QSize resolution, resolution_list) {
        QString res = QString("%1 x %2").arg(resolution.width()).arg(resolution.height());
        cameraLog(QString("Resolution size = %1").arg(res));
        cameraResolutionCB->addItem(res);
    }
}

void MainWindow::Init()
{
    //https://blog.csdn.net/weixin_44307528/article/details/104766533
    this->setWindowTitle("摄像头工具20240513");     // 窗口名称
    this->resize(640, 480);                         // 窗口大小
    this->setWindowIcon(QIcon(APP_LOGO_FILE_PATH)); // 图标
    QWidget *widget = new QWidget();
    this->setCentralWidget(widget);                 // 居中显示

    // 创建帮助菜单
    QMenu *help_menu = ui->menubar->addMenu(tr("帮助(&H)"));
    QAction *document_action = help_menu->addAction(tr("&文档"));
    QAction *update_log_action = help_menu->addAction(tr("&更新日志"));
    QAction *about_action = help_menu->addAction(tr("&关于"));
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
        cameraLog(QString("pixelFormat = %1 %2").arg(pixelFormat).arg(pixelFormatStr));
        cameraFormatCB->addItem(pixelFormatStr);
    }
    connect(cameraFormatCB, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::comboBoxIndexChanged);

    // 摄像头分辨率下拉框
    cameraResolutionCB = new QComboBox();
    resolution_list = camera->supportedViewfinderResolutions();
    cameraLog(QString("ViewfinderResolutions sizes.len = %1").arg(resolution_list.length()));
    foreach (QSize resolution, resolution_list) {
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
    autoSwitchBtn = new QPushButton("开启自动切换分辨率测试", this);
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
    statusbarBaiCheng = new QLabel("切换次数: 0", this);
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
    rightLayout->addWidget(autoSwitchBtn);
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
    connect(autoSwitchBtn, SIGNAL(clicked()), this, SLOT(autoSwitchBtnResponded()));
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

    // 获取要打开的设备的名称
    QCameraInfo CameraInfo = cameraList.at(cameraNameCB->currentIndex());
    camera = new QCamera(CameraInfo);
    camera->setViewfinder(cameravierfinder);
    if (!cameravierfinder->isVisible()) {
        cameravierfinder->setVisible(true);
    }
    camera->start();
    qDebug() << "state: " << camera->state();

    QString cameraName = cameraNameCB->currentText();
    int resolutionWidth = resolution_list.at(cameraResolutionCB->currentIndex()).width();
    int resolutionHeight = resolution_list.at(cameraResolutionCB->currentIndex()).height();
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

std::string trim(const std::string& str) {
    std::string temp(str);
    // 去除开头的空格
    temp.erase(temp.begin(), std::find_if(temp.begin(), temp.end(), [](unsigned char ch) { return !std::isspace(ch); }));
    // 去除结尾的空格
    temp.erase(std::find_if(temp.rbegin(), temp.rend(), [](unsigned char ch) {return !std::isspace(ch); }).base(), temp.end());
    return temp;
}

class IniReader {
public:
    IniReader(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        std::string section;
        if (file.is_open()) {
            while (std::getline(file, line)) {
                line = trim(line);
                if (line.empty() || line[0] == ';' || line[0] == '#') {
                    // 忽略空行和注释
                    continue;
                }
                if (line[0] == '[') {
                    // 处理段落
                    auto endPos = line.find(']');
                    if (endPos != std::string::npos) {
                        section = trim(line.substr(1, endPos - 1));
                    }
                } else {
                    // 处理键值对
                    auto delimPos = line.find('=');
                    if (delimPos != std::string::npos) {
                        auto key = trim(line.substr(0, delimPos));
                        auto value = trim(line.substr(delimPos + 1));
                        data[section][key] = value;
                    }
                }
            }
            file.close();
        }
    }

    std::string operator[](const std::string& sectionAndKey) const {
        auto sectionEnd = sectionAndKey.find(':');
        std::string section = sectionAndKey.substr(0, sectionEnd);
        std::string key = sectionAndKey.substr(sectionEnd + 1);
        auto it = data.find(section);
        if (it != data.end()) {
            auto it2 = it->second.find(key);
            if (it2 != it->second.end()) {
                return it2->second;
            }
        }
        return "";
    }

private:
    std::map<std::string, std::map<std::string, std::string>> data;
};

std::vector<std::string> split(const std::string& str, char delimiter)
{
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// 自动切换指定格式的分辨率按钮槽函数
void MainWindow::autoSwitchBtnResponded()
{
    qDebug("autoSwitchBtnResponded start");
    IniReader iniReader(".\\cfg\\automated_configuration.ini");

    std::string resolutions = iniReader["setting:resolutions"];
    int log_interval = std::stoi(iniReader["setting:log_interval"]);
    int interval = std::stoi(iniReader["setting:interval"]);
    std::string format = iniReader["setting:format"];
    qDebug("resolutions = %s\n", resolutions.c_str());
    qDebug("%d %d %s\n", log_interval, interval, format.c_str());

    if (!isExit) {
        autoSwitchBtn->setText("开启自动切换分辨率测试");
        cameraLog("自动切换分辨率测试结束");
        cameravierfinder->setVisible(false);
        isExit = true;
    } else {
        autoSwitchBtn->setText("关闭自动切换分辨率测试");
        isExit = false;
        cameraLog("自动切换分辨率测试开始");
        if (!cameravierfinder->isVisible()) {
            cameravierfinder->setVisible(true);
        }
        statusbarBaiCheng->setText(QString("切换次数: 0"));
        if (camera) {
            camera->start();
        }
    }

    // 获取要打开的设备的名称
    QCameraInfo CameraInfo = cameraList.at(cameraNameCB->currentIndex());
    if (!camera) {
        camera = new QCamera(CameraInfo);
        camera->setViewfinder(cameravierfinder);
        if (!cameravierfinder->isVisible()) {
            cameravierfinder->setVisible(true);
        }
    }
    QVideoFrame::PixelFormat pixelFormat = QVideoFrame::Format_Invalid;
    if (format == "Format_Jpeg") pixelFormat = QVideoFrame::Format_Jpeg;
    else if (format == "Format_YUYV") pixelFormat = QVideoFrame::Format_YUYV;
    QList<QSize> resolution_list;
    std::vector<std::string> result = split(resolutions, ',');
    for (const auto& token : result) {
        int height = 0, width = 0;
        sscanf(token.data(), "%dx%d", &height, &width);
        resolution_list.append(QSize(height, width));
    }
    long long taskCount = 0;
    bool isAbnormal = false;
    // 如果写成true会在窗口关闭后一直在执行（任务管理器依然存在进程，并且exe文件删除不掉），正常退出会有exited with code 0字样
    while (!isExit) {
        qDebug() << camera->status() << ' ' << camera->state();
        if (taskCount % log_interval == 0) {
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

        for (int i = 0; i < resolution_list.size(); i++) {
            set.setResolution(resolution_list.at(i).width(), resolution_list.at(i).height());
            camera->setViewfinderSettings(set); // 设置摄像头分辨率

            // 更新状态栏
            QString cameraName = cameraNameCB->currentText();
            statusbarName->setText(QString("名称: %1").arg(cameraName));
            statusbarFormat->setText(QString("格式: %1").arg(QString::fromStdString(format)));
            statusbarResolution->setText(QString("分辨率: %1 x %2").arg(resolution_list.at(i).width()).arg(resolution_list.at(i).height()));

            sleep(interval);    // 睡眠等待
        }
        taskCount++;
        statusbarBaiCheng->setText(QString("切换次数: %1").arg(taskCount));
    }
    qDebug("autoSwitchBtnResponded end");
    /*
    自动切换分辨率测试结束
    autoSwitchBtnResponded end
    摄像头工具关闭
    autoSwitchBtnResponded end

    有时候会出现这种情况，因此需要判断camera是否为空
    */
    if (camera && camera->state() == QCamera::ActiveState) {
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
    QMessageBox close_mb(QMessageBox::Warning, "", tr("你确定要退出吗?"));
    //close_mb.setWindowTitle("你舍得离开吗");
    close_mb.setWindowFlag(Qt::FramelessWindowHint);
    close_mb.setAttribute(Qt::WA_ShowModal, true);

    close_mb.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    close_mb.setButtonText (QMessageBox::Ok, QString(tr("确定")));
    close_mb.setButtonText (QMessageBox::Cancel, QString(tr("取消")));
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
