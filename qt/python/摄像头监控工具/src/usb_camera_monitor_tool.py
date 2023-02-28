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
import ico
from PyQt5.QtWidgets import QInputDialog
from PyQt5.QtCore import Qt, QThread, pyqtSignal
import os
import base64
from PyQt5.QtNetwork import QUdpSocket, QHostAddress

USB_CAMERA_MONITOR_TOOL_ICO = 'usb_camera_monitor_tool.ico'
MSG_ICO = 'msg.ico'
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
        
        # pyinstaller打包图片
        self.py2ico(ico.usb_camera_monitor_tool_ico, USB_CAMERA_MONITOR_TOOL_ICO)
        self.py2ico(ico.msg_ico, MSG_ICO)
        
        # 接收消息
        self.sock = QUdpSocket()
        #self.sock.bind(QHostAddress.LocalHost, 6666)
        self.sock.bind(QHostAddress.Any, 6666)
        self.sock.readyRead.connect(self.readDataSlot)
        self.clientAddress = None
        
    def readDataSlot(self):
        while self.sock.hasPendingDatagrams():
            datagram, host, port = self.sock.readDatagram(
                self.sock.pendingDatagramSize()
            )

            messgae = 'Date time: {}\nHost: {}\nPort: {}\n\n'.format(datagram.decode(), host.toString(), port)
            logger.debug(messgae)
            self.windowsMessage(datagram.decode())

    def py2ico(self, ico_data, ico_img):
        """将py文件转换成ico图片
        """

        if not os.path.exists(ico_img):
            tmp = open(ico_img, 'wb+')
            tmp.write(base64.b64decode(ico_data))
            tmp.close()

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
        self.ui.setWindowIcon(QtGui.QIcon(USB_CAMERA_MONITOR_TOOL_ICO))

    def setTrayIcon(self):
        """最小化右键菜单
        """

        # 初始化菜单单项
        self.settingClientAddressAction = QtWidgets.QAction("设置客户端地址")
        self.monitorScreenCenterAction = QtWidgets.QAction("监控屏幕中心")
        self.testMsgAction = QtWidgets.QAction("测试消息")
        self.aboutAction = QtWidgets.QAction("关于")
        self.quitAppAction = QtWidgets.QAction("退出")

        # 菜单单项连接方法
        self.settingClientAddressAction.triggered.connect(self.settingClientAddress)
        self.monitorScreenCenterAction.triggered.connect(self.monitorScreenCenter)
        self.testMsgAction.triggered.connect(self.windowsMessage)
        self.quitAppAction.triggered.connect(self.quitApp)

        # 初始化菜单列表
        self.trayIconMenu = QtWidgets.QMenu()
        self.trayIconMenu.addAction(self.settingClientAddressAction)
        self.trayIconMenu.addAction(self.monitorScreenCenterAction)
        self.trayIconMenu.addSeparator()
        self.trayIconMenu.addAction(self.testMsgAction)
        self.trayIconMenu.addSeparator()
        self.trayIconMenu.addAction(self.aboutAction)
        self.trayIconMenu.addAction(self.quitAppAction)

        # 构建菜单UI
        self.trayIcon = QtWidgets.QSystemTrayIcon()
        self.trayIcon.setContextMenu(self.trayIconMenu)
        self.trayIcon.setIcon(QtGui.QIcon(USB_CAMERA_MONITOR_TOOL_ICO))
        self.trayIcon.setToolTip(APP_NAME)
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

    def windowsMessage(self, msg=False):
        """配置显示 windows 系统消息通知
        """

        if msg == False:
            msg = '这是一条测试消息'
        if self.trayIcon.supportsMessages() == True and self.trayIcon.isSystemTrayAvailable() == True:
            self.trayIcon.showMessage('新消息', msg, QtGui.QIcon(MSG_ICO), 10000)
        else:
            logger.error('ERROR: windowsMessage()')

    def quitApp(self):
        """包含二次确认的退出
        """
        
        checkFlag = QtWidgets.QMessageBox.information(self.ui, "退出确认", "是否确认退出？",
                                                      QtWidgets.QMessageBox.Yes | QtWidgets.QMessageBox.No)
        if checkFlag == QtWidgets.QMessageBox.Yes:
            logger.info('******** stop ********\n')
            os.remove(USB_CAMERA_MONITOR_TOOL_ICO)
            os.remove(MSG_ICO)
            QtWidgets.qApp.quit()
        else:
            pass

    def settingClientAddress(self):
        """设置服务器
        """
        
        text, ok = QInputDialog.getText(None, '设置客户端地址', '请输入地址:')
        if ok:
            self.clientAddress = str(text)

    def monitorScreenCenter(self):
        """监控屏幕中心
        """
        
        msg = 'i love you'
        datagram = msg.encode()
        #self.sock.writeDatagram(datagram, QHostAddress.LocalHost, 6666)
        #self.sock.writeDatagram(datagram, QHostAddress.Broadcast, 6666)
        self.sock.writeDatagram(datagram, QHostAddress(self.clientAddress), 6666)
        
class Thread_UdpServer(QThread):
    msg_signal = pyqtSignal(str)

    def __init__(self):
        super(Thread_UdpServer, self).__init__()
        self.is_on = True


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
