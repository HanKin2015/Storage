#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QRadioButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QListWidget>
#include <QTreeWidget>
#include <QTableWidget>
#include <QComboBox>
#include <QSlider>
#include <QSpinBox>
#include <QDateEdit>
#include <QGroupBox>
#include <QScrollArea>
#include <QSplitter>
#include <QToolBox>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Qt 控件导航示例");
    setMinimumSize(800, 600);

    // 创建主布局
    QWidget *centralWidget = new QWidget(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    setCentralWidget(centralWidget);

    // 创建导航列表
    navListView = new QListView(this);
    navModel = new QStandardItemModel(this);
    navListView->setModel(navModel);
    navListView->setEditTriggers(QAbstractItemView::NoEditTriggers); // 禁止编辑
    navListView->setSelectionMode(QAbstractItemView::SingleSelection); // 单选
    navListView->setMinimumWidth(150);
    navListView->setMaximumWidth(200);

    // 添加导航项
    QStringList navItems = {
        "基本控件",
        "文本控件",
        "列表控件",
        "选择控件",
        "容器控件"
    };
    foreach (const QString &item, navItems) {
        QStandardItem *standardItem = new QStandardItem(item);
        navModel->appendRow(standardItem);
    }

    // 创建堆叠窗口
    stackedWidget = new QStackedWidget(this);

    // 为每个导航项创建对应的页面
    stackedWidget->addWidget(createBasicWidgetsPage());
    stackedWidget->addWidget(createTextWidgetsPage());
    stackedWidget->addWidget(createListWidgetsPage());
    stackedWidget->addWidget(createSelectionWidgetsPage());
    stackedWidget->addWidget(createContainerWidgetsPage());

    // 将导航和堆叠窗口添加到主布局
    mainLayout->addWidget(navListView);
    mainLayout->addWidget(stackedWidget, 1); // 让内容区域占更多空间

    // 连接导航项点击信号
    connect(navListView, &QListView::clicked, this, &MainWindow::onNavItemClicked);

    // 默认选中第一个导航项
    navListView->setCurrentIndex(navModel->index(0, 0));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onNavItemClicked(const QModelIndex &index)
{
    // 切换到对应的页面
    stackedWidget->setCurrentIndex(index.row());
}

// 创建基本控件页面
QWidget* MainWindow::createBasicWidgetsPage()
{
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);

    QGroupBox *groupBox = new QGroupBox("基本按钮控件");
    QVBoxLayout *groupLayout = new QVBoxLayout(groupBox);

    // 添加各种按钮控件
    groupLayout->addWidget(new QPushButton("普通按钮"));

    QPushButton *checkableBtn = new QPushButton("可勾选按钮");
    checkableBtn->setCheckable(true);
    groupLayout->addWidget(checkableBtn);

    groupLayout->addWidget(new QCheckBox("复选框 1"));
    groupLayout->addWidget(new QCheckBox("复选框 2"));

    QRadioButton *radio1 = new QRadioButton("单选按钮 1");
    QRadioButton *radio2 = new QRadioButton("单选按钮 2");
    radio1->setChecked(true);
    groupLayout->addWidget(radio1);
    groupLayout->addWidget(radio2);

    layout->addWidget(groupBox);
    layout->addStretch(); // 添加伸缩项，将内容顶到上方
    return page;
}

// 创建文本控件页面
QWidget* MainWindow::createTextWidgetsPage()
{
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);

    QGroupBox *groupBox = new QGroupBox("文本输入与显示控件");
    QVBoxLayout *groupLayout = new QVBoxLayout(groupBox);

    groupLayout->addWidget(new QLabel("这是一个标签(QLabel)"));

    groupLayout->addWidget(new QLineEdit("单行文本框(QLineEdit)"));

    QTextEdit *textEdit = new QTextEdit();
    textEdit->setPlaceholderText("多行文本编辑框(QTextEdit)");
    textEdit->setPlainText("第一行文本\n第二行文本\n第三行文本");
    groupLayout->addWidget(textEdit);

    layout->addWidget(groupBox);
    layout->addStretch();
    return page;
}

