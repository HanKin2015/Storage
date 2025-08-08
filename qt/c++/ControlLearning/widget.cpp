#include "widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // 设置窗口标题和大小
    setWindowTitle("Qt控件展示学习程序");
    resize(1000, 700);

    // 创建主标签页控件
    tabWidget = new QTabWidget(this);

    // 添加各个标签页
    tabWidget->addTab(createBasicControlsTab(), "基本控件");
    tabWidget->addTab(createTextControlsTab(), "文本控件");
    tabWidget->addTab(createListControlsTab(), "列表控件");
    tabWidget->addTab(createSelectionControlsTab(), "选择控件");
    tabWidget->addTab(createContainerControlsTab(), "容器控件");
    tabWidget->addTab(createOtherControlsTab(), "其他控件");
    tabWidget->addTab(createDialogsTab(), "对话框");

    // 设置主布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);
}

Widget::~Widget()
{
}

// 创建基本控件标签页
QWidget* Widget::createBasicControlsTab()
{
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);

    // 按钮控件分组
    QGroupBox *buttonGroup = createGroupBox("按钮控件");
    QHBoxLayout *buttonLayout = new QHBoxLayout(buttonGroup);

    QPushButton *pushBtn = new QPushButton("QPushButton");
    pushBtn->setToolTip("普通按钮");
    buttonLayout->addWidget(pushBtn);

    QToolButton *toolBtn = new QToolButton;
    toolBtn->setText("QToolButton");
    toolBtn->setToolTip("工具按钮");
    buttonLayout->addWidget(toolBtn);

    QCheckBox *checkBox1 = new QCheckBox("复选框1");
    QCheckBox *checkBox2 = new QCheckBox("复选框2");
    checkBox2->setChecked(true);
    buttonLayout->addWidget(checkBox1);
    buttonLayout->addWidget(checkBox2);

    QRadioButton *radioBtn1 = new QRadioButton("单选按钮1");
    QRadioButton *radioBtn2 = new QRadioButton("单选按钮2");
    radioBtn2->setChecked(true);
    QButtonGroup *radioGroup = new QButtonGroup(this);
    radioGroup->addButton(radioBtn1);
    radioGroup->addButton(radioBtn2);
    buttonLayout->addWidget(radioBtn1);
    buttonLayout->addWidget(radioBtn2);

    layout->addWidget(buttonGroup);

    // 添加拉伸项，使控件靠上显示
    layout->addStretch();

    return widget;
}

// 创建文本控件标签页
QWidget* Widget::createTextControlsTab()
{
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);

    // 简单文本控件
    QGroupBox *simpleTextGroup = createGroupBox("简单文本控件");
    QGridLayout *simpleTextLayout = new QGridLayout(simpleTextGroup);

    simpleTextLayout->addWidget(new QLabel("QLabel: 这是一个标签"), 0, 0);

    QLineEdit *lineEdit = new QLineEdit("QLineEdit: 单行文本框");
    simpleTextLayout->addWidget(lineEdit, 0, 1);

    QLabel *passwordLabel = new QLabel("密码框:");
    QLineEdit *passwordEdit = new QLineEdit;
    passwordEdit->setEchoMode(QLineEdit::Password);
    passwordEdit->setText("password");
    simpleTextLayout->addWidget(passwordLabel, 1, 0);
    simpleTextLayout->addWidget(passwordEdit, 1, 1);

    layout->addWidget(simpleTextGroup);

    // 多行文本控件
    QGroupBox *multiTextGroup = createGroupBox("多行文本控件");
    QHBoxLayout *multiTextLayout = new QHBoxLayout(multiTextGroup);

    QTextEdit *textEdit = new QTextEdit;
    textEdit->setHtml("<b>QTextEdit:</b> 富文本编辑器<br>支持HTML格式");
    multiTextLayout->addWidget(textEdit);

    QPlainTextEdit *plainTextEdit = new QPlainTextEdit;
    plainTextEdit->setPlainText("QPlainTextEdit: 纯文本编辑器\n适合显示代码等纯文本内容");
    multiTextLayout->addWidget(plainTextEdit);

    layout->addWidget(multiTextGroup);

    layout->addStretch();

    return widget;
}

