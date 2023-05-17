# -*- coding: utf-8 -*-
"""
文 件 名: office_assistant.py
文件描述: 办公助手
作    者: HanKin
创建日期: 2023.04.04
修改日期：2023.04.04

Copyright (c) 2023 HanKin. All rights reserved.
"""

from Ui_MessageTipForm import *

class Ui_SystemTrayIcon(QSystemTrayIcon):
    """托盘类
    """

    show_mainwindow_signal = pyqtSignal()

    def __init__(self, parent=None):
        super().__init__(parent)

        # 初始化菜单单项
        self.settingClientAddressAction = QAction("设置客户端地址")
        self.settingClientAddressAction.setIcon(QIcon(CAMERA_MONITOR_ICO))
        self.settingClientAddressAction.setShortcut(Qt.CTRL + Qt.Key_S)
        self.startMonitorScreenAction = QAction("开启监控屏幕")
        self.startMonitorScreenAction.setIcon(QIcon(CAMERA_MONITOR_ICO))
        self.startMonitorScreenAction.setShortcut(Qt.CTRL + Qt.Key_M)
        self.showScreenshotAreaAction = QAction("显示截图区域")
        self.showScreenshotAreaAction.setIcon(QIcon(CAMERA_MONITOR_ICO))
        self.showScreenshotAreaAction.setShortcut(Qt.CTRL + Qt.Key_D)
        
        self.startUdevDetectAction = QAction("开启USB设备检测")
        self.startUdevDetectAction.setIcon(QIcon(USB_CHECK_ICO))
        self.startUdevDetectAction.setShortcut(Qt.CTRL + Qt.Key_C)
        
        self.testMsgAction = QAction("测试消息")
        self.testMsgAction.setIcon(QIcon(TEST_PNG))
        self.testMsgAction.setShortcut(Qt.CTRL + Qt.Key_T)
        self.aboutAction = QAction("关于(&N)")
        self.aboutAction.setIcon(QIcon(ABOUT_PNG))
        self.aboutAction.setShortcut(Qt.CTRL + Qt.Key_A)
        self.quitAppAction = QAction("退出")
        self.quitAppAction.setIcon(QIcon(EXIT_PNG))
        self.quitAppAction.setShortcut(Qt.CTRL + Qt.Key_Q)

        # 菜单单项连接方法
        self.settingClientAddressAction.triggered.connect(self.settingClientAddress)
        self.startMonitorScreenAction.triggered.connect(self.startMonitorScreen)
        self.showScreenshotAreaAction.triggered.connect(self.showScreenshotArea)
        self.testMsgAction.triggered.connect(self.testMsgSlot)
        self.aboutAction.triggered.connect(self.about)
        self.quitAppAction.triggered.connect(self.quitApp)

        # 初始化菜单列表
        self.trayIconMenu = QMenu()
        self.trayIconMenu.addAction(self.settingClientAddressAction)
        self.trayIconMenu.addAction(self.startMonitorScreenAction)
        self.trayIconMenu.addAction(self.showScreenshotAreaAction)
        self.trayIconMenu.addSeparator()
        self.trayIconMenu.addAction(self.startUdevDetectAction)
        self.trayIconMenu.addSeparator()
        self.trayIconMenu.addAction(self.testMsgAction)
        self.trayIconMenu.addSeparator()
        self.trayIconMenu.addAction(self.aboutAction)
        self.trayIconMenu.addAction(self.quitAppAction)

        # 构建菜单UI
        self.trayIcon = QSystemTrayIcon()
        self.trayIcon.setContextMenu(self.trayIconMenu)
        self.trayIcon.setIcon(QIcon(OFFICE_ASSISTANT_ICO))
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
        trayIconPos = QPoint(rect.left() + int(rect.width()/2)-1, rect.top() + int(rect.height()/2)-1)
        leftBottom = QPoint(trayIconPos.x() - int(self.messageTipForm.width()/2)+1, trayIconPos.y() - 19)
        logger.debug('原始位置: {}'.format(leftBottom))
        self.messageTipForm.setFixedLeftBottom(leftBottom)
        
        # 测试使用
        #self.messageTipForm.addToTipList('张三', '来电话啦')
        
        # 矫正位置
        #self.messageTipForm.resizeHeight()
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
            self.show_mainwindow_signal.emit()
        elif reason == QSystemTrayIcon.Trigger:
            pass

    def show_message_box(self):
        """弹出消息框
        """
        
        QToolTip.showText(QCursor.pos(), '你有新的消息')

    def showScreenshotArea(self):
        """显示截图区域
        """
        
        # 创建子窗口，并将主窗口设置为其父窗口
        self.subwindow = ScreenShotArea()
        # 显示子窗口
        self.subwindow.show()

    def startFlashingTrayIconSlot(self, message):
        """开启图标闪烁
        """

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
        self.trayIcon.setIcon(self.usbCameraMonitorToolIcon)   # 设置已读消息图标
        self.messageTipForm.hide()
    
    def testMsgSlot(self):
        """测试消息槽函数
        """
        
        text = self.msgPackage('这是一条测试信息')
        text_list = text.split(',')
        name = text_list[3]
        self.messageTipForm.addToTipList(name, text)

    def settingClientAddress(self):
        """设置服务器
        """
        
        text, ok = QInputDialog.getText(None, '设置客户端地址', '请输入地址:')
        if ok:
            self.clientAddress = str(text)
            msg = '服务端下发的测试消息'
            datagram = msg.encode()
            self.sock.writeDatagram(datagram, QHostAddress(self.clientAddress), 6666)

    def startMonitorScreen(self, flag=False):
        """初始化显示为开启监控屏幕，即默认是关闭状态
        flag是关闭监控屏幕标记，防止线程消息未及时反馈过来，提前设置了is_on为False，导致现有判断错误
        """

        if self.monitorScreen.is_on == True and flag == False:
            logger.info('stop monitor screen')
            self.monitorScreen.is_on = False
            self.startMonitorScreenAction.setText('开启监控屏幕')
        else:
            if self.clientAddress == None:
                QMessageBox.warning(self.ui, '警告', '请先设置客户端地址!', QMessageBox.Yes)
                return
            logger.info('start monitor screen')
            self.monitorScreen.is_on = True
            self.monitorScreen.start()
            self.startMonitorScreenAction.setText('关闭监控屏幕')
        

    def about(self):
        """关于
        """

        aboutText = '{} V{}\n\n{}'.format(resource.InternalName, resource.ProductVersion, resource.LegalCopyright)
        QMessageBox.about(None, resource.FileDescription, aboutText)
        
    def quitApp(self):
        """包含二次确认的退出
        """
        
        checkFlag = QMessageBox.information(None, "退出确认", "是否确认退出？",
                                                      QMessageBox.Yes | QMessageBox.No)
        if checkFlag == QMessageBox.Yes:
            logger.info('******** stop ********')
            qApp.quit()
        else:
            pass
    
    def showMessage(self, title, message, icon=QSystemTrayIcon.Information, duration=5000):
        self.showMessage(title, message, icon, duration)

def main():
    """主函数
    """

    app = QApplication(sys.argv)
    systemTrayIcon = Ui_SystemTrayIcon('../img/office_assistant.png')
    systemTrayIcon.show()
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