#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "usbmanagement.h"

#define TOOLTIP_VISIBLE_ACTION "tooltip_visible_action"

class QCustomTooltip : public QWidget
{
public:
    QCustomTooltip(QToolButton *toolButton, QWidget *parent = nullptr) : QWidget(parent) {
        mToolButton = toolButton;
        setWindowFlags(Qt::Tool | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
        QVBoxLayout *layout = new QVBoxLayout(this);
        //layout->setSpacing(0);
        //layout->setMargin(0);
        QListWidget *mAppList = new QListWidget();
        mAppList->setObjectName("customTooltip");
        mAppList->setFixedSize(QSize(140, 172));
        mAppList->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        mAppList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        // 设置滚动条样式
        mAppList->setStyleSheet(
          "QScrollBar:vertical {"
          "    width: 5px;" // 设置垂直滚动条的宽度
          "    background: #f0f0f0;" // 滚动条背景色
          "}"
          "QScrollBar::handle:vertical {"
          "    background: #a0a0a0;" // 滚动条滑块颜色
          "    min-height: 10px;" // 滚动条滑块的最小高度
          "}"
          "QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {"
          "    background: none;" // 隐藏上下箭头
          "    height: 0px;" // 确保不占用空间
          "}"
          "QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {"
          "    background: none;" // 隐藏箭头
          "    height: 0px;" // 确保不占用空间
          "}"
          "QScrollBar::handle:vertical:hover {"
          "    background: #808080;" // 鼠标悬停时的滑块颜色
          "}"
          "QListWidget::item { margin-top: 4px; }"
        );
        mAppList->setViewMode(QListView::ListMode);
        mAppList->setFlow(QListView::TopToBottom);  // 以上图标下文字单行显示
        mAppList->setMovement(QListView::Static);

        for (int j = 0; j < 15; j++) {
            std::string name = "我是应用名称"+std::to_string(j+1);
            QListWidgetItem *item = new QListWidgetItem(QIcon(QString::fromStdString("://images/head.jpeg")),
                                       QString::fromStdString(name), mAppList);
            item->setSizeHint(QSize(96, 24));
        }
        mAppList->adjustSize();
        layout->addWidget(mAppList);
        setLayout(layout);
        setAttribute(Qt::WA_TranslucentBackground);

        // 初始化定时器
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &QCustomTooltip::checkMousePosition);
        timer->start(1000); // 每3秒检查一次
    }

    void showTooltip(const QString &text, const QPoint &pos) {
        QLabel *label = findChild<QLabel *>();
        if (label) {
            label->setText(text);
        }
        move(pos);
        show();
        timer->start();
    }

    void hideTooltip() {
        hide();
        timer->stop(); // 停止定时器
    }

private slots:
    void checkMousePosition() {
        // 检查鼠标是否在悬浮框上
        if (!underMouse() && !mToolButton->underMouse()) {
            hideTooltip(); // 如果不在悬浮框上，隐藏悬浮框
        }
    }

private:
    QTimer *timer; // 定时器
    QToolButton *mToolButton;
};

class QCustomListWidget : public QListWidget
{
public:
    QCustomListWidget(QWidget *parent = nullptr) : QListWidget(parent) {
        setMouseTracking(true); // 启用鼠标追踪
    }

protected:
    void mouseMoveEvent(QMouseEvent *event) override {
        QListWidget::mouseMoveEvent(event);
        // 检查鼠标是否在列表项上
        QListWidgetItem *item = itemAt(event->pos());
        if (item) {
            // 如果鼠标在项上，显示悬浮窗口
            if (item->data(Qt::UserRole).isValid()) {
                QPoint pos = QCursor::pos();
                //tooltip->showTooltip(item->data(Qt::UserRole).toString(), pos + QPoint(10, 10));
            } else {
                // 如果鼠标不在任何项上，检查是否在悬浮框上
//                if (!tooltip->isVisible() || !tooltip->underMouse()) {
//                    qDebug("%d hideTooltip", __LINE__);
//                    tooltip->hideTooltip(); // 隐藏悬浮窗口
//                }
            }
        }
    }
    void leaveEvent(QEvent *event) override {
        QListWidget::leaveEvent(event);
        // 当鼠标离开列表时，隐藏悬浮窗口
//        if (!tooltip->underMouse()) {
//            qDebug("%d hideTooltip", __LINE__);
//            tooltip->hideTooltip();
//        }
    }

//    QCustomTooltip *tooltip = new QCustomTooltip();
};


/**
 * @brief 建立起图形界面
 *
 * @return int 0：成功，其他：失败
 */
