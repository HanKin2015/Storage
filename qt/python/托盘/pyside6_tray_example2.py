import sys
from PySide6.QtWidgets import *
from PySide6.QtGui import *
from PySide6.QtCore import *
from ui import ui_main_win

# 主窗口
class main_win(QWidget):

    def __init__(self,parent = None):

        # 从文件中加载UI定义
        super(main_win, self).__init__(parent)
        self.ui = ui_main_win.Ui_Form()
        self.ui.setupUi(self)

        self.setWindowFlag(Qt.FramelessWindowHint)		#将界面设置为无框
        self.setAttribute(Qt.WA_TranslucentBackground)	#将界面属性设置为半透明
        self.shadow = QGraphicsDropShadowEffect()		#设定一个阴影,半径为 4,颜色为 2, 10, 25,偏移为 0,0
        self.shadow.setBlurRadius(4)
        self.shadow.setColor(QColor(2, 10, 25))
        self.shadow.setOffset(0, 0)
        self.ui.frame.setGraphicsEffect(self.shadow)	#为frame设定阴影效果

        # 按钮绑定退出信号
        # self.ui.pushButton_2.clicked.connect(app.quit)
        # 更改按钮为绑定关闭窗口信号
        self.ui.pushButton_2.clicked.connect(self.close)

        # 开启鼠标跟踪后，鼠标离开窗口或进入窗口会触发 mouseMoveEvent 事件
        self.setMouseTracking(True)
        # 初始化各扳机的状态
        self.initDrag()
        # 主窗口绑定事件过滤器
        self.ui.frame.installEventFilter(self)  # 初始化事件过滤器

        # 托盘菜单初始化
        self.tray_icon()


#   -------------------------------------------------托盘菜单功能-----------------------------------------------

    # 托盘菜单初始化
    def tray_icon(self):
        # 创建菜单的项目，并连接对应信号
        self.create_actions()
        # 把项目添加到菜单中( QMenu(self) )
        self.create_tray_icon()

    # 创建菜单的项目，并连接对应信号
    def create_actions(self):

        self._restore_action = QAction("显示主界面")
        self._restore_action.triggered.connect(self.showNormal)

        self._quit_action = QAction("退出")
        self._quit_action.triggered.connect(self.app_quit)

    # 把项目添加到菜单中( QMenu(self) )
    def create_tray_icon(self):
        self._tray_icon_menu = QMenu(self)
        self._tray_icon_menu.addAction(self._restore_action)
        # 添加分隔符
        self._tray_icon_menu.addSeparator()
        self._tray_icon_menu.addAction(self._quit_action)
        # 设置托盘图标，图片必须为正方形
        self._tray_icon = QSystemTrayIcon()
        self._tray_icon.setIcon(QIcon(r'img\logo.png'))
        self._tray_icon.setContextMenu(self._tray_icon_menu)

        # 在系统托盘显示此对象
        self._tray_icon.show()

        # 动作信号
        self._tray_icon.activated.connect(self.iconActivated)

    # 动作信号
    def iconActivated(self,reason):
        # 输出在鼠标在托盘图标上的动作
        print(reason)

        # 双击
        if reason == QSystemTrayIcon.DoubleClick:

            if self._tray_icon.isVisible():
                self.showNormal()

        # 右击
        if reason == QSystemTrayIcon.Context:

            if self._tray_icon.isVisible():
                # 菜单跟随鼠标
                self._tray_icon_menu.exec(QPoint(QCursor.pos().x() - 55 ,QCursor.pos().y() - 90))
            else:
                self.hide()

    # 退出
    def app_quit(self):
        # 先释放资源再退出，用于解决退出后图标不消失的问题
        self._restore_action = None
        self._quit_action = None
        self._tray_icon = None
        self._tray_icon_menu = None
        app.quit()

#   -------------------------------------------------事件过滤器-------------------------------------------------

    def eventFilter(self, obj, event):
        # 事件过滤器,用于解决鼠标进入其它控件后还原为标准鼠标样式
        if isinstance(event, QEnterEvent):
            self.setCursor(Qt.ArrowCursor)
        return super().eventFilter(obj, event)


