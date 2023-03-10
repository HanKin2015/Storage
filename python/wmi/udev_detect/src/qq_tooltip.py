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
from PyQt5.QtWidgets import QMenu, QMessageBox, QSystemTrayIcon, qApp, QToolTip, QListWidgetItem
from PyQt5.QtWidgets import QLabel, QListWidget, QPushButton, QHBoxLayout, QVBoxLayout, QDesktopWidget
from PyQt5.QtCore import QThread, pyqtSignal, QMetaObject, QCoreApplication, Qt, QRect, QTimer, QPoint
from PyQt5.QtGui import QIcon, QPainter, QColor, QBrush, QCursor
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
    
    def show_message_box(self):
        # 弹出消息框
        QToolTip.showText(QCursor.pos(), '你有新的消息')



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
        self.aboutAction.triggered.connect(self.showToolTip)
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
        
        self.trayIcon.messageClicked.connect(self.show_message_box)
        
        # 左键双击打开主界面
        self.trayIcon.activated[QSystemTrayIcon.ActivationReason].connect(self.openMainWindow)
        
        # 允许托盘菜单显示
        self.trayIcon.show()

    def showToolTip(self):
        self.messageTipForm = Ui_MessageTipForm()
        
        rect = self.trayIcon.geometry()
        trayIconPos = QPoint(rect.left() + rect.width()/2-1, rect.top() + rect.height()/2-1)
        leftBottom = QPoint(trayIconPos.x() - self.messageTipForm.width()/2+1, trayIconPos.y() - 19)
        logger.info('原始位置: {}'.format(leftBottom))
        self.messageTipForm.setFixedLeftBottom(leftBottom)
        
        logger.info(rect)
        logger.info('{} {} {} {}'.format(rect.left(), rect.width(), rect.top(), rect.height()))
        logger.info('{} {}'.format(rect.left() + rect.width()/2-1, rect.top() + rect.height()/2-1))
        logger.info('{} {}'.format(trayIconPos.x() - self.messageTipForm.width()/2+1, trayIconPos.y() - 19))
        
        self.messageTipForm.addToTipList('张三', '来电话啦')
        self.messageTipForm.addToTipList('李四', '床前明月光')
        self.messageTipForm.addToTipList('王麻子', '当前是黑屏状态')
        self.messageTipForm.show()

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

