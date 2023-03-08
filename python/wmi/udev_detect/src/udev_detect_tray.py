# -*- coding: utf-8 -*-
"""
文 件 名: udev_detect_tray.py
文件描述: usb设备检测（基于windows系统）
作    者: HanKin
创建日期: 2023.02.27
修改日期：2023.03.08

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
import win32com.client
from log import logger
from PyQt5.QtWidgets import QInputDialog, QWidget, QMainWindow, QAction, QApplication
from PyQt5.QtWidgets import QMenu, QMessageBox, QSystemTrayIcon, qApp
from PyQt5.QtCore import QThread, pyqtSignal, QMetaObject, QCoreApplication, Qt, QRect, QTimer
from PyQt5.QtGui import QIcon, QPainter, QColor, QBrush
import sys
import os
import ico
import base64

UDEV_DETECT_ICO = 'udev_detect.ico'
MSG_ICO = 'msg.ico'
APP_NAME = 'USB设备检测' 

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

        # USB设备检测线程
        self.udevDetect = Thread_UdevDetect()
        self.udevDetect.hotplug_signal.connect(self.hotplugSignalSlot)
        self.udevDetect.get_udev_info_list_signal.connect(self.get_udev_info_list)
        
        # 图片打包
        self.py2ico(ico.udev_detect_ico, UDEV_DETECT_ICO)
        self.py2ico(ico.msg_ico, MSG_ICO)

        # 托盘消息图标闪烁
        self.timer = QTimer(self.ui)
        self.timer.timeout.connect(self.toggleIcon)
        self.udevDetectIcon = QIcon(UDEV_DETECT_ICO)
        self.msgIcon = QIcon(MSG_ICO)
        self.unreadMessageCount = 0                  # 未读消息数

    def toggleIcon(self):
        """托盘消息图标闪烁
        """
        
        if self.trayIcon.isVisible():
            if self.trayIcon.icon().cacheKey() == self.udevDetectIcon.cacheKey():
                self.trayIcon.setIcon(self.msgIcon)
            else:
                self.trayIcon.setIcon(self.udevDetectIcon)
    
    def showMessage(self, title, message, icon=QSystemTrayIcon.Information, timeout=5000):
        """显示消息并开启未读消息定时器
        """
        
        logger.info('message is {}'.format(message))
        self.trayIcon.showMessage(title, message, icon, timeout)
        self.unreadMessageCount += 1  # 未读消息数加1
        if not self.timer.isActive():
            self.timer.start(500)       # 开始定时器
    
    def clearMessage(self):
        """关闭消息定时器
        """
        
        if self.timer.isActive():
            logger.info('current read {} messages'.format(self.unreadMessageCount))
            self.timer.stop()           # 停止定时器
            self.unreadMessageCount = 0 # 未读消息数清零
            self.trayIcon.setIcon(self.udevDetectIcon)   # 设置已读消息图标

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
        
        # QMessageBox第一次打开不居中
        self.ui.setWindowFlags(Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.Tool)
        self.ui.setAttribute(Qt.WA_TranslucentBackground)
        self.ui.show()
        self.ui.hide()

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
        self.ui.setWindowIcon(self.udevDetectIcon)

    def setTrayIcon(self):
        """最小化右键菜单
        """

        # 初始化菜单单项
        self.startUdevDetectAction = QAction("开启USB设备检测")
        self.testMsgAction = QAction("测试消息")
        self.aboutAction = QAction("关于(&N)")
        self.quitAppAction = QAction("退出")
        
        #添加一个图标
        self.aboutAction.setIcon(self.udevDetectIcon)
        
        #添加快捷键
        self.aboutAction.setShortcut(Qt.CTRL + Qt.Key_N)

        # 菜单单项连接方法
        self.startUdevDetectAction.triggered.connect(self.startUdevDetect)
        self.testMsgAction.triggered.connect(self.hotplugSignalSlot)
        self.aboutAction.triggered.connect(self.about)
        self.quitAppAction.triggered.connect(self.quitApp)

        # 初始化菜单列表
        self.trayIconMenu = QMenu()
        self.trayIconMenu.addAction(self.startUdevDetectAction)
        self.trayIconMenu.addSeparator()
        self.trayIconMenu.addAction(self.testMsgAction)
        self.trayIconMenu.addSeparator()
        self.trayIconMenu.addAction(self.aboutAction)
        self.trayIconMenu.addAction(self.quitAppAction)

        # 构建菜单UI
        self.trayIcon = QSystemTrayIcon()
        self.trayIcon.setContextMenu(self.trayIconMenu)
        self.trayIcon.setIcon(self.udevDetectIcon)
        self.trayIcon.setToolTip(APP_NAME)
        
        # 左键双击打开主界面
        self.trayIcon.activated[QSystemTrayIcon.ActivationReason].connect(self.openMainWindow)
        
        # 允许托盘菜单显示
        self.trayIcon.show()

    def openMainWindow(self, reason):
        """双击打开主界面并使其活动
        QSystemTrayIcon::Unknown 0 未知原因
        QSystemTrayIcon::Context 1 系统托盘的上下文菜单请求
        QSystemTrayIcon::DoubleClick 2 双击系统托盘
        QSystemTrayIcon::Trigger 3 单击系统托盘
        QSystemTrayIcon::MiddleClick 4 鼠标中键点击系统托盘
        """
        
        if reason == QSystemTrayIcon.DoubleClick:
            self.ui.showNormal()
            self.ui.activateWindow()
        elif reason == QSystemTrayIcon.Trigger:
            self.clearMessage()

    def hotplugSignalSlot(self, action=''):
        """配置显示 windows 系统消息通知
        """

        msg = '这是一条测试消息'
        if action == 'out':
            msg = '有USB设备拔出'
        elif action == 'in':
            msg = '有USB设备插入'
        if self.trayIcon.supportsMessages() == True and self.trayIcon.isSystemTrayAvailable() == True:
            self.showMessage('新消息', msg, self.msgIcon, 10000)
        else:
            logger.error('trayIcon supportsMessages {}, isSystemTrayAvailable {}'.format(self.trayIcon.supportsMessages(), self.trayIcon.isSystemTrayAvailable()))

    def startUdevDetect(self):
        """初始化显示为开启USB设备检测，即默认是关闭状态
        """
        
        if self.udevDetect.is_on == False:
            logger.info('start usb device detect')
            self.udevDetect.is_on = True
            self.udevDetect.start()
            self.startUdevDetectAction.setText('关闭USB设备检测')
        else:
            logger.info('stop usb device detect')
            self.udevDetect.is_on = False
            self.startUdevDetectAction.setText('开启USB设备检测')

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
            os.remove(UDEV_DETECT_ICO)
            os.remove(MSG_ICO)
            qApp.quit()
        else:
            pass

    def get_udev_info_list(self):
        """获取USB设备的信息列表（包含Hub和USB设备）
        """
        
        wmi = win32com.client.GetObject("winmgmts:")
        #logger.info(wmi)  # <COMObject winmgmts:>
        
        udev_info_list = []
        for usb in wmi.InstancesOf("Win32_USBHub"):
            udev_info_list.append({'usb.USBVersion': usb.USBVersion,
                                 'usb.ProtocolCode': usb.ProtocolCode,
                                 'usb.SubclassCode': usb.SubclassCode,
                                 'usb.Availability': usb.Availability,
                                 'usb.NumberOfConfigs': usb.NumberOfConfigs,
                                 'usb.Name': usb.Name,
                                 'usb.DeviceID': usb.DeviceID,
                                 'usb.Status': usb.Status,
                                 'usb.StatusInfo': usb.StatusInfo,
                                 'usb.PNPDeviceID': usb.PNPDeviceID,
                                 'usb.ClassCode': usb.ClassCode,
                                 'usb.SystemName': usb.SystemName,
                                 'usb.Caption': usb.Caption,
                                 'usb.CreationClassName': usb.CreationClassName,
                                 'usb.CurrentConfigValue': usb.CurrentConfigValue,
                                 'usb.Description': usb.Description})
        # 通知给子进程
        self.udevDetect.udev_info_list = udev_info_list

class Thread_UdevDetect(QThread):
    hotplug_signal = pyqtSignal(str)
    get_udev_info_list_signal = pyqtSignal()

    def __init__(self):
        super(Thread_UdevDetect, self).__init__()
        self.is_on = False
        self.udev_info_list = []

    def run(self):

        self.get_udev_info_list_signal.emit()
        self.sleep(1)   # 等待信号消息处理完成
        logger.info('there are {} hub and usb devices now'.format(len(self.udev_info_list)))
        last_udev_info_list = self.udev_info_list
        while self.is_on:
            self.sleep(1)
            
            self.get_udev_info_list_signal.emit()
            diff_count = len(self.udev_info_list) - len(last_udev_info_list)
            if diff_count == 0:
                continue
            
            self.hotplug_signal.emit('in' if diff_count > 0 else 'out')
            logger.warning('there are {} usb devices which are hogplug {}'.format(abs(diff_count), 'in' if diff_count > 0 else 'out'))
            self.print_hotplug_udev_info(diff_count, last_udev_info_list, self.udev_info_list)
            last_udev_info_list = self.udev_info_list

    def print_udev_info(self, udev_info):
        """打印USB设备信息
        """
        
        for key, value in udev_info.items():
            logger.info('{}: {}'.format(key, value))
        return

    def print_hotplug_udev_info(self, diff_count, udev_info_list, current_udev_info_list):
        """打印出热插拔的设备信息
        """
        
        logger.info('=============== Hotplug USB Device ===============')
        if diff_count > 0:
            udev_info_list, current_udev_info_list = current_udev_info_list, udev_info_list
        for udev_info in udev_info_list:
            if udev_info not in current_udev_info_list:
                self.print_udev_info(udev_info)
        logger.info('=============== Hotplug USB Device ===============')
        return

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
    # mainWindow.show()

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