#   -----------------------------------------------移动与拉伸功能------------------------------------------------

    # 初始化各扳机的状态
    def initDrag(self):
        self._move_drag = False
        self._corner_drag = False
        self._bottom_drag = False
        self._right_drag = False

    # 鼠标按下所执行的功能
    def mousePressEvent(self, event):
        # globalPos为鼠标位置 , pos 为窗口的位置 , m_Position 为鼠标在窗口中的位置  .x() .y() 获取事件中的坐标

        # 移动事件
        if event.button() == Qt.LeftButton and (event.globalPos() - self.pos()).x() < self.ui.frame.size().width() and (event.globalPos() - self.pos()).y() < self.ui.frame.size().height():
            self._move_drag = True
            self.m_Position = event.globalPos() - self.pos()
            event.accept()

        # 右下角边界拉伸事件
        if event.button() == Qt.LeftButton and (event.globalPos() - self.pos()).x() > self.ui.frame.size().width() and (event.globalPos() - self.pos()).y() > self.ui.frame.size().height():
            self._corner_drag = True
            event.accept()

        # 下边界拉伸事件
        if event.button() == Qt.LeftButton and (event.globalPos() - self.pos()).x() < self.ui.frame.size().width() and (event.globalPos() - self.pos()).y() > self.ui.frame.size().height():
            self._bottom_drag = True
            event.accept()

        # 右边界拉伸事件
        if event.button() == Qt.LeftButton and (event.globalPos() - self.pos()).x() > self.ui.frame.size().width() and (event.globalPos() - self.pos()).y() < self.ui.frame.size().height():
            self._right_drag = True
            event.accept()

    # 鼠标移动所执行的功能
    def mouseMoveEvent(self, QMouseEvent):

        # 移动事件
        if Qt.LeftButton and self._move_drag:
            self.move(QMouseEvent.globalPos() - self.m_Position)
            QMouseEvent.accept()

        # 右下角边界拉伸事件
        if Qt.LeftButton and self._corner_drag:
            self.resize(QMouseEvent.pos().x()+10 , QMouseEvent.pos().y()+10)
            QMouseEvent.accept()

        # 下边界拉伸事件
        if Qt.LeftButton and self._bottom_drag:
            self.resize(self.width() , QMouseEvent.pos().y()+10)
            QMouseEvent.accept()

        # 右边界拉伸事件
        if Qt.LeftButton and self._right_drag:
            self.resize(QMouseEvent.pos().x()+10 , self.height())
            QMouseEvent.accept()

        # 获取鼠标在窗口中的位置来改变鼠标的图标
        # 右下角边界光标事件
        if (QMouseEvent.globalPos() - self.pos()).x() > self.ui.frame.size().width() and (QMouseEvent.globalPos() - self.pos()).y() > self.ui.frame.size().height():
            self.setCursor(Qt.SizeFDiagCursor)

        # 下边界光标事件
        elif (QMouseEvent.globalPos() - self.pos()).x() < self.ui.frame.size().width() and (QMouseEvent.globalPos() - self.pos()).y() > self.ui.frame.size().height():
            self.setCursor(Qt.SizeVerCursor)

        # 右边界光标事件
        elif (QMouseEvent.globalPos() - self.pos()).x() > self.ui.frame.size().width() and (QMouseEvent.globalPos() - self.pos()).y() < self.ui.frame.size().height():
            self.setCursor(Qt.SizeHorCursor)
        # 正常光标事件
        else:
            self.setCursor(Qt.ArrowCursor)

    # 鼠标弹起后，恢复各扳机的状态
    def mouseReleaseEvent(self, QMouseEvent):
        self._move_drag = False
        self._corner_drag = False
        self._bottom_drag = False
        self._right_drag = False


if __name__ == '__main__':
    # 每一个 PySide6 应用都必须创建一个应用对象
    app = QApplication([])

    # 设置窗口图标：按下 Alt + Tab 能够看到的图标，图片必须为正方形
    app.setWindowIcon(QIcon(r'img\logo.png'))

    # 检测当前系统是否支持托盘功能
    if not QSystemTrayIcon.isSystemTrayAvailable():
        QMessageBox.critical(None, "系统托盘", "本系统检测不出系统托盘")
        sys.exit(1)

    # 使得程序能在后台运行，关闭最后一个窗口不退出程序
    QApplication.setQuitOnLastWindowClosed(False)

    main_win = main_win()
    main_win.show()
    sys.exit(app.exec()) 