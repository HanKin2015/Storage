#include "usbmanagement.h"

USBManagement::USBManagement()
{
    SetupUI();

    // 应用qss视觉效果
    QFile* qssFile = new QFile("://qss/style.qss");
    qssFile->open(QFile::ReadOnly);
    QString styleSheet = QString(qssFile->readAll());
    mManagerWidget->setStyleSheet(styleSheet);
    qssFile->close();
    delete qssFile;
}
USBManagement::~USBManagement()
{

}

class ManagerTitleBar {
public:
    ManagerTitleBar()
    {
        mTitleBarWidget = new QWidget();
        mTitleBarWidget->setObjectName("managerTitleBarWidget");
        QHBoxLayout *mTitleBarLayout = new QHBoxLayout();
        QLabel *mTitleLabel = new QLabel(QObject::tr("USB设备管理"));

        mTitleBarLayout->addWidget(mTitleLabel);
        mTitleBarWidget->setLayout(mTitleBarLayout);
    }
    ~ManagerTitleBar(){}

    /**
     * @brief 获取标题栏主界面组件引用
     *
     * @return QWidget* 标题栏主界面组件引用
     */
    QWidget* GetMainWidget() { return mTitleBarWidget; }

private:
    QWidget *mTitleBarWidget;
};

class USBDevicePanel {
public:
    USBDevicePanel(USBManagement* manager)
    {
        Q_UNUSED(manager);
        mPanelArea = new QScrollArea();
        mPanelArea->setObjectName("scrollUSBDevicePanelArea");
        // 随内容物大小而放大缩小
        mPanelArea->setWidgetResizable(true);
        mPanelArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mPanelContent = new QWidget();
        mPanelContent->setObjectName("usbDevicePanelContentWidget");
        mPanelLayout = new QVBoxLayout();

        mPanelLayout->setDirection(QBoxLayout::TopToBottom);

        // 添加设备
        std::vector<std::string> mAllowedSession;
        USBDeviceMappingData mapping = {"phone", "1234", "abcd", "2025", "11111", mAllowedSession, "123"};
        QList<USBDeviceMappingData> mUsbDeviceMappingsData;     //usb设备信息及其映射关系
        mUsbDeviceMappingsData.append(mapping);
        mUsbDeviceMappingsData.append(mapping);
        for (int i = 0; i < mUsbDeviceMappingsData.size(); i++) {
            USBDeviceItem *usbDeviceItem = new USBDeviceItem(mUSBDeviceManager, mUsbDeviceMappingsData.at(i));
            mPanelLayout->addWidget(usbDeviceItem->GetMainWidget());
            mPanelLayout->setAlignment(Qt::AlignTop);
        }

        mPanelContent->setLayout(mPanelLayout);
        mPanelArea->setWidget(mPanelContent);
    }
    ~USBDevicePanel();

public:
    QWidget* GetMainWidget() {return mPanelArea;}

    /**
     * @brief 刷新设备映射信息盘
     *
     * @return int 0：成功，其他：失败
     */
    int ReFreshDevicePanel();
    int ShowEmptyPanel();

    //QList<USBDeviceItem*> *GetDeviceItemData() { return &mUsbDevices;}

private:
    //UI
    QScrollArea* mPanelArea;
    QWidget* mPanelContent;
    QVBoxLayout* mPanelLayout;
    bool mNoUSBDeviceItem;

    QLabel* mEmptyIconLable;
    QLabel* mEmptyTextLabel;

    QList<USBDeviceItem *> mUsbDevices;  /// 每条设备信息及其映射关系

    USBManagement *mUSBDeviceManager;
};

int USBDeviceItem::ReFreshDeviceMapping()
{
    std::vector<AppData*> mApps;
    AppData mApp = {"qq", "://images/head.jpeg"};
    mApps.push_back(&mApp);
    mApps.push_back(&mApp);
    AppGroupData appGroupData = {"本地PC", "远程应用组", mApps};

    AppGroup* group = NULL;
    for (int i = 1; i < 4; i++) {   // 整个服务器
        group = new AppGroup(mUSBDeviceManager, mButtonGroup, i-1);
        appGroupData.mGroupName = "远程应用组" + std::to_string(i);
        mAppGroupsData.append(appGroupData);

        // 打开的远程应用
        group->mGroupHandler->setText(QString::fromStdString(appGroupData.mGroupName));
        int appNum = appGroupData.mApps.size();
        QListWidgetItem* item = NULL;
        for (int i = 0; i < appNum; i++) {
            item = new QListWidgetItem(QIcon(QString::fromStdString(appGroupData.mApps[i]->mAppIconFile)),
                                   QString::fromStdString(appGroupData.mApps[i]->mAppName), group->mAppList);
            item->setToolTip(QString::fromStdString(appGroupData.mApps[i]->mAppName));
            //该数字根据视觉稿和实际效果调整
            item->setSizeHint(QSize(120, 60));
            group->mAppListItems.push_back(item);
        }

        mAppGroups.append(group);
        mDeviceBodyLayout->addWidget(group->GetMainWidget(), i / 2, i % 2, Qt::AlignLeft | Qt::AlignTop);
    }

    return 0;
}

