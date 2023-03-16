# -*- coding: utf-8 -*-
"""
文 件 名: usb_camera_monitor_tool.py
文件描述: USB摄像头监控工具
作    者: HanKin
创建日期: 2023.02.24
修改日期：2023.03.07

Copyright (c) 2023 HanKin. All rights reserved.
"""

from Ui_MessageTipForm import *

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
        self.lastIsTrayIconHover = False
        
        # pyinstaller打包图片
        self.py2ico(resource.usb_camera_monitor_tool_ico, USB_CAMERA_MONITOR_TOOL_ICO)
        self.py2ico(resource.msg_ico, MSG_ICO)
        self.usbCameraMonitorToolIcon = QIcon(USB_CAMERA_MONITOR_TOOL_ICO)
        self.msgIcon = QIcon(MSG_ICO)
        
        # 接收消息
        self.sock = QUdpSocket()
        #self.sock.bind(QHostAddress.LocalHost, 6666)
        self.sock.bind(QHostAddress.Any, 6666)
        self.sock.readyRead.connect(self.readDataSlot)
        self.clientAddress = None
        
        # 监控屏幕线程
        self.monitorScreen = Thread_MonitorScreen()
        self.monitorScreen.msg_signal.connect(self.writeDataSlot)

        # 托盘图标闪烁定时器
        self.flashTimer = QTimer(self.ui)
        self.flashTimer.timeout.connect(self.flashingTrayIconSlot)

        # 检测鼠标位置定时器
        self.checkMousePosTimer = QTimer(self.ui)
        self.checkMousePosTimer.timeout.connect(self.checkTrayIconHoverSlot)
        self.checkMousePosTimer.setInterval(200)

    def readDataSlot(self):
        while self.sock.hasPendingDatagrams():
            datagram, host, port = self.sock.readDatagram(
                self.sock.pendingDatagramSize()
            )

            messgae = 'Date time: {}\nHost: {}\nPort: {}\n\n'.format(datagram.decode(), host.toString(), port)
            logger.debug(messgae)
            self.monitorSignalSlot(datagram.decode())

    def writeDataSlot(self, msg):
        """
        """

        if msg == '关闭监控屏幕':
            self.startMonitorScreen()
        datagram = msg.encode()
        #self.sock.writeDatagram(datagram, QHostAddress.LocalHost, 6666)
        #self.sock.writeDatagram(datagram, QHostAddress.Broadcast, 6666)
        self.sock.writeDatagram(datagram, QHostAddress(self.clientAddress), 6666)

    def monitorSignalSlot(self, text):
        """监控信号槽函数
        """

        self.messageTipForm.addToTipList(text, text)

    def flashingTrayIconSlot(self):
        """托盘消息图标闪烁
        """
        
        if self.trayIcon.isVisible():
            if self.trayIcon.icon().cacheKey() == self.usbCameraMonitorToolIcon.cacheKey():
                self.trayIcon.setIcon(self.msgIcon)
            else:
                self.trayIcon.setIcon(self.usbCameraMonitorToolIcon)
    
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

        # 去掉边框和置顶显示以及任务栏显示
        self.ui.setWindowFlags(Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.Tool)
        
        # 去掉背景框
        self.ui.setAttribute(Qt.WA_TranslucentBackground)
        
        # QMessageBox第一次打开不居中
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
        self.ui.setWindowIcon(self.usbCameraMonitorToolIcon)

    def show_message_box(self):
        """弹出消息框
        """
        
        QToolTip.showText(QCursor.pos(), '你有新的消息')

    def setTrayIcon(self):
        """最小化右键菜单
        """

        # 初始化菜单单项
        self.settingClientAddressAction = QAction("设置客户端地址")
        self.startMonitorScreenAction = QAction("开启监控屏幕")
        self.showScreenshotAreaAction = QAction("显示截图区域")
        self.testMsgAction = QAction("测试消息")
        self.aboutAction = QAction("关于(&N)")
        self.quitAppAction = QAction("退出")
        
        #添加一个图标
        self.aboutAction.setIcon(self.usbCameraMonitorToolIcon)
        
        #添加快捷键
        self.aboutAction.setShortcut(Qt.CTRL + Qt.Key_N)

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
        self.trayIconMenu.addSeparator()
        self.trayIconMenu.addAction(self.startMonitorScreenAction)
        self.trayIconMenu.addSeparator()
        self.trayIconMenu.addAction(self.showScreenshotAreaAction)
        self.trayIconMenu.addAction(self.testMsgAction)
        self.trayIconMenu.addSeparator()
        self.trayIconMenu.addAction(self.aboutAction)
        self.trayIconMenu.addAction(self.quitAppAction)

        # 构建菜单UI
        self.trayIcon = QSystemTrayIcon()
        self.trayIcon.setContextMenu(self.trayIconMenu)
        self.trayIcon.setIcon(self.usbCameraMonitorToolIcon)
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
            self.ui.showNormal()
            self.ui.activateWindow()
        elif reason == QSystemTrayIcon.Trigger:
            pass

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
        
        text = '这是一条测试信息'
        self.messageTipForm.addToTipList(text, text)

    def settingClientAddress(self):
        """设置服务器
        """
        
        text, ok = QInputDialog.getText(None, '设置客户端地址', '请输入地址:')
        if ok:
            self.clientAddress = str(text)
            msg = '服务端下发的测试消息'
            datagram = msg.encode()
            self.sock.writeDatagram(datagram, QHostAddress(self.clientAddress), 6666)

    def startMonitorScreen(self):
        """初始化显示为开启监控屏幕，即默认是关闭状态
        """

        if self.monitorScreen.is_on == False:
            if self.clientAddress == None:
                QMessageBox.warning(self.ui, '警告', '请先设置客户端地址!', QMessageBox.Yes)
                return
            logger.info('start monitor screen')
            self.monitorScreen.is_on = True
            self.monitorScreen.start()
            self.startMonitorScreenAction.setText('关闭监控屏幕')
        else:
            logger.info('stop monitor screen')
            self.monitorScreen.is_on = False
            self.startMonitorScreenAction.setText('开启监控屏幕')

    def about(self):
        """关于
        """

        aboutText = '{} V{}\n\n{}'.format(resource.InternalName, resource.ProductVersion, resource.LegalCopyright)
        QMessageBox.about(self.ui, resource.FileDescription, aboutText)
        
    def quitApp(self):
        """包含二次确认的退出
        """
        
        checkFlag = QMessageBox.information(self.ui, "退出确认", "是否确认退出？",
                                                      QMessageBox.Yes | QMessageBox.No)
        if checkFlag == QMessageBox.Yes:
            logger.info('******** stop ********\n')
            os.remove(USB_CAMERA_MONITOR_TOOL_ICO)
            os.remove(MSG_ICO)
            if os.path.exists(TMP_SCREENSHOT_PNG):
                os.remove(TMP_SCREENSHOT_PNG)
            qApp.quit()
        else:
            pass