class Ui_MessageTipForm(QWidget):
    """消息提示窗口类
    """
    
    def __init__(self):
        super().__init__()
    
        self.orignalHeight = None
        self.orignalPoint  = None
        self.messageCountRole = Qt.UserRole + 0x01
        self.messageTextRole  = Qt.UserRole + 0x02
        
        self.initUI()

    def initUI(self):
        """初始化界面
        """
        
        # 窗口属性
        self.setWindowFlags(Qt.FramelessWindowHint | Qt.WindowTitleHint | Qt.WindowMinimizeButtonHint | Qt.WindowMaximizeButtonHint)

        # 创建 QLabel
        self.label = QLabel('新消息(0)', self)
        self.label.setMaximumHeight(18)

        # 创建 QListWidget
        self.listWidget = QListWidget(self)
        self.listWidget.itemClicked.connect(self.itemClickedSlot)
        
        # 去除item选中时的虚线边框
        self.listWidget.setFocusPolicy(Qt.NoFocus)
        
        #self.listWidget.setFixedHeight(0)       # 将高度设置为0
        self.listWidget.setMaximumHeight(0)
        logger.info(self.listWidget.height())   # 默认为30


        # 创建 QPushButton
        self.ignoreAllBtn = QPushButton('忽略全部', self)
        self.ignoreAllBtn.clicked.connect(self.ignoreAllSlot)
        self.openAllBtn = QPushButton('打开全部', self)
        self.openAllBtn.clicked.connect(self.openAllSlot)

        # 创建 QHBoxLayout 布局
        self.hbox = QHBoxLayout()
        self.hbox.addWidget(self.ignoreAllBtn)
        self.hbox.addWidget(self.openAllBtn)

        # 创建 QVBoxLayout 布局
        vbox = QVBoxLayout()
        vbox.addWidget(self.label)
        vbox.addWidget(self.listWidget)
        vbox.addLayout(self.hbox)

        # 设置窗口布局
        self.setLayout(vbox)

        
        
        # 起始高度不包含listWidget
        self.orignalHeight = self.label.height() + self.ignoreAllBtn.height()
        # 计算窗口内容的高度
        frameGeometryHeight = self.frameGeometry().height()
        frameSizeHeight = self.frameSize().height()
        contentHeight = frameGeometryHeight - frameSizeHeight
        logger.info('orignalHeight: {}, window height: {} {} {}'.format(self.orignalHeight, 
            frameGeometryHeight, frameSizeHeight, contentHeight))
            
        # 默认位置宽度和高度
        logger.info('label: {}, listWidget: {}, hbox: {}'.format(self.label.height(), self.listWidget.height(), self.ignoreAllBtn.height()))
        
        logger.info('高度: {}'.format(self.frameGeometry().height()))
        logger.info(self.frameSize().height())
        logger.info(self.geometry().height())
        logger.info(self.height())
        logger.info(vbox.sizeHint().height())
        logger.info(self.hbox.sizeHint().height())
        
        self.setGeometry(0, 0, 50, self.orignalHeight)
        self.setWindowTitle('消息提示窗口')

    def calcListWidgetHeight(self):
        """
        """
        
        listWidgetHeight = sum([self.listWidget.sizeHintForRow(i) for i in range(self.listWidget.count())]) + self.listWidget.frameWidth() * 2
        #return sum([self.listWidget.sizeHintForRow(i) for i in range(self.listWidget.count())])
        return listWidgetHeight

    def setFixedLeftBottom(self, leftBottom):
        """
        """
        
        self.orignalPoint = leftBottom

    def ignoreAllSlot(self):
        """
        """
        
        for i in range(self.listWidget.count()):
            item = self.listWidget.item(i);
            self.listWidget.removeItemWidget(item);

        # 修改消息盒子的长度，恢复最初的高度
        self.resizeHeight(self.orignalHeight)
        #emit signal_NoMessage();
        
    def openAllSlot(self):
        """
        """
        
        for i in range(self.listWidget.count()):
            item = self.listWidget.item(i);
            self.listWidget.removeItemWidget(item);
            self.itemClickedSlot(item);
        #emit signal_NoMessage();

    def itemClickedSlot(self, item):
        """
        """
        
        if item == None:
            logger.error('no item')
            return
        
        text = item.data(self.messageTextRole)
        logger.info(type(text))
        #self.listWidget.removeItemWidget(item)
        self.listWidget.takeItem(self.listWidget.row(item))
        logger.info('getMessageCount: {}'.format(self.getMessageCount()))

        # 修改消息盒子的长度，每阅读一条消息，减少34pix
        self.resizeHeight();
        
        desktop = QDesktopWidget()
        logger.debug('桌面大小: {}'.format(desktop.screenGeometry()))
        # D:\Github\GitBook\gitbook\Python\pyqt5.md
        #screenGeometry = desktop.screenGeometry()
        #centerX = (screenGeometry.x() + screenGeometry.width() - self.width()) / 2
        #centerY = (screenGeometry.y() + screenGeometry.height() - self.height()) / 2
        #logger.info('中心位置:({}, {})'.format(centerX, centerY))
        #QMessageBox.warning(self, '消息', text).move(desktop.screenGeometry().center() - msgBox.rect().center())
        
        msgBox = QMessageBox(self)
        msgBox.setWindowTitle('消息')
        msgBox.setText(text)
        msgBox.setGeometry(0, 0, 100, 200)       # 设置对话框大小
        msgBox.move(desktop.screenGeometry().center() - msgBox.rect().center())
        msgBox.setIcon(QMessageBox.Information)  # 设置对话框类型为信息框
        msgBox.show()

        if self.getMessageCount() == 0:
            #emit signal_NoMessage();
            pass

    def getMessageCount(self):
        """
        """
        
        return self.listWidget.count()
    
    def addToTipList(self, name, text):
        """
        """
        
        item = QListWidgetItem(self.listWidget);
        item.setText(' {}'.format(name));
        item.setData(self.messageTextRole, text);
        self.listWidget.addItem(item);

        # 显示收到消息数量
        self.label.setText('新消息({})'.format(self.getMessageCount()));

        # 修改消息盒子的长度，每增加一条消息，增加34pix
        self.resizeHeight();

    def resizeHeight(self):
        """
        """
        
        # 设置高度为内容刚好的高度
        listWidgetHeight = self.calcListWidgetHeight()
        logger.info('listWidgetHeight: {}'.format(listWidgetHeight))
        self.listWidget.setMaximumHeight(listWidgetHeight)

        height = self.orignalHeight + listWidgetHeight + self.hbox.sizeHint().height() / 2
        
        self.resize(self.width(), height)
        # 根据新的大小移动窗口至原始位置
        logger.info(self.label.height())
        logger.info('消息提示窗口真实高度: {}, 计算高度: {}'.format(self.height(), height))
        logger.info('新位置: {} {}'.format(self.orignalPoint.x(), self.orignalPoint.y() - height))
        leftTop = QPoint(self.orignalPoint.x(), self.orignalPoint.y() - height)
        self.move(leftTop)

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