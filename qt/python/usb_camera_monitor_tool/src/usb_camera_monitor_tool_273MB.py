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
from log import logger
import ico
from PyQt5.QtWidgets import QInputDialog, QWidget, QMainWindow, QAction, QApplication, QMenu, QMessageBox, QSystemTrayIcon, qApp
from PyQt5.QtCore import QThread, pyqtSignal, QMetaObject, QCoreApplication
from PyQt5.QtGui import QIcon
import os
import base64
from PyQt5.QtNetwork import QUdpSocket, QHostAddress
import pyautogui
from PIL import Image
import math
import operator
from functools import reduce

USB_CAMERA_MONITOR_TOOL_ICO = 'usb_camera_monitor_tool.ico'
MSG_ICO = 'msg.ico'
BLACK_SCREEN_PNG = 'black_screen.png'
ERROR_SCREEN_PNG = 'error_screen.png'
TMP_SCREENSHOT_PNG = 'tmp.png'
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
        self.py2ico(ico.black_screen_png, BLACK_SCREEN_PNG)
        self.py2ico(ico.error_screen_png, ERROR_SCREEN_PNG)
        
        # 接收消息
        self.sock = QUdpSocket()
        #self.sock.bind(QHostAddress.LocalHost, 6666)
        self.sock.bind(QHostAddress.Any, 6666)
        self.sock.readyRead.connect(self.readDataSlot)
        self.clientAddress = None
        
        # 监控屏幕线程
        self.monitorScreen = Thread_MonitorScreen()
        self.monitorScreen.msg_signal.connect(self.writeDataSlot)
        
    def readDataSlot(self):
        while self.sock.hasPendingDatagrams():
            datagram, host, port = self.sock.readDatagram(
                self.sock.pendingDatagramSize()
            )

            messgae = 'Date time: {}\nHost: {}\nPort: {}\n\n'.format(datagram.decode(), host.toString(), port)
            logger.debug(messgae)
            self.windowsMessage(datagram.decode())

    def writeDataSlot(self, msg):
        if msg == 'black_screen':
            msg = 'USB摄像头现在是黑屏状态'
        elif msg == 'error_screen':
            msg = 'USB摄像头现在是异常状态'
        #msg = 'i love you'
        datagram = msg.encode()
        #self.sock.writeDatagram(datagram, QHostAddress.LocalHost, 6666)
        #self.sock.writeDatagram(datagram, QHostAddress.Broadcast, 6666)
        if self.clientAddress == None:
            QMessageBox.warning(self.ui, '警告', '请先设置客户端地址!', QMessageBox.Yes)
        self.sock.writeDatagram(datagram, QHostAddress(self.clientAddress), 6666)
        
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
        self.centralwidget = QWidget(self.ui)
        self.centralwidget.setObjectName("centralwidget")

        # 构建内容组件
        self.ui.setCentralWidget(self.centralwidget)

        # 配置主窗口
        self.retranslateUi()
        QMetaObject.connectSlotsByName(self.ui)

        # 配置最小化
        self.setTrayIcon()

    def retranslateUi(self):
        """
        设置主界面
        :param MainWindow:
        :return:
        """
        _translate = QCoreApplication.translate
        self.ui.setWindowTitle(_translate("MainWindow", APP_NAME))
        self.ui.setWindowIcon(QIcon(USB_CAMERA_MONITOR_TOOL_ICO))

    def setTrayIcon(self):
        """最小化右键菜单
        """

        # 初始化菜单单项
        self.settingClientAddressAction = QAction("设置客户端地址")
        self.startMonitorScreenAction = QAction("开启监控屏幕")
        self.stopMonitorScreenAction = QAction("关闭监控屏幕")
        self.testMsgAction = QAction("测试消息")
        self.aboutAction = QAction("关于")
        self.quitAppAction = QAction("退出")

        # 菜单单项连接方法
        self.settingClientAddressAction.triggered.connect(self.settingClientAddress)
        self.startMonitorScreenAction.triggered.connect(self.startMonitorScreen)
        self.stopMonitorScreenAction.triggered.connect(self.stopMonitorScreen)
        self.testMsgAction.triggered.connect(self.windowsMessage)
        self.aboutAction.triggered.connect(self.about)
        self.quitAppAction.triggered.connect(self.quitApp)

        # 初始化菜单列表
        self.trayIconMenu = QMenu()
        self.trayIconMenu.addAction(self.settingClientAddressAction)
        self.trayIconMenu.addSeparator()
        self.trayIconMenu.addAction(self.startMonitorScreenAction)
        self.trayIconMenu.addAction(self.stopMonitorScreenAction)
        self.trayIconMenu.addSeparator()
        self.trayIconMenu.addAction(self.testMsgAction)
        self.trayIconMenu.addSeparator()
        self.trayIconMenu.addAction(self.aboutAction)
        self.trayIconMenu.addAction(self.quitAppAction)

        # 构建菜单UI
        self.trayIcon = QSystemTrayIcon()
        self.trayIcon.setContextMenu(self.trayIconMenu)
        self.trayIcon.setIcon(QIcon(USB_CAMERA_MONITOR_TOOL_ICO))
        self.trayIcon.setToolTip(APP_NAME)
        # 左键双击打开主界面
        self.trayIcon.activated[QSystemTrayIcon.ActivationReason].connect(self.openMainWindow)
        # 允许托盘菜单显示
        self.trayIcon.show()

    def openMainWindow(self, reason):
        """双击打开主界面并使其活动
        """
        
        if reason == QSystemTrayIcon.DoubleClick:
            self.ui.showNormal()
            self.ui.activateWindow()

    def windowsMessage(self, msg=False):
        """配置显示 windows 系统消息通知
        """

        if msg == False:
            msg = '这是一条测试消息'
        if self.trayIcon.supportsMessages() == True and self.trayIcon.isSystemTrayAvailable() == True:
            self.trayIcon.showMessage('新消息', msg, QIcon(MSG_ICO), 10000)
        else:
            logger.error('ERROR: windowsMessage()')

    def settingClientAddress(self):
        """设置服务器
        """
        
        text, ok = QInputDialog.getText(None, '设置客户端地址', '请输入地址:')
        if ok:
            self.clientAddress = str(text)
            msg = '这是一条服务端下发的测试消息'
            datagram = msg.encode()
            self.sock.writeDatagram(datagram, QHostAddress(self.clientAddress), 6666)

    def startMonitorScreen(self):
        """开启监控屏幕
        """

        logger.info('start monitor screen')
        self.monitorScreen.is_on = True
        self.monitorScreen.start()

    def stopMonitorScreen(self):
        """关闭监控屏幕
        """
        
        logger.info('stop monitor screen')
        self.monitorScreen.is_on = False

    def about(self):
        """关于
        """

        # parent:QtWidget|None -> self.mainwindow
        QMessageBox.about(self.ui, '关于', 'USB摄像头监控工具')

    def quitApp(self):
        """包含二次确认的退出
        """
        
        checkFlag = QMessageBox.information(self.ui, "退出确认", "是否确认退出？",
                                                      QMessageBox.Yes | QMessageBox.No)
        if checkFlag == QMessageBox.Yes:
            logger.info('******** stop ********\n')
            os.remove(USB_CAMERA_MONITOR_TOOL_ICO)
            os.remove(MSG_ICO)
            os.remove(BLACK_SCREEN_PNG)
            os.remove(ERROR_SCREEN_PNG)
            if os.path.exists(TMP_SCREENSHOT_PNG):
                os.remove(TMP_SCREENSHOT_PNG)
            qApp.quit()
        else:
            pass
        