// 创建列表控件标签页
QWidget* Widget::createListControlsTab()
{
    QWidget *widget = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout(widget);

    // 列表控件
    QGroupBox *listGroup = createGroupBox("QListWidget");
    QVBoxLayout *listLayout = new QVBoxLayout(listGroup);

    QListWidget *listWidget = new QListWidget;
    listWidget->addItem("列表项 1");
    listWidget->addItem("列表项 2");
    listWidget->addItem("列表项 3");
    listWidget->addItem("列表项 4");
    listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    listLayout->addWidget(listWidget);

    layout->addWidget(listGroup);

    // 树控件
    QGroupBox *treeGroup = createGroupBox("QTreeWidget");
    QVBoxLayout *treeLayout = new QVBoxLayout(treeGroup);

    QTreeWidget *treeWidget = new QTreeWidget;
    treeWidget->setHeaderLabel("树结构示例");

    QTreeWidgetItem *root1 = new QTreeWidgetItem(QStringList() << "根节点 1");
    root1->addChild(new QTreeWidgetItem(QStringList() << "子节点 1-1"));
    root1->addChild(new QTreeWidgetItem(QStringList() << "子节点 1-2"));

    QTreeWidgetItem *root2 = new QTreeWidgetItem(QStringList() << "根节点 2");
    root2->addChild(new QTreeWidgetItem(QStringList() << "子节点 2-1"));
    QTreeWidgetItem *sub2 = new QTreeWidgetItem(QStringList() << "子节点 2-2");
    sub2->addChild(new QTreeWidgetItem(QStringList() << "子节点 2-2-1"));
    root2->addChild(sub2);

    treeWidget->addTopLevelItem(root1);
    treeWidget->addTopLevelItem(root2);
    treeWidget->expandAll();
    treeLayout->addWidget(treeWidget);

    layout->addWidget(treeGroup);

    // 表格控件
    QGroupBox *tableGroup = createGroupBox("QTableWidget");
    QVBoxLayout *tableLayout = new QVBoxLayout(tableGroup);

    QTableWidget *tableWidget = new QTableWidget(4, 3);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "列1" << "列2" << "列3");

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 3; ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(QString("(%1,%2)").arg(row).arg(col));
            tableWidget->setItem(row, col, item);
        }
    }
    tableLayout->addWidget(tableWidget);

    layout->addWidget(tableGroup);

    return widget;
}

// 创建选择控件标签页
QWidget* Widget::createSelectionControlsTab()
{
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);

    // 下拉列表和滑块
    QGroupBox *comboSliderGroup = createGroupBox("下拉列表和滑块");
    QHBoxLayout *comboSliderLayout = new QHBoxLayout(comboSliderGroup);

    QComboBox *comboBox = new QComboBox;
    comboBox->addItems(QStringList() << "选项 1" << "选项 2" << "选项 3" << "选项 4");
    comboBox->setEditable(true);
    comboSliderLayout->addWidget(comboBox);

    QVBoxLayout *sliderLayout = new QVBoxLayout;
    sliderLayout->addWidget(new QLabel("水平滑块 QSlider"));
    QSlider *hSlider = new QSlider(Qt::Horizontal);
    hSlider->setRange(0, 100);
    hSlider->setValue(50);
    sliderLayout->addWidget(hSlider);

    sliderLayout->addWidget(new QLabel("垂直滑块 QSlider"));
    QSlider *vSlider = new QSlider(Qt::Vertical);
    vSlider->setRange(0, 100);
    vSlider->setValue(50);
    sliderLayout->addWidget(vSlider);

    comboSliderLayout->addLayout(sliderLayout);
    layout->addWidget(comboSliderGroup);

    // 数字选择控件
    QGroupBox *numberGroup = createGroupBox("数字选择控件");
    QHBoxLayout *numberLayout = new QHBoxLayout(numberGroup);

    QSpinBox *spinBox = new QSpinBox;
    spinBox->setRange(0, 100);
    spinBox->setValue(50);
    spinBox->setSuffix(" %");
    numberLayout->addWidget(new QLabel("QSpinBox:"));
    numberLayout->addWidget(spinBox);
    numberLayout->addSpacing(20);

    QDial *dial = new QDial;
    dial->setRange(0, 100);
    dial->setValue(50);
    numberLayout->addWidget(new QLabel("QDial:"));
    numberLayout->addWidget(dial);

    // 连接滑块和旋钮，使它们的值同步
    connect(hSlider, &QSlider::valueChanged, dial, &QDial::setValue);
    connect(dial, &QDial::valueChanged, hSlider, &QSlider::setValue);
    connect(hSlider, &QSlider::valueChanged, spinBox, &QSpinBox::setValue);
    connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), hSlider, &QSlider::setValue);

    layout->addWidget(numberGroup);

    // 日期时间选择控件
    QGroupBox *dateTimeGroup = createGroupBox("日期时间选择控件");
    QHBoxLayout *dateTimeLayout = new QHBoxLayout(dateTimeGroup);

    QDateEdit *dateEdit = new QDateEdit(QDate::currentDate());
    dateEdit->setDisplayFormat("yyyy-MM-dd");
    dateTimeLayout->addWidget(new QLabel("QDateEdit:"));
    dateTimeLayout->addWidget(dateEdit);
    dateTimeLayout->addSpacing(10);

    QTimeEdit *timeEdit = new QTimeEdit(QTime::currentTime());
    timeEdit->setDisplayFormat("HH:mm:ss");
    dateTimeLayout->addWidget(new QLabel("QTimeEdit:"));
    dateTimeLayout->addWidget(timeEdit);
    dateTimeLayout->addSpacing(10);

    QDateTimeEdit *dateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime());
    dateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm");
    dateTimeLayout->addWidget(new QLabel("QDateTimeEdit:"));
    dateTimeLayout->addWidget(dateTimeEdit);

    layout->addWidget(dateTimeGroup);

    // 日历控件
    QGroupBox *calendarGroup = createGroupBox("日历控件");
    QHBoxLayout *calendarLayout = new QHBoxLayout(calendarGroup);

    QCalendarWidget *calendarWidget = new QCalendarWidget;
    calendarWidget->setGridVisible(true);
    calendarLayout->addWidget(calendarWidget);

    layout->addWidget(calendarGroup);

    layout->addStretch();

    return widget;
}

