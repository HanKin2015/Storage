#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QListWidgetItem>
#include <QLabel>
#include <QFont>
#include <QPalette>
#include <QMessageBox>

#pragma execution_character_set("utf-8")

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initUI();
    initNavItems();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initUI()
{
    // 设置窗口基本属性
    setWindowTitle("可折叠导航栏示例");
    setMinimumSize(800, 600);

    // 创建主布局
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // 创建导航列表
    navList = new QListWidget(this);
    navList->setMaximumWidth(200);
    navList->setMinimumWidth(200);
    navList->setStyleSheet("QListWidget { background-color: #2d2d2d; color: white; border: none; }"
                           "QListWidget::item { height: 30px; padding-left: 10px; }"
                           "QListWidget::item:selected { background-color: #555555; color: white; }"
                           "QListWidget::item:hover { background-color: #444444; }");
    connect(navList, &QListWidget::itemClicked, this, &MainWindow::onNavItemClicked);

    // 创建内容区域
    contentStack = new QStackedWidget(this);
    contentStack->setStyleSheet("background-color: #f0f0f0;");

    // 添加到主布局
    mainLayout->addWidget(navList);
    mainLayout->addWidget(contentStack, 1);

    setCentralWidget(centralWidget);
}

void MainWindow::initNavItems()
{
    // 初始化导航项数据
    navItems["基本控件"] = {"按钮", "复选框", "单选按钮", "标签", "文本框"};
    navItems["容器控件"] = {"窗口", "对话框", "滚动区域", "分组框", "选项卡"};
    navItems["数据控件"] = {"列表", "表格", "树", "组合框", "视图"};
    navItems["高级控件"] = {"图表", "进度条", "滑块", "日历", "时间选择器"};

    // 添加所有导航组
    for (auto it = navItems.begin(); it != navItems.end(); ++it) {
        addNavGroup(it.key(), it.value());
        expandStates[it.key()] = false; // 默认折叠
    }
}

void MainWindow::addNavGroup(const QString &groupName, const QStringList &items)
{
    // 添加组标题项
    QListWidgetItem *groupItem = createGroupItem(groupName);
    navList->addItem(groupItem);

    // 添加子项（默认隐藏）
    for (const QString &item : items) {
        QListWidgetItem *subItem = createSubItem(item, groupName);
        subItem->setHidden(true);
        navList->addItem(subItem);
    }

    // 添加一个内容页面
    QLabel *label = new QLabel("<center><h1>" + groupName + "</h1><p>请选择左侧具体控件查看详情</p></center>");
    label->setStyleSheet("font-size: 16px; color: #333;");
    contentStack->addWidget(label);
}

QListWidgetItem* MainWindow::createGroupItem(const QString &text)
{
    QListWidgetItem *item = new QListWidgetItem(text + " [+]");
    QFont font = item->font();
    font.setBold(true);
    font.setPointSize(10);
    item->setFont(font);
    item->setData(Qt::UserRole, "group");
    item->setData(Qt::UserRole + 1, text);
    return item;
}

QListWidgetItem* MainWindow::createSubItem(const QString &text, const QString &parent)
{
    QListWidgetItem *item = new QListWidgetItem("  " + text); // 缩进显示
    item->setData(Qt::UserRole, "sub");
    item->setData(Qt::UserRole + 1, text);
    parentMap[item] = parent;

    // 添加对应的内容页面
    QLabel *label = new QLabel("<center><h2>" + text + "</h2><p>这是" + text + "的演示页面</p></center>");
    label->setStyleSheet("font-size: 16px; color: #333;");
    contentStack->addWidget(label);

    return item;
}

void MainWindow::toggleGroup(const QString &groupName)
{
    bool isExpanded = expandStates[groupName];
    expandStates[groupName] = !isExpanded;

    // 更新组标题显示
    for (int i = 0; i < navList->count(); ++i) {
        QListWidgetItem *item = navList->item(i);
        if (item->data(Qt::UserRole).toString() == "group" &&
            item->data(Qt::UserRole + 1).toString() == groupName) {

            item->setText(groupName + (isExpanded ? " [+]" : " [-]"));
            break;
        }
    }

    // 显示或隐藏子项
    for (int i = 0; i < navList->count(); ++i) {
        QListWidgetItem *item = navList->item(i);
        if (item->data(Qt::UserRole).toString() == "sub" &&
            parentMap[item] == groupName) {

            item->setHidden(isExpanded);
        }
    }
}

void MainWindow::onNavItemClicked(QListWidgetItem *item)
{
    if (!item) return;

    QString type = item->data(Qt::UserRole).toString();

    if (type == "group") {
        // 点击组标题，切换展开/折叠状态
        QString groupName = item->data(Qt::UserRole + 1).toString();
        toggleGroup(groupName);
    }
    else if (type == "sub") {
        // 点击子项，切换到对应的内容页面
        QString text = item->data(Qt::UserRole + 1).toString();

        // 这里简化处理，实际应用中可以根据需要映射到正确的页面索引
        for (int i = 0; i < contentStack->count(); ++i) {
            QLabel *label = qobject_cast<QLabel*>(contentStack->widget(i));
            if (label && label->text().contains(text)) {
                contentStack->setCurrentIndex(i);
                break;
            }
        }
    }
}
