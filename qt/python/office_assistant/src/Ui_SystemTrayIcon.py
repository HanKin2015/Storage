# -*- coding: utf-8 -*-
"""
文 件 名: Ui_SystemTrayIcon.py
文件描述: 托盘类
作    者: HanKin
创建日期: 2023.04.04
修改日期：2023.05.25

Copyright (c) 2023 HanKin. All rights reserved.
"""

from Ui_MessageTipForm import *
import udev_detect_interface
import hack_interface
import screen_monitor_interface

class Ui_SystemTrayIcon(QSystemTrayIcon):
    """托盘类
    """

    show_mainwindow_signal = pyqtSignal()
    standalone = False
    unreadMessageCount = 0
    lastIsTrayIconHover = False
    ip, mac   = hack_interface.get_ip_mac_address()
    user_name = hack_interface.get_login_user_name()

    def __init__(self, parent=None):
        """托盘菜单列表初始化
        """
        
        super().__init__(parent)

        self.initThreadTimer()
        self.initUI()

        # 构建托盘对象
        self.trayIcon = QSystemTrayIcon()
        # 本来应该由父进程创建图片，但是单独执行会不存在
        if parent == None:
            self.standalone = True
            tmp = open(OFFICE_ASSISTANT_ICO, 'wb+')
            tmp.write(base64.b64decode(resource.office_assistant_ico))
            tmp.close()
        self.trayIconIcon = QIcon(OFFICE_ASSISTANT_ICO)
        self.trayIcon.setIcon(self.trayIconIcon)
        self.trayIcon.setContextMenu(self.trayIconMenu)
        self.trayIcon.setToolTip(APP_NAME)
        
        # 鼠标悬浮显示提示框
        self.trayIcon.messageClicked.connect(self.showMessageBox)
        self.trayIconMenu.hovered.connect(self.showTooltip)
        
        # 左键双击打开主界面
        self.trayIcon.activated[QSystemTrayIcon.ActivationReason].connect(self.openMainWindow)
        
        # 允许托盘菜单显示
        self.trayIcon.show()
        
        # 初始化消息提示框
        self.initMessageTipForm()
    
    def initThreadTimer(self):
        """初始化各种线程定时器
        """
        
        # 监控屏幕线程
        self.monitorScreen = screen_monitor_interface.Thread_MonitorScreen()
        self.monitorScreen.ip = self.ip
        self.monitorScreen.mac = self.mac
        self.monitorScreen.user_name = self.user_name
        self.monitorScreen.recv_msg_signal.connect(self.recvMsgSignalSlot)
        self.monitorScreen.stop_monitor_signal.connect(self.startMonitorScreen)
        
        # USB设备检测线程
        self.udevDetect = udev_detect_interface.Thread_UdevDetect()
        self.udevDetect.hotplugSignal.connect(self.hotplugSignalSlot)
        self.udevDetect.getUdevInfoListSignal.connect(self.getUdevInfoListSlot)

        # 托盘图标闪烁定时器
        self.flashTimer = QTimer()
        self.flashTimer.timeout.connect(self.flashingTrayIconSlot)

        # 检测鼠标位置定时器
        self.checkMousePosTimer = QTimer()
        self.checkMousePosTimer.timeout.connect(self.checkTrayIconHoverSlot)
        self.checkMousePosTimer.setInterval(200)
    
    def initUI(self):
        """初始化菜单列表界面
        """
        
        # 初始化菜单单项
        self.settingClientAddressAction = QAction("设置客户端地址")
        self.settingClientAddressAction.setIcon(QIcon(CAMERA_MONITOR_ICO))
        self.settingClientAddressAction.setShortcut(Qt.CTRL + Qt.Key_S)
        self.startMonitorScreenAction = QAction("开启监控屏幕")
        self.startMonitorScreenAction.setIcon(QIcon(CAMERA_MONITOR_ICO))
        self.startMonitorScreenAction.setShortcut(Qt.CTRL + Qt.Key_M)
        self.startMonitorScreenAction.setToolTip('3秒监控间隔，连续5次触发消息，连续20次停止监控')
        self.showScreenshotAreaAction = QAction("显示截图区域")
        self.showScreenshotAreaAction.setIcon(QIcon(CAMERA_MONITOR_ICO))
        self.showScreenshotAreaAction.setShortcut(Qt.CTRL + Qt.Key_D)
        
        self.startUdevDetectAction = QAction("开启USB设备检测")
        self.startUdevDetectAction.setIcon(QIcon(USB_CHECK_ICO))
        self.startUdevDetectAction.setShortcut(Qt.CTRL + Qt.Key_C)
        
        self.testMsgAction = QAction("测试消息")
        self.testMsgAction.setIcon(QIcon(TEST_PNG))
        self.testMsgAction.setShortcut(Qt.CTRL + Qt.Key_T)
        self.ipMacAddressAction = QAction('本机地址')
        self.ipMacAddressAction.setToolTip('{} {}'.format(self.ip, self.mac))
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
        self.startUdevDetectAction.triggered.connect(self.startUdevDetect)
        self.testMsgAction.triggered.connect(self.testMsgSlot)
        self.aboutAction.triggered.connect(self.about)
        self.quitAppAction.triggered.connect(self.quitApp)

        # 初始化托盘菜单列表
        self.trayIconMenu = QMenu()
        self.trayIconMenu.addAction(self.settingClientAddressAction)
        self.trayIconMenu.addAction(self.startMonitorScreenAction)
        self.trayIconMenu.addAction(self.showScreenshotAreaAction)
        self.trayIconMenu.addSeparator()    # 分割线
        self.trayIconMenu.addAction(self.startUdevDetectAction)
        self.trayIconMenu.addSeparator()    # 分割线
        self.trayIconMenu.addAction(self.testMsgAction)
        self.trayIconMenu.addAction(self.ipMacAddressAction)
        self.trayIconMenu.addSeparator()    # 分割线
        self.trayIconMenu.addAction(self.aboutAction)
        self.trayIconMenu.addAction(self.quitAppAction)
    
    def showTooltip(self):
        """在鼠标悬停在菜单项上时显示提示框
        """
        
        action = self.trayIconMenu.activeAction()
        if action is not None:
            QToolTip.showText(QCursor.pos(), action.toolTip())
            
    def flashingTrayIconSlot(self):
        """托盘消息图标闪烁
        """
        
        if self.trayIcon.isVisible():
            if self.trayIcon.icon().cacheKey() == self.trayIconIcon.cacheKey():
                self.trayIcon.setIcon(QIcon(MSG_PNG))
            else:
                self.trayIcon.setIcon(self.trayIconIcon)
    
    def checkTrayIconHoverSlot(self):
        """检测鼠标位置
        """
        
        # 获取消息盒子全局rect
        pos  = self.messageTipForm.mapToGlobal(QPoint(0, 0))
        size = self.messageTipForm.size();
        rectForm = QRect(pos, size);

        # 若鼠标在图片图标内，或鼠标在消息盒子内
        rect = self.trayIcon.geometry()
        logger.debug('{} {} {}'.format(rect, QCursor.pos(), rectForm))
        #if rect.contains(QCursor.pos()) or rectForm.contains(QCursor.pos()):
        if rect.contains(QCursor.pos()):
            self.lastIsTrayIconHover = True
            logger.debug('mouse hover tray icon')
            if self.messageTipForm.isHidden():
                self.messageTipForm.show()
                self.messageTipForm.activateWindow()
        elif self.lastIsTrayIconHover and rectForm.contains(QCursor.pos()):
            logger.debug('mouse hover message tip form')
            if self.messageTipForm.isHidden():
                self.messageTipForm.show()
                self.messageTipForm.activateWindow()
        else:
            self.lastIsTrayIconHover = False
            self.messageTipForm.hide()
        
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

    def showMessageBox(self):
        """弹出消息框
        """
        
        QToolTip.showText(QCursor.pos(), '你有新的消息')

    def showScreenshotArea(self):
        """显示截图区域
        """
        
        # 创建子窗口，并将主窗口设置为其父窗口
        self.subwindow = screen_monitor_interface.ScreenShotArea()
        # 显示子窗口
        self.subwindow.show()

    def startFlashingTrayIconSlot(self, message):
        """开启图标闪烁
        """

        logger.info('message is {}'.format(message))
        if self.trayIcon.supportsMessages() == True and self.trayIcon.isSystemTrayAvailable() == True:
            self.trayIcon.showMessage('新消息', message, QIcon(MSG_PNG), 5000)
            self.unreadMessageCount += 1  # 未读消息数加1
            logger.info('there are {} unread messages now'.format(self.unreadMessageCount))
            
            if not self.flashTimer.isActive():
                self.flashTimer.start(500)       # 开启托盘图标闪烁定时器
            if not self.checkMousePosTimer.isActive():
                self.checkMousePosTimer.start()  # 200毫秒间隔
        else:
            logger.error('trayIcon supportsMessages {}, isSystemTrayAvailable {}'.format(self.trayIcon.supportsMessages(), self.trayIcon.isSystemTrayAvailable()))
    
    def recvMsgSignalSlot(self, text):
        """屏幕监控线程发送消息过来显示消息
        """
        
        logger.info(text)
        text_list = text.split(',')
        name = text_list[3]
        self.messageTipForm.addToTipList(name, text)
    
    def stopFlashingTrayIconSlot(self):
        """关闭图标闪烁
        """
        
        if self.flashTimer.isActive():
            self.flashTimer.stop()           # 停止托盘图标闪烁定时器
        if self.checkMousePosTimer.isActive():
            self.checkMousePosTimer.stop()   # 停止检测鼠标位置定时器

        self.unreadMessageCount = 0      # 未读消息数清零
        self.trayIcon.setIcon(self.trayIconIcon)   # 设置已读消息图标
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
    
    def hotplugSignalSlot(self, text):
        """USB设备拔插信号槽函数
        """

        self.messageTipForm.addToTipList(text, text)
    
    def getUdevInfoListSlot(self):
        """获取USB信息列表槽函数
        """
        
        self.udevDetect.udev_info_list = udev_detect_interface.get_udev_info_list()
    
    def testMsgSlot(self):
        """测试消息槽函数
        """

        current_time = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime())
        text = '{},{},{},{} 这是一条测试信息'.format(self.user_name, self.ip, self.mac, current_time)
        text_list = text.split(',')
        name = text_list[3]
        self.messageTipForm.addToTipList(name, text)

    def settingClientAddress(self):
        """设置服务器
        """
        
        text, ok = QInputDialog.getText(None, '设置客户端地址', '请输入地址:')
        if ok:
            self.monitorScreen.clientAddress = str(text)
            logger.info('setting client address success, {}'.format(text))
            current_time = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime())
            msg = '{},{},{},{} 服务端下发的测试消息'.format(self.user_name, self.ip, self.mac, current_time)
            datagram = msg.encode()
            self.monitorScreen.sock.writeDatagram(datagram, QHostAddress(self.monitorScreen.clientAddress), 6666)

    def startMonitorScreen(self, flag=False):
        """初始化显示为开启监控屏幕，即默认是关闭状态
        flag是关闭监控屏幕标记，防止线程消息未及时反馈过来，提前设置了is_on为False，导致现有判断错误
        """

        if self.monitorScreen.is_on == True and flag == False:
            logger.info('stop monitor screen')
            self.monitorScreen.is_on = False
            self.startMonitorScreenAction.setText('开启监控屏幕')
        else:
            if self.monitorScreen.clientAddress == None:
                QMessageBox.warning(None, '警告', '请先设置客户端地址!', QMessageBox.Yes)
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
        
        # 自定义询问对话框
        reply = QMessageBox()
        reply.setWindowTitle('退出确认')
        reply.setText('是否确认退出?')
        reply.setIcon(QMessageBox.Question)
        yes_btn = reply.addButton('是', QMessageBox.YesRole)
        no_btn  = reply.addButton('否', QMessageBox.NoRole)
        reply.exec_()
        if reply.clickedButton() == yes_btn:
            logger.info('******** stop ********')
            if self.standalone:
                os.remove(OFFICE_ASSISTANT_ICO)
            qApp.quit()
        else:
            pass
        
        """
        checkFlag = QMessageBox.information(None, "退出确认", "是否确认退出？",
                                                      QMessageBox.Yes | QMessageBox.No)
        if checkFlag == QMessageBox.Yes:
            logger.info('******** stop ********')
            qApp.quit()
        else:
            pass
        """
        
    def showMessage(self, title, message, icon=QSystemTrayIcon.Information, duration=5000):
        self.showMessage(title, message, icon, duration)

def main():
    """主函数
    """

    app = QApplication(sys.argv)
    systemTrayIcon = Ui_SystemTrayIcon()
    #systemTrayIcon.show()
    # 关闭全部窗口后程序不退出
    app.setQuitOnLastWindowClosed(False)
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