// 创建容器控件标签页
QWidget* Widget::createContainerControlsTab()
{
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);

    // 工具盒控件
    QGroupBox *toolBoxGroup = createGroupBox("QToolBox");
    QHBoxLayout *toolBoxLayout = new QHBoxLayout(toolBoxGroup);

    QToolBox *toolBox = new QToolBox;

    QWidget *page1 = new QWidget;
    QVBoxLayout *page1Layout = new QVBoxLayout(page1);
    page1Layout->addWidget(new QLabel("工具盒页面 1"));
    page1Layout->addWidget(new QPushButton("按钮 1"));
    page1Layout->addStretch();
    toolBox->addItem(page1, "页面 1");

    QWidget *page2 = new QWidget;
    QVBoxLayout *page2Layout = new QVBoxLayout(page2);
    page2Layout->addWidget(new QLabel("工具盒页面 2"));
    page2Layout->addWidget(new QCheckBox("复选框"));
    page2Layout->addStretch();
    toolBox->addItem(page2, "页面 2");

    toolBoxLayout->addWidget(toolBox);

    // 分割器控件
    QWidget *splitterWidget = new QWidget;
    QVBoxLayout *splitterLayout = new QVBoxLayout(splitterWidget);
    splitterLayout->addWidget(new QLabel("QSplitter - 可拖动分割窗口"));

    QSplitter *splitter = new QSplitter(Qt::Horizontal);

    QFrame *frame1 = new QFrame;
    frame1->setFrameShape(QFrame::StyledPanel);
    frame1->setLayout(new QVBoxLayout);
    frame1->layout()->addWidget(new QLabel("左侧面板"));
    splitter->addWidget(frame1);

    QSplitter *vSplitter = new QSplitter(Qt::Vertical);

    QFrame *frame2 = new QFrame;
    frame2->setFrameShape(QFrame::StyledPanel);
    frame2->setLayout(new QVBoxLayout);
    frame2->layout()->addWidget(new QLabel("右上方面板"));
    vSplitter->addWidget(frame2);

    QFrame *frame3 = new QFrame;
    frame3->setFrameShape(QFrame::StyledPanel);
    frame3->setLayout(new QVBoxLayout);
    frame3->layout()->addWidget(new QLabel("右下方面板"));
    vSplitter->addWidget(frame3);

    splitter->addWidget(vSplitter);
    splitterLayout->addWidget(splitter);

    toolBoxLayout->addWidget(splitterWidget);
    layout->addWidget(toolBoxGroup);

    // 滚动区域
    QGroupBox *scrollGroup = createGroupBox("QScrollArea - 滚动区域");
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollGroup);

    QScrollArea *scrollArea = new QScrollArea;
    QWidget *scrollContent = new QWidget;
    QVBoxLayout *contentLayout = new QVBoxLayout(scrollContent);

    for (int i = 0; i < 20; ++i) {
        contentLayout->addWidget(new QLabel(QString("滚动内容 %1").arg(i+1)));
    }

    scrollArea->setWidget(scrollContent);
    scrollArea->setWidgetResizable(true);
    scrollLayout->addWidget(scrollArea);

    layout->addWidget(scrollGroup);

    layout->addStretch();

    return widget;
}

