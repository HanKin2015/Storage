# -*- coding: utf-8 -*-
"""
文 件 名: udev_detect_tray.py
文件描述: usb设备检测（基于windows系统）
作    者: HanKin
创建日期: 2023.02.27
修改日期：2023.03.13

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
        
        # 图片打包
        self.py2ico(resource.udev_detect_ico, UDEV_DETECT_ICO)
        self.py2ico(resource.msg_ico, MSG_ICO)
        self.udevDetectIcon = QIcon(UDEV_DETECT_ICO)
        self.msgIcon = QIcon(MSG_ICO)
        
        # USB设备检测线程
        self.udevDetect = Thread_UdevDetect()
        self.udevDetect.hotplugSignal.connect(self.hotplugSignalSlot)
        self.udevDetect.getUdevInfoListSignal.connect(self.get_udev_info_list)

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
        self.ui.setWindowIcon(self.udevDetectIcon)
    
    def show_message_box(self):
        """弹出消息框
        """
        
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
        self.testMsgAction.triggered.connect(self.testMsgSlot)
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

    def hotplugSignalSlot(self, text):
        """USB设备拔插信号槽函数
        """

        self.messageTipForm.addToTipList(text, text)

    def testMsgSlot(self):
        """测试消息槽函数
        """
        
        text = '这是一条测试信息'
        self.messageTipForm.addToTipList(text, text)

    def about(self):
        """关于
        """
        
        #self.get_udev_info_list()
        aboutText = '{} V{}\n\n{}'.format(resource.InternalName, resource.ProductVersion, resource.LegalCopyright)
        QMessageBox.about(self.ui, resource.FileDescription, aboutText)
        
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
        不能在线程中执行，否则会有报错
        """
        
        wmi = win32com.client.GetObject("winmgmts:")
        #logger.info(wmi)  # <COMObject winmgmts:>
        
        udev_info_list = []
        for pnp in wmi.InstancesOf("Win32_PnPEntity"):
            if 'USB\\VID' in pnp.DeviceID and pnp.DeviceID.count('&') <= 4:
                for prop in pnp.Properties_:
                    logger.debug('{} : {}'.format(prop.Name, prop.Value))
                logger.debug('')

                udev_info = dict({'Name': pnp.Name,
                                     'deviceID': pnp.deviceID,
                                     'Service': pnp.Service,
                                     'ConfigManagerErrorCode': pnp.ConfigManagerErrorCode,
                                     'Status': pnp.Status,
                                     'HardWareID': pnp.HardWareID,
                                     'SystemName': pnp.SystemName})
                if platform.system() == 'Windows':
                    win_ver = platform.win32_ver()
                    if win_ver[0] == '7':
                        logger.debug('当前系统为Windows 7')
                        udev_info['PNPClass'] = 'USB'
                    else:
                        logger.debug('当前系统为Windows，但不是Windows 7')
                        udev_info['PNPClass'] = pnp.PNPClass
                else:
                    logger.error('当前系统不是Windows')

                udev_info_list.append(udev_info)
        for udev_info in udev_info_list:
            for key, value in udev_info.items():
                logger.debug('{}: {}'.format(key, value))
            logger.debug('')

        # 通知给子进程
        self.udevDetect.udev_info_list = udev_info_list

class Thread_UdevDetect(QThread):
    hotplugSignal = pyqtSignal(str)
    getUdevInfoListSignal = pyqtSignal()

    def __init__(self):
        super(Thread_UdevDetect, self).__init__()
        self.is_on = False
        self.udev_info_list = []

    def run(self):

        self.getUdevInfoListSignal.emit()
        self.sleep(1)   # 等待信号消息处理完成
        logger.info('there are {} hub and usb devices now'.format(len(self.udev_info_list)))
        last_udev_info_list = self.udev_info_list
        while self.is_on:
            self.sleep(1)
            
            self.getUdevInfoListSignal.emit()
            diff_count = len(self.udev_info_list) - len(last_udev_info_list)
            if diff_count == 0:
                continue
            
            self.hotplugSignal.emit('有USB设备插入' if diff_count > 0 else '有USB设备拔出')
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