class ScreenShotArea(QWidget):

    def __init__(self):
        super().__init__()

        # 设置窗口尺寸和背景色
        self.setGeometry(0, 0, 800, 600)
        self.setStyleSheet("background-color:transparent;")

        # 去掉边框和置顶显示以及任务栏显示
        self.setWindowFlags(Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.Tool)
        
        # 去掉背景框
        self.setAttribute(Qt.WA_TranslucentBackground)

        # 将窗口移动到屏幕中心
        screen = QCoreApplication.instance().desktop().screenGeometry()
        self.setGeometry(screen.width() / 2 - 400, screen.height() / 2 - 300, 800, 600)

    def paintEvent(self, event):
        painter = QPainter(self)
        painter.setPen(QColor(255, 0, 0))
        painter.setBrush(QBrush(QColor(255, 0, 0)))
        rect = QRect(self.width() / 2 - 32, self.height() / 2 - 32, 32, 32)
        painter.drawRect(rect)
        
    def mousePressEvent(self, event):
        if event.button() == Qt.LeftButton:
            self.close()

class Thread_MonitorScreen(QThread):
    msg_signal = pyqtSignal(str)

    def __init__(self):
        super(Thread_MonitorScreen, self).__init__()
        self.is_on = False
        
        logger.info('screen size: {} x {}'.format(pyautogui.size()[0], pyautogui.size()[1]))
        self.screenshot_x = pyautogui.size()[0] / 2 - 32
        self.screenshot_y = pyautogui.size()[1] / 2 -32
        logger.info('screenshot_x = {}, screenshot_y = {}'.format(self.screenshot_x, self.screenshot_y))
    
    def identify_image_by_PIL(self, img_path=TMP_SCREENSHOT_PNG):
        """判定截取区域是否接近指定图片
        0为黑色，255为白色
        """
    
        color_img = Image.open(img_path)

        # 转换成灰度图像
        gray_img = color_img.convert('L')

        # 图像中的最高和最低值
        extrema = gray_img.getextrema()

        # 黑白判断阈值
        black_threshold = (0, 9)
        white_threshold = (246, 255)
        light_white_threshold = (236, 245)

        if black_threshold[0] <= extrema[0] and extrema[1] <= black_threshold[1]:
            return 'black'
        if white_threshold[0] <= extrema[0] and extrema[1] <= white_threshold[1]:
            return 'white'
        if light_white_threshold[0] <= extrema[0] and extrema[1] <= light_white_threshold[1]:
            return 'light white'
        return 'not in range'
    
    def run(self):
        black_continuous_count = 0
        light_white_continuous_count = 0
        while self.is_on:
            self.sleep(3)
            screenshot = pyautogui.screenshot(TMP_SCREENSHOT_PNG, region=[self.screenshot_x, self.screenshot_y, 32, 32])
            logger.debug('screenshot: {}'.format(screenshot))
            
            image_type = self.identify_image_by_PIL()
            if image_type == 'black':
                black_continuous_count += 1
                light_white_continuous_count = 0
                if black_continuous_count >= 5: # 需要连续三次才能判断是黑屏状态
                    logger.info('usb camera is {} screen state'.format(image_type))
                    self.msg_signal.emit('警告可能是黑屏状态')
                    #black_continuous_count = 0
                    if black_continuous_count >= 20:    # 如果连续超过20次即一分钟停止监控屏幕
                        self.msg_signal.emit('关闭监控屏幕')
            elif image_type == 'light white':
                light_white_continuous_count += 1
                black_continuous_count = 0
                if light_white_continuous_count >= 5:   # 需要连续三次才能判断是浅白屏状态
                    logger.info('usb camera is {} screen state'.format(image_type))
                    self.msg_signal.emit('警告可能是异常状态')
                    #light_white_continuous_count = 0
                    if light_white_continuous_count >= 20:    # 如果连续超过20次即一分钟停止监控屏幕
                        self.msg_signal.emit('关闭监控屏幕')
            else:
                black_continuous_count = 0
                light_white_continuous_count = 0
                
            

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