// 创建其他控件标签页
QWidget* Widget::createOtherControlsTab()
{
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);

    // 进度条和状态栏
    QGroupBox *progressGroup = createGroupBox("进度指示控件");
    QVBoxLayout *progressLayout = new QVBoxLayout(progressGroup);

    QHBoxLayout *progressBarLayout = new QHBoxLayout;
    progressBarLayout->addWidget(new QLabel("QProgressBar:"));

    QProgressBar *progressBar = new QProgressBar;
    progressBar->setRange(0, 100);
    progressBar->setValue(67);
    progressBarLayout->addWidget(progressBar);
    progressLayout->addLayout(progressBarLayout);

    // 状态条
    QStatusBar *statusBar = new QStatusBar;
    statusBar->showMessage("QStatusBar: 显示状态信息");
    statusBar->addPermanentWidget(new QLabel("右侧信息"));
    progressLayout->addWidget(statusBar);

    layout->addWidget(progressGroup);

    // 菜单栏和工具栏
    QGroupBox *menuToolGroup = createGroupBox("菜单栏和工具栏");
    QVBoxLayout *menuToolLayout = new QVBoxLayout(menuToolGroup);

    QWidget *menuToolWidget = new QWidget;
    QVBoxLayout *mtLayout = new QVBoxLayout(menuToolWidget);

    // 菜单栏
    QMenuBar *menuBar = new QMenuBar;
    QMenu *fileMenu = menuBar->addMenu("文件(&F)");
    fileMenu->addAction("新建(&N)");
    fileMenu->addAction("打开(&O)");
    fileMenu->addSeparator();
    fileMenu->addAction("退出(&X)");

    QMenu *editMenu = menuBar->addMenu("编辑(&E)");
    editMenu->addAction("复制(&C)");
    editMenu->addAction("粘贴(&V)");

    mtLayout->setMenuBar(menuBar);

    // 工具栏
    QToolBar *toolBar = new QToolBar("工具栏");
    toolBar->addAction("新建");
    toolBar->addAction("打开");
    toolBar->addSeparator();
    toolBar->addAction("保存");
    mtLayout->addWidget(toolBar);

    mtLayout->addWidget(new QLabel("以上是菜单栏和工具栏示例"));
    mtLayout->addStretch();

    menuToolLayout->addWidget(menuToolWidget);
    layout->addWidget(menuToolGroup);

    layout->addStretch();

    return widget;
}

// 创建对话框标签页
QWidget* Widget::createDialogsTab()
{
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(widget);

    // 消息对话框按钮
    QGroupBox *msgBoxGroup = createGroupBox("消息对话框");
    QHBoxLayout *msgBoxLayout = new QHBoxLayout(msgBoxGroup);

    QPushButton *infoBtn = new QPushButton("信息对话框");
    connect(infoBtn, &QPushButton::clicked, [=]() {
        QMessageBox::information(this, "信息", "这是一个信息对话框", QMessageBox::Ok);
    });
    msgBoxLayout->addWidget(infoBtn);

    QPushButton *warnBtn = new QPushButton("警告对话框");
    connect(warnBtn, &QPushButton::clicked, [=]() {
        QMessageBox::warning(this, "警告", "这是一个警告对话框", QMessageBox::Ok);
    });
    msgBoxLayout->addWidget(warnBtn);

    QPushButton *errorBtn = new QPushButton("错误对话框");
    connect(errorBtn, &QPushButton::clicked, [=]() {
        QMessageBox::critical(this, "错误", "这是一个错误对话框", QMessageBox::Ok);
    });
    msgBoxLayout->addWidget(errorBtn);

    QPushButton *questionBtn = new QPushButton("询问对话框");
    connect(questionBtn, &QPushButton::clicked, [=]() {
        QMessageBox::question(this, "询问", "这是一个询问对话框",
                              QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    });
    msgBoxLayout->addWidget(questionBtn);

    layout->addWidget(msgBoxGroup);

    // 其他对话框
    QGroupBox *otherDlgGroup = createGroupBox("其他对话框");
    QHBoxLayout *otherDlgLayout = new QHBoxLayout(otherDlgGroup);

    QPushButton *fileBtn = new QPushButton("文件对话框");
    connect(fileBtn, &QPushButton::clicked, [=]() {
        QFileDialog::getOpenFileName(this, "打开文件", ".", "文本文件 (*.txt);;所有文件 (*)");
    });
    otherDlgLayout->addWidget(fileBtn);

    QPushButton *colorBtn = new QPushButton("颜色对话框");
    connect(colorBtn, &QPushButton::clicked, [=]() {
        QColorDialog::getColor(Qt::blue, this, "选择颜色");
    });
    otherDlgLayout->addWidget(colorBtn);

    QPushButton *fontBtn = new QPushButton("字体对话框");
    connect(fontBtn, &QPushButton::clicked, [=]() {
        bool ok;
        QFontDialog::getFont(&ok, QFont("Arial", 12), this, "选择字体");
    });
    otherDlgLayout->addWidget(fontBtn);

    layout->addWidget(otherDlgGroup);

    layout->addStretch();

    return widget;
}

// 辅助函数：创建带标题的分组框
QGroupBox* Widget::createGroupBox(const QString& title)
{
    QGroupBox *groupBox = new QGroupBox(title);
    groupBox->setFlat(false);
    return groupBox;
}
