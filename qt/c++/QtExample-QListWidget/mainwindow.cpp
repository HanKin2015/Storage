#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QListWidget* mAppList;          // 程序组的展示程序的列表组件
    QList<QListWidgetItem*> mAppListItems;  // 程序组内的程序列表组件

    mAppList = new QListWidget();
    mAppList->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    mAppList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // 以上图标下文字单行显示
    mAppList->setViewMode(QListView::IconMode);
    mAppList->setFlow(QListView::LeftToRight);
    mAppList->setMovement(QListView::Static);
    mAppList->setWrapping(false);
    // 限制icon图标大小，此处的值取自视觉稿
    mAppList->setIconSize(QSize(32, 32));

    QListWidgetItem* item = NULL;
    for (int i = 0; i < 3; i++) {
        item = new QListWidgetItem(QIcon(QString::fromStdString(".\\images\\head.jpeg")),
                               QString::fromStdString("alien123456789"), mAppList);
        // 设置工具提示
        item->setToolTip(QString("alien123456789"));

        //该数字根据视觉稿和实际效果调整
        item->setSizeHint(QSize(120, 60));
        mAppListItems.push_back(item);
    }
    this->setCentralWidget(mAppList);                 // 居中显示
}

MainWindow::~MainWindow()
{
    delete ui;
}

