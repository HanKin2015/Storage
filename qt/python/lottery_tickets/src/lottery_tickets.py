# -*- coding: utf-8 -*-
"""
文 件 名: lottery_tickets.py
文件描述: 福利彩票分析工具
作    者: HanKin
创建日期: 2022.09.16
修改日期：2023.04.11

Copyright (c) 2023 HanKin. All rights reserved.
"""

from common import *
import lottery_tickets_GUI
import sports_tickets_GUI

class Ui_MainWindow(object):
    def __init__(self):
        super().__init__()
        self.image_prepare()
    
    def setupUi(self, MainWindow):
        """
        """
    
        # 主窗口ID
        self.ui = MainWindow
        self.window_setting()
        QMetaObject.connectSlotsByName(self.ui)
        self.ui.destroyed.connect(self.close)
        
        # 初始化菜单栏
        self.init_menu()
        
        # 初始化状态栏
        self.init_status_bar()

        # 构建内容组件
        self.init_tabwidget()
        
        self.init_body()

    def image_prepare(self):
        """图片预处理
        pyinstaller打包图片
        """
        
        self.pyfile_convert_to_image(resource.lottery_tickets_ico, LOTTERY_TICKETS_ICO)
        self.pyfile_convert_to_image(resource.msg_png, MSG_PNG)
        self.pyfile_convert_to_image(resource.about_png, ABOUT_PNG)
        self.pyfile_convert_to_image(resource.exit_png, EXIT_PNG)
        self.pyfile_convert_to_image(resource.test_png, TEST_PNG)
        self.pyfile_convert_to_image(resource.help_png, HELP_PNG)
    
    def window_setting(self):
        """窗口设置
        """
        
        self.ui.setObjectName('MainWindow')
        _translate = QCoreApplication.translate
        self.ui.setWindowTitle(_translate('MainWindow', APP_NAME))
        self.ui.setWindowIcon(QIcon(LOTTERY_TICKETS_ICO))
        self.ui.setGeometry(0, 0, 900, 560)
        self.center()
        
    def init_menu(self):
        """初始化菜单
        """
        
        # 创建菜单栏
        menu_bar = QMenuBar()
        self.ui.setMenuBar(menu_bar)

        # 添加菜单项
        file_memu = QMenu('文件(&F)', self.ui)
        menu_bar.addMenu(file_memu)
        exit_action = QAction(QIcon(EXIT_PNG), '退出(&Q)', self.ui)
        exit_action.triggered.connect(self.ui.close)
        exit_action.setStatusTip('退出')
        exit_action.setShortcut(Qt.CTRL + Qt.Key_Q)
        file_memu.addAction(exit_action)
        
        view_menu = menu_bar.addMenu('视图(&V)')
        view_status_bar_action = QAction('显示状态栏', self.ui, checkable=True)
        view_status_bar_action.setStatusTip('显示状态栏')
        view_status_bar_action.setChecked(True)    # 默认设置为选中状态
        view_status_bar_action.triggered.connect(self.toggleMenu)
        view_menu.addAction(view_status_bar_action)
        
        language_memu = QMenu('语言(&L)', self.ui)
        C_menu = QMenu('C', self.ui)
        Chinese_action = QAction('Chinese', self.ui) 
        C_menu.addAction(Chinese_action)
        E_menu = QMenu('E', self.ui)
        English_action = QAction('English', self.ui) 
        E_menu.addAction(English_action)
        language_memu.addMenu(C_menu)
        language_memu.addMenu(E_menu)
        menu_bar.addMenu(language_memu)
        
        tool_memu = QMenu('工具(&O)', self.ui)
        menu_bar.addMenu(tool_memu)
        
        help_menu = QMenu('帮助(&H)', self.ui)
        menu_bar.addMenu(help_menu)
        
        about_action = QAction('关于(&A)', self.ui)
        about_action.triggered.connect(self.about)
        about_action.setIcon(QIcon(ABOUT_PNG))
        about_action.setShortcut(Qt.CTRL + Qt.Key_A)
        help_menu.addAction(about_action)


        # 工具栏就是常用的命令的集合
        toolbar = self.ui.addToolBar('退出')
        toolbar.addAction(exit_action)
    
    def init_status_bar(self):
        """初始化状态栏
        """
        
        # 创建状态栏
        self.status_bar = QStatusBar(self.ui)
        self.ui.setStatusBar(self.status_bar)
        self.status_bar.showMessage('Ready')

        #self.status_label = QLabel('当前共有 0 个USB设备连接')
        #self.status_bar.addWidget(self.status_label)

    def init_tabwidget(self):
        """初始化选项卡
        """
        
        tab_widget = QTabWidget()
        
        # 设置选项卡位置为下方
        tab_widget.setTabPosition(QTabWidget.East)

        # 创建USB检测选项卡
        tab_widget.addTab(lottery_tickets-GUI.Ui_MainWindow(), 'USB检测')

        # 创建base64编码选项卡
        #tab_widget.addTab(base64_convert_string.MyWindow(), 'base64编码')
    
        self.ui.setCentralWidget(tab_widget)

    def init_body(self):
        """初始化主体
        """
        
        #设置饼图数据
        self.pieSeries = QPieSeries()
        self.pieSeries.setHoleSize(0.35)
        self.pieSeries.append('蛋白质 4.2%', 4.2)
        pieSlice = self.pieSeries.append('脂肪 15.6%', 15.6)
        pieSlice.setExploded()
        pieSlice.setLabelVisible() #设置标签可见,缺省不可见
        self.pieSeries.append('其他 23.8%', 23.8)
        self.pieSeries.append('碳水化合物 56.4%', 56.4)

        #图表视图
        self.chartView = QChartView(self.ui)
        self.chartView.setRenderHint(QPainter.Antialiasing)
        self.chartView.chart().setTitle('文件数量(0/0)')
        self.chartView.chart().addSeries(self.pieSeries)
        self.chartView.chart().legend().setAlignment(Qt.AlignBottom)
        self.chartView.chart().setTheme(QChart.ChartThemeBlueCerulean)
        self.chartView.chart().legend().setFont(QFont('Arial', 8)) #图例字体
        
        self.roll_file_path_label = QLabel('滚动的文字', self.ui)
        self.roll_file_path_label.setAlignment(Qt.AlignCenter)
        
        vbox = QVBoxLayout(self.ui)
        vbox.addWidget(self.chartView)        
        vbox.addWidget(self.roll_file_path_label)
        
        vbox.setSpacing(20)

        self.ui.setStyleSheet("QLineEdit { border: 1px solid black; }")
        self.ui.setLayout(vbox)

    def center(self):
        """窗口居中显示
        """
        
        # 获取屏幕的大小和分辨率
        screen = QDesktopWidget().screenGeometry()
        # 获取主窗口的大小
        size = self.ui.geometry()
        # 计算主窗口居中时左上角的坐标
        self.ui.move(int((screen.width() - size.width()) / 2), int((screen.height() - size.height()) / 2))

    def pyfile_convert_to_image(self, image_data, image):
        """将py文件转换成图片
        """

        if not os.path.exists(image):
            tmp = open(image, 'wb+')
            tmp.write(base64.b64decode(image_data))
            tmp.close()
            
    def about(self):
        """关于
        """

        aboutText = '{} V{}\n\n{}'.format(resource.InternalName, resource.ProductVersion, resource.LegalCopyright)
        QMessageBox.about(self.ui, resource.FileDescription, aboutText)

    def close(self):
        """关闭
        参考微信qq，现在都是没有二次确认退出，这个函数主要是为了情况新生成的文件
        """
        
        logger.info('******** stop ********\n')
        os.remove(LOTTERY_TICKETS_ICO)
        os.remove(MSG_PNG            )
        os.remove(TEST_PNG           )
        os.remove(HELP_PNG           )
        os.remove(ABOUT_PNG          )
        os.remove(EXIT_PNG           )

    def contextMenuEvent(self, event):
        """右键菜单也叫弹出框
        """
        cmenu = QMenu(self)
        newAct = cmenu.addAction("New")
        opnAct = cmenu.addAction("Open")
        quitAct = cmenu.addAction("Quit")
        action = cmenu.exec_(self.mapToGlobal(event.pos()))
        if action == quitAct:
            qApp.quit()

    def toggleMenu(self, state):
        if state:
            self.status_bar.show()
        else:
            self.status_bar.hide()

def main():
    """主函数
    """

    # 创建活跃 app 句柄
    app = QApplication(sys.argv)

    # 关闭全部窗口后程序不退出
    #app.setQuitOnLastWindowClosed(False)

    # 声明界面句柄
    mainWindow = QMainWindow()

    # 构建程序界面
    ui = Ui_MainWindow()
    ui.setupUi(mainWindow)

    # 程序启动时打开主界面
    mainWindow.show()

    sys.exit(app.exec_())

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    logger.info('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    logger.info('process spend {} s.\n'.format(round(end_time - start_time, 3)))

