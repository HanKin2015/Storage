# -*- coding: utf-8 -*-
"""
文 件 名: usb_camera_monitor_tool.py
文件描述: USB摄像头监控工具
作    者: HanKin
创建日期: 2023.02.24
修改日期：2023.02.24

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
import sys
from PyQt5 import QtCore, QtGui, QtWidgets
from log import logger

APP_ICON_PATH = '../img/dog.ico'
APP_MSG_PATH = '../img/msg.png'
APP_NAME = 'USB摄像头监控工具' 

class Ui_MainWindow(object):
    def __init__(self):
        self.ui = None
        self.trayIconMenu = None
        self.quitAppAction = None
        self.openMainWindowAction = None
        self.trayIcon = None
        self.menubar = None
        self.centralwidget = None
        self.pushButton = None
        self.statusbar = None

    def setupUi(self, MainWindow):
        self.ui = MainWindow
        # 主窗口ID
        self.ui.setObjectName("MainWindow")
        self.ui.resize(800, 600)

        # 声明内容组件
        self.centralwidget = QtWidgets.QWidget(self.ui)
        self.centralwidget.setObjectName("centralwidget")

        # 构建内容组件
        self.ui.setCentralWidget(self.centralwidget)

        # 配置主窗口
        self.retranslateUi()
        QtCore.QMetaObject.connectSlotsByName(self.ui)

        # 配置最小化
        self.setTrayIcon()

    def retranslateUi(self):
        """
        设置主界面
        :param MainWindow:
        :return:
        """
        _translate = QtCore.QCoreApplication.translate
        self.ui.setWindowTitle(_translate("MainWindow", APP_NAME))
        self.ui.setWindowIcon(QtGui.QIcon(APP_ICON_PATH))

    def setTrayIcon(self):
        """最小化右键菜单
        """

        # 初始化菜单单项
        self.settingServerAction = QtWidgets.QAction("设置服务器")
        self.monitorScreenCenterAction = QtWidgets.QAction("监控屏幕中心")
        self.testMsgAction = QtWidgets.QAction("测试消息")
        self.aboutAction = QtWidgets.QAction("关于")
        self.quitAppAction = QtWidgets.QAction("退出")

        # 菜单单项连接方法
        self.testMsgAction.triggered.connect(self.windowsMessage)
        self.quitAppAction.triggered.connect(self.quitApp)

        # 初始化菜单列表
        self.trayIconMenu = QtWidgets.QMenu()
        self.trayIconMenu.addAction(self.settingServerAction)
        self.trayIconMenu.addAction(self.monitorScreenCenterAction)
        self.trayIconMenu.addSeparator()
        self.trayIconMenu.addAction(self.testMsgAction)
        self.trayIconMenu.addSeparator()
        self.trayIconMenu.addAction(self.aboutAction)
        self.trayIconMenu.addAction(self.quitAppAction)

        # 构建菜单UI
        self.trayIcon = QtWidgets.QSystemTrayIcon()
        self.trayIcon.setContextMenu(self.trayIconMenu)
        self.trayIcon.setIcon(QtGui.QIcon(APP_ICON_PATH))
        self.trayIcon.setToolTip("左键聚焦说明")
        # 左键双击打开主界面
        self.trayIcon.activated[QtWidgets.QSystemTrayIcon.ActivationReason].connect(self.openMainWindow)
        # 允许托盘菜单显示
        self.trayIcon.show()

    def openMainWindow(self, reason):
        """双击打开主界面并使其活动
        """
        
        if reason == QtWidgets.QSystemTrayIcon.DoubleClick:
            self.ui.showNormal()
            self.ui.activateWindow()

    def windowsMessage(self):
        """配置显示 windows 系统消息通知
        """

        if self.trayIcon.supportsMessages() == True and self.trayIcon.isSystemTrayAvailable() == True:
            self.trayIcon.showMessage("新消息", "有USB设备插入", QtGui.QIcon(APP_MSG_PATH), 10000)
        else:
            logger.error("ERROR: windowsMessage()")

    def quitApp(self):
        """包含二次确认的退出
        """
        
        checkFlag = QtWidgets.QMessageBox.information(self.ui, "退出确认", "是否确认退出？",
                                                      QtWidgets.QMessageBox.Yes | QtWidgets.QMessageBox.No)
        if checkFlag == QtWidgets.QMessageBox.Yes:
            QtWidgets.qApp.quit()
        else:
            pass

def main():
    """主函数
    """

    # 创建活跃 app 句柄
    app = QtWidgets.QApplication(sys.argv)

    # 关闭全部窗口后程序不退出
    app.setQuitOnLastWindowClosed(False)

    # 声明界面句柄
    mainWindow = QtWidgets.QMainWindow()

    # 构建程序界面
    ui = Ui_MainWindow()
    ui.setupUi(mainWindow)

    # 程序启动时打开主界面
    #mainWindow.show()

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
