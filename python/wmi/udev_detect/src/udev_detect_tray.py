# -*- coding: utf-8 -*-
"""
文 件 名: udev_detect_tray.py
文件描述: usb设备检测（基于windows系统）
作    者: HanKin
创建日期: 2023.02.27
修改日期：2023.02.27

Copyright (c) 2023 HanKin. All rights reserved.
"""

import time
import win32com.client
from log import logger
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtCore import Qt, QThread, pyqtSignal
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

        self.udevDetect = Thread_UdevDetect()
        self.udevDetect.hotplug_signal.connect(self.windowsMessage)
        self.udevDetect.get_udev_info_list_signal.connect(self.get_udev_info_list)
        
        self.py2ico(ico.udev_detect_ico, UDEV_DETECT_ICO)
        self.py2ico(ico.msg_ico, MSG_ICO)

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
        self.ui.setWindowIcon(QtGui.QIcon(UDEV_DETECT_ICO))

    def setTrayIcon(self):
        """最小化右键菜单
        """

        # 初始化菜单单项
        self.startUdevDetectAction = QtWidgets.QAction("开启USB设备检测")
        self.stopUdevDetectAction = QtWidgets.QAction("关闭USB设备检测")
        self.testMsgAction = QtWidgets.QAction("测试消息")
        self.aboutAction = QtWidgets.QAction("关于")
        self.quitAppAction = QtWidgets.QAction("退出")

        # 菜单单项连接方法
        self.startUdevDetectAction.triggered.connect(self.startUdevDetect)
        self.stopUdevDetectAction.triggered.connect(self.stopUdevDetect)
        self.testMsgAction.triggered.connect(self.windowsMessage)
        self.quitAppAction.triggered.connect(self.quitApp)

        # 初始化菜单列表
        self.trayIconMenu = QtWidgets.QMenu()
        self.trayIconMenu.addAction(self.startUdevDetectAction)
        self.trayIconMenu.addAction(self.stopUdevDetectAction)
        self.trayIconMenu.addSeparator()
        self.trayIconMenu.addAction(self.testMsgAction)
        self.trayIconMenu.addSeparator()
        self.trayIconMenu.addAction(self.aboutAction)
        self.trayIconMenu.addAction(self.quitAppAction)

        # 构建菜单UI
        self.trayIcon = QtWidgets.QSystemTrayIcon()
        self.trayIcon.setContextMenu(self.trayIconMenu)
        self.trayIcon.setIcon(QtGui.QIcon(UDEV_DETECT_ICO))
        self.trayIcon.setToolTip("USB设备检测")
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

    def windowsMessage(self, action=''):
        """配置显示 windows 系统消息通知
        """

        msg = '这是一条测试消息'
        if action == 'out':
            msg = '有USB设备拔出'
        elif action == 'in':
            msg = '有USB设备插入'
        if self.trayIcon.supportsMessages() == True and self.trayIcon.isSystemTrayAvailable() == True:
            self.trayIcon.showMessage('新消息', msg, QtGui.QIcon(MSG_ICO), 10000)
        else:
            logger.error('ERROR: windowsMessage()')

    def stopUdevDetect(self):
        """开启USB设备检测
        """
        
        logger.info('stop usb device detect')
        self.udevDetect.is_on = False

    def quitApp(self):
        """包含二次确认的退出
        """
        
        checkFlag = QtWidgets.QMessageBox.information(self.ui, "退出确认", "是否确认退出？",
                                                      QtWidgets.QMessageBox.Yes | QtWidgets.QMessageBox.No)
        if checkFlag == QtWidgets.QMessageBox.Yes:
            logger.info('******** stop ********\n')
            os.remove(UDEV_DETECT_ICO)
            os.remove(MSG_ICO)
            QtWidgets.qApp.quit()
        else:
            pass

    def startUdevDetect(self):
        """关闭USB设备检测
        """
        
        logger.info('start usb device detect')
        self.udevDetect.is_on = True
        self.udevDetect.start()

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
        self.is_on = True
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
    app = QtWidgets.QApplication(sys.argv)

    # 关闭全部窗口后程序不退出
    app.setQuitOnLastWindowClosed(False)

    # 声明界面句柄
    mainWindow = QtWidgets.QMainWindow()

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