int USBManagement::SetupUI()
{
    //QDesktopWidget *desktop = QApplication::desktop();
    //int width = (desktop->screenGeometry(desktop->primaryScreen()).width() - mManagerWidget->width()) / 2;
    //int height = (desktop->screenGeometry(desktop->primaryScreen()).height() -mManagerWidget->height()) / 2;
    // 获取主屏幕
    QScreen *screen = QGuiApplication::primaryScreen();
    if (screen == NULL) {
        qDebug() << "get main screen failed" << endl;
        return -1;
    }
    // 获取屏幕的尺寸
    QRect screenGeometry = screen->geometry();

    mFullScreenMaskWidget = new QWidget();
    // 底层全屏蒙版窗口，去掉标题栏，透明 Qt::X11BypassWindowManagerHint | Qt::WindowTransparentForInput
    mFullScreenMaskWidget->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::Window);
    mFullScreenMaskWidget->setAttribute(Qt::WA_TranslucentBackground, true);    // 默认为true，透明背景
    mFullScreenMaskWidget->setAttribute(Qt::WA_NoSystemBackground, true);       // 默认为true，允许系统背景
    //mFullScreenMaskWidget->setAttribute(Qt::WA_TransparentForMouseEvents, false); // 确保窗口可以接收鼠标事件

    // 设置背景颜色
    //mFullScreenMaskWidget->setStyleSheet("background-color: rgba(0, 0, 0, 150);"); // 半透明黑色背景

    // 创建一个透明覆盖层的 QWidget 用于接收鼠标事件
    QWidget *transparentOverlay = new QWidget(mFullScreenMaskWidget);
    transparentOverlay->setAttribute(Qt::WA_TransparentForMouseEvents, true); // 允许接收鼠标事件
    transparentOverlay->setStyleSheet("background-color: rgba(0, 0, 0, 0.1);"); // 微透明
    //transparentOverlay->setGeometry(mFullScreenMaskWidget->rect()); // 设置大小与蒙版窗口相同
    transparentOverlay->setGeometry(screenGeometry);
    transparentOverlay->show();

    mManagerWidget = new QWidget(mFullScreenMaskWidget);
    // 该大小由视觉稿定义
    mManagerWidget->setMinimumSize(800, 540);
    mManagerWidget->setMaximumSize(800, 540);

    mManagerLayout = new QVBoxLayout();
    ManagerTitleBar *mTitleBar = new ManagerTitleBar();
    mTipsLabel = new QLabel(QObject::tr("请选择接入位置："));
    mTipsLabel->setObjectName("tipsLable");
    mPlaceHolder = new QLabel();
    mPlaceHolder->setStyleSheet("{background-color: rgba(10, 10, 230, 150);}");

    USBDevicePanel *mDevicePanel = new USBDevicePanel(this);

    QWidget *mControlArea = new QWidget();
    mControlArea->setObjectName("bottomControlArea");
    QHBoxLayout *mAreaLayout = new QHBoxLayout();
    mAreaLayout->setAlignment(Qt::AlignRight);
    mAreaLayout->setContentsMargins(11, 11, 20, 11);

    // OK button
    QPushButton *mOKButton = new QPushButton(QObject::tr("OK"));
    mOKButton->setObjectName("okButton");
    QObject::connect(mOKButton, SIGNAL(clicked()), this, SLOT(OkButtonClicked()));
    QSize size = mOKButton->sizeHint();
    // resize
    mOKButton->setMinimumSize(size.width() * 1.7, size.height());
    size = mOKButton->sizeHint();

    // cancel button
    QPushButton *mCancelButton = new QPushButton(QObject::tr("Cancel"));
    mCancelButton->setObjectName("cancelButton");
    QObject::connect(mCancelButton, SIGNAL(clicked()), this, SLOT(CancelButtonClicked()));
    size = mCancelButton->sizeHint();
    mCancelButton->setMinimumSize(size.width() * 1.7, size.height());
    size = mCancelButton->sizeHint();

    // main
    mAreaLayout->addWidget(mOKButton);
    mAreaLayout->addWidget(mCancelButton);
    mControlArea->setLayout(mAreaLayout);

   // 这里可以使用屏幕尺寸进行布局等操作
    int width = (screenGeometry.width() - mManagerWidget->width()) / 2;
    int height = (screenGeometry.height() - mManagerWidget->height()) / 2;
    mManagerWidget->move(width, height);

    mManagerLayout->setSpacing(0);
    mManagerLayout->setContentsMargins(11, 0, 11, 0);
    mManagerLayout->addWidget(mTitleBar->GetMainWidget());
    mManagerLayout->addWidget(mTipsLabel);
    mManagerLayout->addWidget(mPlaceHolder);
    mTipsLabel->show();
    mPlaceHolder->hide();
    mManagerLayout->addWidget(mDevicePanel->GetMainWidget());
    mManagerLayout->addWidget(mControlArea);
    mManagerWidget->setLayout(mManagerLayout);
    mManagerWidget->setObjectName("managerMainWidget");
    mManagerWidget->setWindowFlags(Qt::X11BypassWindowManagerHint | Qt::FramelessWindowHint);

    // 根据需求，模态显示
    mFullScreenMaskWidget->setWindowModality(Qt::ApplicationModal);
    mManagerWidget->setAutoFillBackground(false);
    //mManagerWidget->hide();
    //mFullScreenMaskWidget->hide();

    // 移到屏幕中央
    mManagerWidget->move(width, height);
    mManagerWidget->show();

    //每次显示时都将底层全屏蒙版铺满全屏
    mFullScreenMaskWidget->resize(screenGeometry.width(), screenGeometry.height());
    mFullScreenMaskWidget->move(screenGeometry.x(), screenGeometry.y());
    mFullScreenMaskWidget->show();
    return 0;

}

