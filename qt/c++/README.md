# 项目说明

## 1、qt_example
qt示例，实现上面图标下面文字功能，文字添加工具提示框，图标涵盖png/gif/jpg/jpeg/ico格式。
注意：images文件夹需要放在build-qt_example-Desktop_Qt_5_14_2_MinGW_64_bit-Debug文件夹才能生效。

## 2、capture
实现摄像头打开功能。

## 3、StudyQml
学习Qml实现qt界面。

## 4、判断鼠标是否在组件上面
```
void checkMousePosition() {
    // 检查鼠标是否在悬浮框上
    QPoint pos = QCursor::pos();
    QRect widgetRect = QRect(mToolButton->mapToGlobal(mToolButton->rect().topLeft()), mToolButton->size());
    if (!underMouse() && !widgetRect.contains(pos)) {
        qDebug("hejian underMouse(): %d", underMouse());
        hideTooltip(); // 如果不在悬浮框上，隐藏悬浮框
    }
}
```

## 5、打印事件消息
```
bool event(QEvent *event) override
{
    // 获取当前时间
    QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    // 获取事件类型
    int eventType = event->type();

    // 将事件类型转换为字符串
    QString eventTypeName = QEvent::staticMetaObject.enumerator(QEvent::staticMetaObject.indexOfEnumerator("Type")).valueToKey(eventType);

    // 输出当前时间和事件类型名称
    qDebug("%s: %s", currentTime.toStdString().c_str(), eventTypeName.toStdString().c_str());
    return QWidget::event(event);
}
```

在 Qt 开发中，常用的组件和功能非常丰富，涵盖了界面设计、数据处理、网络通信、多媒体等多个领域。以下是一些高频使用的组件及功能分类说明：
一、基础界面组件
QWidget：所有界面组件的基类，可作为容器或独立窗口。
QPushButton：按钮组件，支持点击事件，可设置图标、文本。
QLabel：用于显示文本或图片，支持富文本、链接跳转。
QLineEdit/QTextEdit：文本输入组件，前者用于单行输入，后者支持多行、富文本编辑。
QComboBox：下拉列表组件，可选择预设选项或允许用户输入。
QCheckBox/QRadioButton：复选框（支持多选）和单选按钮（互斥选择）。
QSlider/QSpinBox：滑动条和数字调节框，用于数值输入或范围选择。
二、布局管理组件
用于自动排列界面元素，适应窗口大小变化：

QVBoxLayout：垂直方向布局，组件上下排列。
QHBoxLayout：水平方向布局，组件左右排列。
QGridLayout：网格布局，按行和列排列组件。
QFormLayout：表单布局，适合 “标签 + 输入框” 的成对排列（如注册表单）。
QStackedLayout：堆叠布局，仅显示一个组件，常用于 “分页” 切换（配合 QTabWidget 使用）。
三、容器与复杂组件
QTabWidget：标签页容器，可切换多个页面（如浏览器标签页）。
QGroupBox：带标题的分组框，用于逻辑分组组件（如 “基本设置”“高级设置”）。
QScrollArea：滚动区域，当内容超出显示范围时提供滚动条。
QTreeWidget/QListView/QTableWidget：
树形结构（QTreeWidget）：如文件目录树。
列表视图（QListView）：单列数据展示，支持自定义项。
表格组件（QTableWidget）：多行多列数据，支持单元格编辑、排序。
QDialog：对话框基类，衍生出QMessageBox（消息提示）、QFileDialog（文件选择）、QInputDialog（输入对话框）等。
四、功能型组件
QTimer：定时器，用于定时执行任务（如刷新界面、轮询数据）。
QMenu/QToolBar：菜单和工具栏，支持添加动作（QAction）、图标、快捷键。
QStatusBar：状态栏，显示程序状态信息（如 “就绪”“正在加载”）。
QProgressBar：进度条，显示任务进度（如文件下载、数据处理）。
QCalendarWidget：日历组件，用于选择日期。
五、数据与文件处理
QFile/QTextStream：文件操作，支持文本文件读写。
QDataStream：二进制文件读写，适合序列化数据。
QSettings：用于读写配置文件（如 ini 格式），保存程序设置（如窗口大小、用户偏好）。
QJsonDocument/QJsonObject：JSON 数据解析与生成，处理网络接口返回的 JSON 数据。
六、网络与通信
QTcpSocket/QTcpServer：TCP 协议通信，实现客户端与服务器的 socket 连接。
QUdpSocket：UDP 协议通信，用于无连接的数据传输。
QNetworkAccessManager：网络请求管理，支持 HTTP/HTTPS 的 GET/POST 请求（如调用 API 接口）。
七、绘图与多媒体
QPainter：绘图工具，在 QWidget 的paintEvent中绘制图形、文本、图像。
QPixmap/QImage：图像处理，前者适合显示，后者支持像素级操作。
QMediaPlayer/QVideoWidget：多媒体播放，支持音频、视频文件播放，配合 QVideoWidget 显示视频画面。
八、信号与槽机制（核心功能）
虽然不是组件，但信号与槽（Signal & Slot） 是 Qt 的核心机制，用于组件间通信：

当组件状态变化（如按钮被点击、文本被修改）时，会发出 “信号”。
通过 “槽函数” 关联信号，实现事件响应（如点击按钮后执行保存操作）。

这些组件覆盖了大部分常见开发场景，Qt 还提供了大量扩展模块（如 Qt Charts 绘图、Qt WebEngine 网页嵌入、Qt Bluetooth 蓝牙通信等），可根据需求进一步扩展功能。