// 创建列表控件页面
QWidget* MainWindow::createListWidgetsPage()
{
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);

    QSplitter *splitter = new QSplitter(Qt::Vertical);

    // 列表控件
    QListWidget *listWidget = new QListWidget;
    listWidget->addItem("列表项 1");
    listWidget->addItem("列表项 2");
    listWidget->addItem("列表项 3");
    listWidget->setWindowTitle("QListWidget");
    splitter->addWidget(listWidget);

    // 树控件
    QTreeWidget *treeWidget = new QTreeWidget;
    treeWidget->setHeaderLabel("树结构(QTreeWidget)");
    QTreeWidgetItem *root = new QTreeWidgetItem(QStringList() << "根节点");
    root->addChild(new QTreeWidgetItem(QStringList() << "子节点 1"));
    root->addChild(new QTreeWidgetItem(QStringList() << "子节点 2"));
    treeWidget->addTopLevelItem(root);
    treeWidget->expandAll();
    splitter->addWidget(treeWidget);

    // 表格控件
    QTableWidget *tableWidget = new QTableWidget(3, 2);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "列 1" << "列 2");
    tableWidget->setWindowTitle("QTableWidget");
    splitter->addWidget(tableWidget);

    layout->addWidget(splitter);
    return page;
}

// 创建选择控件页面
QWidget* MainWindow::createSelectionWidgetsPage()
{
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);

    QGroupBox *groupBox = new QGroupBox("选择控件");
    QVBoxLayout *groupLayout = new QVBoxLayout(groupBox);

    // 下拉框
    QComboBox *comboBox = new QComboBox;
    comboBox->addItems(QStringList() << "选项 1" << "选项 2" << "选项 3");
    groupLayout->addWidget(comboBox);

    // 滑块
    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 100);
    slider->setValue(50);
    groupLayout->addWidget(slider);

    // 数字调节框
    QSpinBox *spinBox = new QSpinBox;
    spinBox->setRange(0, 100);
    spinBox->setValue(50);
    groupLayout->addWidget(spinBox);

    // 连接滑块和数字调节框
    connect(slider, &QSlider::valueChanged, spinBox, &QSpinBox::setValue);
    connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), slider, &QSlider::setValue);

    // 日期选择器
    QDateEdit *dateEdit = new QDateEdit(QDate::currentDate());
    dateEdit->setDisplayFormat("yyyy-MM-dd");
    groupLayout->addWidget(dateEdit);

    layout->addWidget(groupBox);
    layout->addStretch();
    return page;
}

// 创建容器控件页面
QWidget* MainWindow::createContainerWidgetsPage()
{
    QWidget *page = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(page);

    // 工具盒控件
    QToolBox *toolBox = new QToolBox;

    QWidget *toolPage1 = new QWidget;
    QVBoxLayout *layout1 = new QVBoxLayout(toolPage1);
    layout1->addWidget(new QLabel("工具页 1 内容"));
    layout1->addWidget(new QPushButton("工具页 1 按钮"));
    layout1->addStretch();

    QWidget *toolPage2 = new QWidget;
    QVBoxLayout *layout2 = new QVBoxLayout(toolPage2);
    layout2->addWidget(new QLabel("工具页 2 内容"));
    layout2->addWidget(new QCheckBox("工具页 2 复选框"));
    layout2->addStretch();

    toolBox->addItem(toolPage1, "工具页 1");
    toolBox->addItem(toolPage2, "工具页 2");

    layout->addWidget(toolBox);

    // 滚动区域
    QScrollArea *scrollArea = new QScrollArea;
    QWidget *scrollContent = new QWidget;
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollContent);

    // 添加足够多的控件使滚动区域生效
    for (int i = 1; i <= 20; ++i) {
        scrollLayout->addWidget(new QLabel(QString("滚动内容 %1").arg(i)));
    }

    scrollArea->setWidget(scrollContent);
    scrollArea->setWidgetResizable(true);
    scrollArea->setMaximumHeight(200);

    layout->addWidget(scrollArea);

    return page;
}
