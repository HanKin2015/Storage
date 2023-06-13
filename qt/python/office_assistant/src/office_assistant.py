# -*- coding: utf-8 -*-
"""
文 件 名: office_assistant.py
文件描述: 办公助手
作    者: HanKin
创建日期: 2023.04.04
修改日期：2023.04.04

Copyright (c) 2023 HanKin. All rights reserved.
"""

from common import *
import USBInterface
import base64_convert_string
import Ui_USBCheck
import Ui_SystemTrayIcon
import Ui_CheckIP
import Ui_ClearTool
import Ui_HackTool
import Ui_CopyTool
import Ui_MathTool

class Ui_MainWindow(object):
    def __init__(self):
        super().__init__()
        self.image_prepare()
        self.cpu_memory_thread = Thread_CPUMemory()
        self.cpu_memory_thread.flush_signal.connect(self.flush_signal_slot)
    
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

        # 去掉边框和置顶显示以及任务栏显示
        #self.ui.setWindowFlags(Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.Tool)
        
        # 去掉背景框
        #self.ui.setAttribute(Qt.WA_TranslucentBackground)

        # 配置托盘
        self.init_tray_icon()
    
    def image_prepare(self):
        """图片预处理
        pyinstaller打包图片
        """
        
        self.pyfile_convert_to_image(resource.office_assistant_ico, OFFICE_ASSISTANT_ICO)
        self.pyfile_convert_to_image(resource.usb_check_ico, USB_CHECK_ICO)
        self.pyfile_convert_to_image(resource.camera_monitor_ico, CAMERA_MONITOR_ICO)
        self.pyfile_convert_to_image(resource.udev_detect_ico, UDEV_DETECT_ICO)
        
        self.pyfile_convert_to_image(resource.msg_png, MSG_PNG)
        self.pyfile_convert_to_image(resource.test_png, TEST_PNG)
        self.pyfile_convert_to_image(resource.about_png, ABOUT_PNG)
        self.pyfile_convert_to_image(resource.exit_png, EXIT_PNG)
        self.pyfile_convert_to_image(resource.help_png, HELP_PNG)
    
    def window_setting(self):
        """窗口设置
        """
        
        self.ui.setObjectName('MainWindow')
        _translate = QCoreApplication.translate
        self.ui.setWindowTitle(_translate('MainWindow', APP_NAME))
        self.ui.setWindowIcon(QIcon(OFFICE_ASSISTANT_ICO))
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
        exit_action = QAction('退出(&Q)', self.ui)
        exit_action.triggered.connect(self.ui.close)
        exit_action.setIcon(QIcon(EXIT_PNG))
        exit_action.setShortcut(Qt.CTRL + Qt.Key_Q)
        file_memu.addAction(exit_action)
        
        language_memu = QMenu('语言(&L)', self.ui)
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
    
    def init_status_bar(self):
        """初始化状态栏
        """
        
        # 创建状态栏
        status_bar = QStatusBar(self.ui)
        self.ui.setStatusBar(status_bar)

        system = platform.system()
        release = platform.release()
        status_bar.addWidget(QLabel('{}{}'.format(system, release)))
        cpu_count = psutil.cpu_count()
        mem_total = psutil.virtual_memory().total
        status_bar.addWidget(QLabel('{}核 {}G'.format(cpu_count, math.ceil(mem_total/1024/1024/1024))))
        self.cpu_label = QLabel('CPU: 5.5%')
        status_bar.addWidget(self.cpu_label)
        self.memory_label = QLabel('内存: 50.5%')
        status_bar.addWidget(self.memory_label)
        self.cpu_memory_thread.start()
    
    def init_tray_icon(self):
        """初始化托盘
        """

        systemTrayIcon = Ui_SystemTrayIcon.Ui_SystemTrayIcon(self.ui)
        systemTrayIcon.show_mainwindow_signal.connect(self.show_mainwindow_signal_slot)
        #systemTrayIcon.show()

    def init_tabwidget(self):
        """初始化选项卡
        """
        
        tab_widget = QTabWidget()
        
        # 设置选项卡位置为下方
        tab_widget.setTabPosition(QTabWidget.East)

        # 创建USB检测选项卡
        tab_widget.addTab(Ui_USBCheck.MainWindow(), 'USB检测')

        # 创建base64编码选项卡
        tab_widget.addTab(base64_convert_string.MainWindow(), 'base64编码')

        # 创建黑客工具选项卡
        tab_widget.addTab(Ui_HackTool.MainWindow(), '黑客工具')
        
        # 创建IP存活选项卡
        tab_widget.addTab(Ui_CheckIP.MainWindow(), 'IP存活')
        
        # 创建复制拷贝选项卡
        tab_widget.addTab(Ui_CopyTool.MainWindow(), '复制拷贝')
        
        # 创建清理工具选项卡
        tab_widget.addTab(Ui_ClearTool.MainWindow(), '清理工具')
        
        # 创建数学工具选项卡
        tab_widget.addTab(Ui_MathTool.MainWindow(), '数学工具')
    
        self.ui.setCentralWidget(tab_widget)

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

        if LITE_VERSION:
            aboutText = '{} v{} (lite)\n\n{}'.format(resource.InternalName, resource.ProductVersion, resource.LegalCopyright)
        else:
            aboutText = '{} v{}\n\n{}'.format(resource.InternalName, resource.ProductVersion, resource.LegalCopyright)
        QMessageBox.about(self.ui, resource.FileDescription, aboutText)

    def close(self):
        """关闭
        参考微信qq，现在都是没有二次确认退出，这个函数主要是为了情况新生成的文件
        """
        
        logger.info('******** stop ********\n')
        os.remove(OFFICE_ASSISTANT_ICO)
        os.remove(USB_CHECK_ICO       )
        os.remove(CAMERA_MONITOR_ICO  )
        os.remove(UDEV_DETECT_ICO     )
        os.remove(MSG_PNG             )
        os.remove(TEST_PNG            )
        os.remove(HELP_PNG            )
        os.remove(ABOUT_PNG           )
        os.remove(EXIT_PNG            )
        if os.path.exists(TMP_SCREENSHOT_PNG):
            os.remove(TMP_SCREENSHOT_PNG)

    def show_mainwindow_signal_slot(self):
        """双击托盘图标显示主窗口
        """
        
        self.ui.showNormal()
        self.ui.activateWindow()

    def flush_signal_slot(self, cpu_percent, mem_percent):
        """每隔1秒刷新CPU和内存使用率
        """

        self.cpu_label.setText('CPU: {:.1f}%'.format(cpu_percent))
        self.memory_label.setText('内存: {:.1f}%'.format(mem_percent))
    
class Thread_CPUMemory(QThread):
    flush_signal = pyqtSignal(float, float)

    def __init__(self):
        super(Thread_CPUMemory, self).__init__()

    def run(self):
        """
        """

        while True:
            # 获取CPU使用率
            cpu_percent = psutil.cpu_percent(interval=1)

            # 获取内存使用率
            mem = psutil.virtual_memory()
            mem_percent = mem.percent

            logger.debug("CPU使用率：{}%".format(cpu_percent))
            logger.debug("内存使用率：{}%".format(mem_percent))

            self.flush_signal.emit(cpu_percent, mem_percent)
            time.sleep(1)

def main():
    """主函数
    """

    # 创建活跃 app 句柄
    app = QApplication(sys.argv)

    # 关闭全部窗口后程序不退出
    app.setQuitOnLastWindowClosed(False)

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