int MainWindow::SetupUI()
{
    QFile* qssFile = new QFile("://qss/style.qss");
    qssFile->open(QFile::ReadOnly);
    QString styleSheet = QString(qssFile->readAll());
    this->setStyleSheet(styleSheet);
    qssFile->close();
    delete qssFile;

    QGridLayout *mDeviceBodyLayout = new QGridLayout(); // 矩阵显示所有应用组

    for (int i = 0; i < 4; i++) {
        QRadioButton *mGroupHandler = new QRadioButton();
        //mButtonGroup->addButton(mGroupHandler, 1);
        mGroupHandler->setText(QString::fromStdString("应用组1"));

        QListWidget *mAppList = new QCustomListWidget();  // 程序组的展示程序的列表组件
        QWidget *mAppGroupContainer = new QWidget();
        QHBoxLayout *mAppGroupLayout = new QHBoxLayout(mAppGroupContainer);
        mAppGroupLayout->setMargin(0);
        mAppGroupLayout->setSpacing(0);
        mAppGroupContainer->setFixedSize(344, 60);
        mAppGroupLayout->addWidget(mAppList);

        mAppList->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mAppList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        mAppList->setViewMode(QListView::IconMode);

        mAppList->setFlow(QListView::LeftToRight);  // 以上图标下文字单行显示
        mAppList->setMovement(QListView::Static);
        //mAppList->setWrapping(false);
        // 限制icon图标大小，此处的值取自视觉稿
        mAppList->setIconSize(QSize(24, 24));
        //mAppList->setStyleSheet("border: 1px solid silver; border-color: red;");
        //mAppList->setContentsMargins(8, 0, 0, 0);

        QList<QListWidgetItem*> mAppListItems;  // 程序组内的程序列表组件
        QListWidgetItem* item = NULL;

        int appNum = 13;
        int showNum = 0, hideNum = 0;
        if (appNum > 4) {
            showNum = 4;
            hideNum = appNum - showNum;
        }
        for (int j = 0; j < showNum; j++) {
            std::string name = "name"+std::to_string(j+1);
            item = new QListWidgetItem(QIcon(QString::fromStdString("://images/head.jpeg")),
                                       QString::fromStdString(name), mAppList);
            // 设置工具提示
            item->setToolTip(QString::fromStdString(name));
            //该数字根据视觉稿和实际效果调整
            item->setSizeHint(QSize(64, 48));
            mAppListItems.push_back(item);
            // 添加一个空白项作为间隔
//            if (j != showNum - 1) { // 最后一个项后面不需要间隔
//                QListWidgetItem *spaceItem = new QListWidgetItem();
//                spaceItem->setFlags(Qt::NoItemFlags); // 设置为不可点击
//                spaceItem->setSizeHint(QSize(8, 48)); // 设置间隔的高度
//                mAppList->addItem(spaceItem);
//            }
        }
        if (hideNum > 0) {
//            QListWidgetItem *spaceItem = new QListWidgetItem();
//            spaceItem->setFlags(Qt::NoItemFlags);   // 设置为不可点击
//            spaceItem->setSizeHint(QSize(15, 48));  // 设置间隔的高度
//            mAppList->addItem(spaceItem);
//            item = new QListWidgetItem(QIcon(QString::fromStdString("://images/ellipsis.png")),
//                                       QString("等%1个").arg(hideNum), mAppList);
//            //该数字根据视觉稿和实际效果调整
//            item->setSizeHint(QSize(71, 48));
//            // 设置自定义数据，例如使用 Qt::UserRole
//            item->setData(Qt::UserRole, "ellipsis_flag");
            QToolButton *toolButton = new QToolButton();
            toolButton->setText(QString("等%1个").arg(hideNum)); // 设置按钮文本
            toolButton->setIcon(QIcon(QString::fromStdString("://images/ellipsis.png"))); // 设置按钮图标，替换为您的图标路径
            toolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);    // 文本在图标下方
            toolButton->setStyleSheet("margin-right: 13px; margin-top: 0px; border: none; background-color: red;");
            qDebug() << mAppList->size();
            toolButton->setFixedSize(QSize(71, 48));
            toolButton->setIconSize(QSize(24, 24));
            mAppGroupLayout->addWidget(toolButton);
            // 连接信号和槽
            QCustomTooltip *tooltip = new QCustomTooltip(toolButton);
            connect(toolButton, &QToolButton::clicked, [=]() {
                // 获取鼠标位置
                QPoint pos = QCursor::pos();
                // 在鼠标旁边显示自定义悬浮窗口
                tooltip->showTooltip("", pos + QPoint(10, 10));
            });
        }

//        QCustomTooltip *tooltip_ = new QCustomTooltip();
//        // 连接信号和槽
//        QObject::connect(mAppList, &QListWidget::itemClicked, [=](QListWidgetItem *item) {
//            // 只在点击特定项时弹出悬浮窗口
//            if (item->data(Qt::UserRole).isValid()) { // 检查自定义数据是否有效
//                // 获取鼠标位置
//                QPoint pos = QCursor::pos();
//                // 在鼠标旁边显示自定义悬浮窗口
//                tooltip_->showTooltip(item->data(Qt::UserRole).toString(), pos + QPoint(10, 10));
//            }
//        });

        // 应用组头部组件
        QWidget *mAppHeader = new QWidget();
        mAppHeader->setFixedSize(QSize(344, 28));

        // 协议版本
        QPushButton *mProtocolVersionBtn = new QPushButton(QObject::tr("协议1.0"));
        mProtocolVersionBtn->setDisabled(true);

        // 水平显示协议版本
        QHBoxLayout *mQHBoxLayout= new QHBoxLayout(mAppHeader);
        mQHBoxLayout->setSpacing(0);
        mQHBoxLayout->setMargin(0);
        mQHBoxLayout->addWidget(mGroupHandler);
        mQHBoxLayout->addWidget(mProtocolVersionBtn);



        QVBoxLayout *mGroupLayout = new QVBoxLayout();
        // 紧凑显示
        mGroupLayout->setSpacing(0);
        mGroupLayout->setMargin(0);
        mGroupLayout->addWidget(mAppHeader);

        //mAppGroupContainer->setStyleSheet("padding-top: 8px; ");
        mGroupLayout->addWidget(mAppGroupContainer);


        QWidget *mGroupWidget = new QWidget();
        mGroupWidget->setObjectName("sessionAppGroupWidget");
        mGroupWidget->setLayout(mGroupLayout);
        mGroupWidget->setStyleSheet("border: 1px solid silver; border-color: blue;");
        mGroupWidget->setFixedSize(QSize(344, 88));
        mDeviceBodyLayout->addWidget(mGroupWidget, i / 2, i % 2, Qt::AlignLeft | Qt::AlignTop);
    }

    // body
    QWidget *mDeviceItemBody = new QWidget();
    mDeviceItemBody->setStyleSheet("border: 1px solid silver; border-color: black;");
    mDeviceItemBody->setLayout(mDeviceBodyLayout);

    // 工具栏菜单
    QToolBar *toolBar = new QToolBar("My Toolbar");
    QAction *action = new QAction("My Action");
    toolBar->addAction(action);
    this->addToolBar(toolBar);

    // 托盘主菜单
    QMenu *mMenu = new QMenu();

    // 显示工具提示的Action
    mSbcAction = new QAction();
    mSbcAction->setText(tr("sbc Action"));
    mSbcAction->setDisabled(true);
    mSbcAction->setObjectName(TOOLTIP_VISIBLE_ACTION);
    mSbcAction->setToolTip("This is a tooltip for my action");

    // 托盘组件配置
    QSystemTrayIcon *mSystemTray = new QSystemTrayIcon(this);
    mSystemTray->setIcon(QIcon(QString::fromStdString("://images/logo.png")));
    mSystemTray->setToolTip(QString::fromLocal8Bit("VDI Client"));
    mSystemTray->setVisible(true); // 显示图标
    mSystemTray->setContextMenu(mMenu); /* 设置系统托盘的上下文菜单 */
    connect(mSystemTray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(ActiveTray(QSystemTrayIcon::ActivationReason)));
    // 启用菜单项的工具提示（高版本QT支持，测试5.14.2支持，4.8.7不支持）
    //mMenu->setToolTipsVisible(true);

    // 小配角Action
    QAction *exitAction = new QAction("Exit", this);
    QToolButton *toolButton = new QToolButton();    // QMenu 只支持 QAction 作为其菜单项
    toolButton->setText("Show"); // 设置按钮文本
    mMenu->addAction(exitAction);

    // 自定义菜单默认构造函数未继承
    QAction *action1 = new QAction(QString("phone(VID:PID abcd:1234)"));
    QAction *action2 = new QAction("USB设备管理");
    action1->setEnabled(true);
    CustomMenu *mSubMenu = new CustomMenu("jianhe");
    mSubMenu->setTitle("应用设置");
    mSubMenu->addAction(action1);
    mSubMenu->addAction(action2);
    mSubMenu->addAction(mSbcAction);
    //mSubMenu->menuAction()->setVisible(false);    // 直接不显示隐藏了
    // 连接信号和槽
    //connect(mSubMenu, SIGNAL(showEventSignal()), this, SLOT(RappSettings()));
    QObject::connect(action2, SIGNAL(triggered()), this, SLOT(OpenUSBManagement()));
    mMenu->addMenu(mSubMenu);

    this->setCentralWidget(mDeviceItemBody);   // 居中显示
    return 0;
}

void MainWindow::RappSettings()
{
    qDebug("RappSettings\n");
    mSbcAction->setDisabled(true);
}

void MainWindow::OpenUSBManagement()
{
    USBManagement *mUsbDeviceManager = new USBManagement();
    Q_UNUSED(mUsbDeviceManager);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SetupUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

