#include "mainwindow.h"
#include "ui_mainwindow.h"

#define TOOLTIP_VISIBLE_ACTION "tooltip_visible_action"

/**
 * @brief 建立起图形界面
 *
 * @return int 0：成功，其他：失败
 */
int MainWindow::SetupUI()
{
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
    mSystemTray->setIcon(QIcon(QString::fromStdString(".\\images\\logo.png")));
    mSystemTray->setToolTip(QString::fromLocal8Bit("VDI Client"));
    mSystemTray->setVisible(true); // 显示图标
    mSystemTray->setContextMenu(mMenu); /* 设置系统托盘的上下文菜单 */

    // 小配角Action
    QAction *exitAction = new QAction("Exit", this);
    QToolButton *toolButton = new QToolButton();    // QMenu 只支持 QAction 作为其菜单项
    toolButton->setText("Show"); // 设置按钮文本
    mMenu->addAction(exitAction);

    // 自定义菜单默认构造函数未继承
    QAction *action1 = new QAction("action1");
    QAction *action2 = new QAction("action2");
    action1->setEnabled(true);
    CustomMenu *mSubMenu = new CustomMenu("jianhe");
    mSubMenu->setTitle("hejian");
    mSubMenu->addAction(action1);
    mSubMenu->addAction(action2);
    mSubMenu->addAction(mSbcAction);
    // 连接信号和槽
    connect(mSubMenu, SIGNAL(showEventSignal()), this, SLOT(RappSettings()));
    mMenu->addMenu(mSubMenu);
    return 0;
}

void MainWindow::RappSettings()
{
    qDebug("RappSettings\n");
    mSbcAction->setDisabled(true);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SetupUI();

    // 创建主窗口的中心部件
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // 创建垂直布局
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // 创建 QToolButton
    QToolButton *toolButton = new QToolButton(this);
    toolButton->setText("Click Me"); // 设置按钮文本
    toolButton->setIcon(QIcon(".\\images\\alienx64.png")); // 设置按钮图标，替换为您的图标路径
    toolButton->setToolTip("This is a tool button."); // 设置工具提示
    toolButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);   // 文本在图标旁边
    toolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);    // 文本在图标下方
    toolButton->setToolButtonStyle(Qt::ToolButtonTextOnly); // 只显示文本
    toolButton->setToolButtonStyle(Qt::ToolButtonIconOnly); // 只显示图标

    // 将按钮添加到布局
    layout->addWidget(toolButton);
}

MainWindow::~MainWindow()
{
    delete ui;
}

