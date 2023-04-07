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
import USBCheck
import Ui_SystemTrayIcon
import check_ip2

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
        about_action.setIcon(QIcon(EXIT_PNG))
        about_action.setShortcut(Qt.CTRL + Qt.Key_Q)
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

        self.status_label = QLabel('当前共有 0 个USB设备连接')
        status_bar.addWidget(self.status_label)
    
    def init_tray_icon(self):
        """初始化托盘
        """

        systemTrayIcon = Ui_SystemTrayIcon.Ui_SystemTrayIcon(self.ui)
        systemTrayIcon.show()

    def init_tabwidget(self):
        """初始化选项卡
        """
        
        tab_widget = QTabWidget()
        
        # 设置选项卡位置为下方
        tab_widget.setTabPosition(QTabWidget.East)

        # 创建USB检测选项卡
        tab_widget.addTab(USBCheck.MainWindow(), 'USB检测')

        # 创建base64编码选项卡
        tab_widget.addTab(base64_convert_string.MyWindow(), 'base64编码')

        # 创建黑客工具选项卡
        tab_widget.addTab(base64_convert_string.MyWindow(), '黑客工具')
        
        # 创建IP存活选项卡
        tab_widget.addTab(check_ip2.MyWindow(), 'IP存活')
        
        # 创建复制拷贝选项卡
        tab_widget.addTab(base64_convert_string.MyWindow(), '复制拷贝')
    
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

        aboutText = '{} V{}\n\n{}'.format(resource.InternalName, resource.ProductVersion, resource.LegalCopyright)
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
