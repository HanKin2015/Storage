# -*- coding: utf-8 -*-
"""
文 件 名: udev_detect_tray.py
文件描述: usb设备检测（基于windows系统）
作    者: HanKin
创建日期: 2023.02.27
修改日期：2023.03.10

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
        self.unreadMessageCount = 0
        
        # 图片打包
        self.py2ico(ico.udev_detect_ico, UDEV_DETECT_ICO)
        self.py2ico(ico.msg_ico, MSG_ICO)
        self.udevDetectIcon = QIcon(UDEV_DETECT_ICO)
        self.msgIcon = QIcon(MSG_ICO)

        # 托盘图标闪烁定时器
        self.flashTimer = QTimer(self.ui)
        self.flashTimer.timeout.connect(self.flashingTrayIconSlot)

        # 检测鼠标位置定时器
        self.checkMousePosTimer = QTimer(self.ui)
        self.checkMousePosTimer.timeout.connect(self.checkTrayIconHoverSlot)
        self.checkMousePosTimer.setInterval(200)

    def flashingTrayIconSlot(self):
        """托盘消息图标闪烁
        """
        
        if self.trayIcon.isVisible():
            if self.trayIcon.icon().cacheKey() == self.udevDetectIcon.cacheKey():
                self.trayIcon.setIcon(self.msgIcon)
            else:
                self.trayIcon.setIcon(self.udevDetectIcon)
    
    def checkTrayIconHoverSlot(self):
        """检测鼠标位置
        """
        
        # 获取消息盒子全局rect
        pos  = self.messageTipForm.mapToGlobal(QPoint(0, 0))
        size = self.messageTipForm.size();
        rectForm = QRect(pos, size);

        # 若鼠标在图片图标内，或鼠标在消息盒子内
        rect = self.trayIcon.geometry()
        logger.info('{} {} {}'.format(rect, QCursor.pos(), rectForm))
        if rect.contains(QCursor.pos()) or rectForm.contains(QCursor.pos()):
            logger.debug('mouse hover tray icon')
            if self.messageTipForm.isHidden():
                self.messageTipForm.show()
                self.messageTipForm.activateWindow()
        else:
            self.messageTipForm.hide()

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

        # 添加一条消息
        addMsgBtn = QPushButton(self.ui)
        addMsgBtn.setText('添加一条消息')
        addMsgBtn.clicked.connect(self.addMsgSlot)

        # 配置最小化
        self.setTrayIcon()
        
        # QMessageBox第一次打开不居中
        #self.ui.setWindowFlags(Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.Tool)
        #self.ui.setAttribute(Qt.WA_TranslucentBackground)
        self.ui.show()
        #self.ui.hide()

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
        """弹出消息框
        """
        
        QToolTip.showText(QCursor.pos(), '你有新的消息')

    def addMsgSlot(self):
        """测试使用，添加一条消息
        """
        
        current_time = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime())
        text = '{} 黑屏状态'.format(current_time)
        self.messageTipForm.addToTipList(text, text)

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
        self.testMsgAction.triggered.connect(self.startFlashingTrayIconSlot)
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
        
        self.trayIcon.messageClicked.connect(self.show_message_box)
        
        # 左键双击打开主界面
        self.trayIcon.activated[QSystemTrayIcon.ActivationReason].connect(self.openMainWindow)
        
        # 允许托盘菜单显示
        self.trayIcon.show()
        
        # 初始化消息提示框
        self.initMessageTipForm()

    def initMessageTipForm(self):
        """初始化消息提示框
        """
        
        self.messageTipForm = Ui_MessageTipForm()
        self.messageTipForm.startFlashingTrayIconSignal.connect(self.startFlashingTrayIconSlot)
        self.messageTipForm.stopFlashingTrayIconSignal.connect(self.stopFlashingTrayIconSlot)
        
        rect = self.trayIcon.geometry()
        trayIconPos = QPoint(rect.left() + rect.width()/2-1, rect.top() + rect.height()/2-1)
        leftBottom = QPoint(trayIconPos.x() - self.messageTipForm.width()/2+1, trayIconPos.y() - 19)
        logger.info('原始位置: {}'.format(leftBottom))
        self.messageTipForm.setFixedLeftBottom(leftBottom)
        
        logger.info(rect)
        logger.info('{} {} {} {}'.format(rect.left(), rect.width(), rect.top(), rect.height()))
        logger.info('{} {}'.format(rect.left() + rect.width()/2-1, rect.top() + rect.height()/2-1))
        logger.info('{} {}'.format(trayIconPos.x() - self.messageTipForm.width()/2+1, trayIconPos.y() - 19))
        #self.messageTipForm.setHidden(True)
        
        # 测试使用
        #self.messageTipForm.addToTipList('张三', '来电话啦')
        #self.messageTipForm.show()

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
            pass

    def startFlashingTrayIconSlot(self, action=''):
        """开启图标闪烁
        """

        message = '这是一条测试消息'
        if action == 'out':
            message = '有USB设备拔出'
        elif action == 'in':
            message = '有USB设备插入'
        logger.info('message is {}'.format(message))
        
        if self.trayIcon.supportsMessages() == True and self.trayIcon.isSystemTrayAvailable() == True:
            self.trayIcon.showMessage('新消息', message, self.msgIcon, 5000)
            self.unreadMessageCount += 1  # 未读消息数加1
            logger.info('there are {} unread messages now'.format(self.unreadMessageCount))
            
            if not self.flashTimer.isActive():
                self.flashTimer.start(500)       # 开启托盘图标闪烁定时器
            if not self.checkMousePosTimer.isActive():
                self.checkMousePosTimer.start()  # 200毫秒间隔
        else:
            logger.error('trayIcon supportsMessages {}, isSystemTrayAvailable {}'.format(self.trayIcon.supportsMessages(), self.trayIcon.isSystemTrayAvailable()))
        
    def stopFlashingTrayIconSlot(self):
        """关闭图标闪烁
        """
        
        if self.flashTimer.isActive():
            self.flashTimer.stop()           # 停止托盘图标闪烁定时器
        if self.checkMousePosTimer.isActive():
            self.checkMousePosTimer.stop()   # 停止检测鼠标位置定时器

        self.unreadMessageCount = 0      # 未读消息数清零
        self.trayIcon.setIcon(self.udevDetectIcon)   # 设置已读消息图标
        self.messageTipForm.hide()

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
    
    startFlashingTrayIconSignal = pyqtSignal(str)
    stopFlashingTrayIconSignal  = pyqtSignal()
    
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

        # 设置QWidget的背景色和边框
        #self.setStyleSheet('''
        #    QWidget {
        #        background-color: #f0f0f0;
        #        border: 1px solid #ccc;
        #    }
        #''')

        # 创建 QLabel
        self.label = QLabel('新消息(0)', self)
        #self.label.setMaximumHeight(18)
        self.label.setContentsMargins(0, 0, 0, 0)
        # 设置样式表
        self.label.setStyleSheet('''
            QLabel {
                margin-top: 0px;
                margin-bottom: 0px;
                padding: 0px;
            }
        ''')

        # 创建 QListWidget
        self.listWidget = QListWidget(self)
        self.listWidget.itemClicked.connect(self.itemClickedSlot)
        
        # 设置样式表
        self.listWidget.setStyleSheet('''
            QListWidget {
                border: none;
            }
        ''')
        
        # 去除item选中时的虚线边框
        self.listWidget.setFocusPolicy(Qt.NoFocus)
        
        #self.listWidget.setFixedHeight(0)       # 将高度设置为0
        self.listWidget.setMaximumHeight(0)
        logger.debug(self.listWidget.height())   # 默认为30


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

        #vbox.setSpacing(0)
        
        
        # 起始高度不包含listWidget
        self.orignalHeight = 88
        # 计算窗口内容的高度
        frameGeometryHeight = self.frameGeometry().height()
        frameSizeHeight = self.frameSize().height()
        contentHeight = frameGeometryHeight - frameSizeHeight
        logger.debug('orignalHeight: {}, window height: {} {} {}'.format(self.orignalHeight, 
            frameGeometryHeight, frameSizeHeight, contentHeight))
            
        # 默认位置宽度和高度
        logger.info('label: {}, listWidget: {}, hbox: {}'.format(self.label.height(), self.listWidget.height(), self.ignoreAllBtn.height()))
        
        logger.info('高度: {}'.format(self.frameGeometry().height()))
        logger.info(self.frameSize().height())
        logger.info(self.geometry().height())
        logger.info(self.height())
        logger.info(vbox.sizeHint().height())
        logger.info(self.hbox.sizeHint().height())
        
        self.setGeometry(0, 0, 210, self.orignalHeight)
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
        
        # 必须是倒序否则会删除不全有问题
        for i in range(self.listWidget.count() - 1, -1, -1):
            item = self.listWidget.item(i);
            # 用于从列表中删除一个项，并释放与该项相关联的小部件
            #self.listWidget.removeItemWidget(item);
            
            # 用于从列表中删除一个项，listWidget.count()会变化
            self.listWidget.takeItem(self.listWidget.row(item))
            
            # 只能删除一个修改一次高度，否则只会resize成删除一个的高度
            # 修改消息盒子的长度，恢复最初的高度
            self.resizeHeight()
        self.stopFlashingTrayIconSignal.emit()
        
    def openAllSlot(self):
        """
        """
        
        for i in range(self.listWidget.count() - 1, -1, -1):
            item = self.listWidget.item(i);
            self.itemClickedSlot(item);

    def itemClickedSlot(self, item):
        """
        """
        
        if item == None:
            logger.error('no item')
            return
        
        text = item.data(self.messageTextRole)
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
        
        #msgBox = QMessageBox(self)
        #msgBox.setWindowTitle('消息')
        #msgBox.setText(text)
        #msgBox.setGeometry(0, 0, 100, 200)       # 设置对话框大小
        #msgBox.move(desktop.screenGeometry().center() - msgBox.rect().center())
        #msgBox.setIcon(QMessageBox.Information)  # 设置对话框类型为信息框
        #msgBox.show()

        if self.getMessageCount() == 0:
            self.stopFlashingTrayIconSignal.emit()

    def getMessageCount(self):
        """
        """
        
        return self.listWidget.count()
    
    def addToTipList(self, name, text):
        """
        """
        
        item = QListWidgetItem(self.listWidget)
        item.setText(' {}'.format(name))
        item.setData(self.messageTextRole, text)
        self.listWidget.addItem(item)

        # 修改消息盒子的长度，每增加一条消息，增加34pix
        self.resizeHeight();
        self.startFlashingTrayIconSignal.emit('in')

    def resizeHeight(self):
        """
        """
        
         # 显示收到消息数量
        self.label.setText('新消息({})'.format(self.getMessageCount()));
        
        listWidgetHeight = self.calcListWidgetHeight()
        self.listWidget.setMaximumHeight(listWidgetHeight)
        
        height = self.orignalHeight + listWidgetHeight
        logger.debug('one row listWidget height: {}, {}'.format(self.listWidget.sizeHintForRow(0),
            self.listWidget.frameWidth()))

        self.resize(self.width(), int(height))
        logger.info('消息提示窗口真实高度: {}, 计算高度: {}'.format(self.height(), int(height)))
        logger.info('新位置: {} {}'.format(self.orignalPoint.x(), self.orignalPoint.y() - int(height)))
        
        # 根据新的大小移动窗口至原始位置
        leftTop = QPoint(self.orignalPoint.x(), self.orignalPoint.y() - self.height())
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