class Thread_MonitorScreen(QThread):
    msg_signal = pyqtSignal(str)

    def __init__(self):
        super(Thread_MonitorScreen, self).__init__()
        self.is_on = True
        
        logger.info('screen size: {} x {}'.format(pyautogui.size()[0], pyautogui.size()[1]))
        self.screenshot_x = pyautogui.size()[0] / 2 - 32
        self.screenshot_y = pyautogui.size()[1] / 2 -32
        logger.info('screenshot_x = {}, screenshot_y = {}'.format(self.screenshot_x, self.screenshot_y))
    
    def diff_between_two_images(self, image1_path, image2_path):
        """
        """
        
        return 5
    
    def run(self):
        while self.is_on:
            self.sleep(3)
            screenshot = pyautogui.screenshot(TMP_SCREENSHOT_PNG, region=[self.screenshot_x, self.screenshot_y, 32, 32])
            logger.debug('screenshot: {}'.format(screenshot))
            
            black_diff_degree = self.diff_between_two_images(TMP_SCREENSHOT_PNG, BLACK_SCREEN_PNG)
            logger.debug('black_diff_degree: {}'.format(black_diff_degree))
            error_diff_degree = self.diff_between_two_images(TMP_SCREENSHOT_PNG, ERROR_SCREEN_PNG)
            logger.debug('error_diff_degree: {}'.format(error_diff_degree))
            
            if black_diff_degree > 0.97:
                logger.info('usb camera is black screen state, degree is {}'.format(black_diff_degree))
                self.msg_signal.emit('black_screen')
            elif error_diff_degree > 0.97:
                logger.info('usb camera is error screen state, degree is {}'.format(error_diff_degree))
                self.msg_signal.emit('error_screen')

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
