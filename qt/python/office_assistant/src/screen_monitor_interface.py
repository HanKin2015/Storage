# -*- coding: utf-8 -*-
"""
文 件 名: screen_monitor_interface.py
文件描述: 屏幕监控接口类
作    者: HanKin
创建日期: 2023.05.25
修改日期：2023.05.26

Copyright (c) 2023 HanKin. All rights reserved.
"""

from common import *

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
    recv_msg_signal = pyqtSignal(str)
    stop_monitor_signal = pyqtSignal(bool)
    ip = None
    mac = None
    user_name = None

    def __init__(self):
        super(Thread_MonitorScreen, self).__init__()
        self.is_on = False
        
        logger.info('screen size: {} x {}'.format(pyautogui.size()[0], pyautogui.size()[1]))
        self.screenshot_x = pyautogui.size()[0] / 2 - 32
        self.screenshot_y = pyautogui.size()[1] / 2 -32
        logger.info('screenshot_x = {}, screenshot_y = {}'.format(self.screenshot_x, self.screenshot_y))
        
        # 收发消息
        self.sock = QUdpSocket()
        #self.sock.bind(QHostAddress.LocalHost, 6666)
        self.sock.bind(QHostAddress.Any, 6666)
        self.sock.readyRead.connect(self.readDataSlot)
        self.clientAddress = None

    def readDataSlot(self):
        """服务端一直在监听客户端的消息
        """
        
        while self.sock.hasPendingDatagrams():
            datagram, host, port = self.sock.readDatagram(
                self.sock.pendingDatagramSize()
            )

            messgae = 'Date time: {}\nHost: {}\nPort: {}\n\n'.format(datagram.decode(), host.toString(), port)
            logger.debug(messgae)
            self.recv_msg_signal.emit(datagram.decode())

    def writeDataSlot(self, msg):
        """收到本地线程的监控消息，然后上报给服务端
        """

        if msg == '关闭监控屏幕':
            logger.warning('收到关闭监控屏幕消息')
            self.stop_monitor_signal.emit(True)
        
        current_time = time.strftime('%Y-%m-%d %H:%M:%S', time.localtime())
        msg = '{},{},{},{} {}'.format(self.user_name, self.ip, self.mac, current_time, msg)
        datagram = msg.encode()
        #self.sock.writeDatagram(datagram, QHostAddress.LocalHost, 6666)
        #self.sock.writeDatagram(datagram, QHostAddress.Broadcast, 6666)
        self.sock.writeDatagram(datagram, QHostAddress(self.clientAddress), 6666)

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
                if black_continuous_count >= 5: # 需要连续五次才能判断是黑屏状态
                    logger.info('usb camera is {} screen state({})'.format(image_type, black_continuous_count))
                    self.writeDataSlot('警告可能是黑屏状态({})'.format(black_continuous_count))
                    #black_continuous_count = 0
                    if black_continuous_count >= 20:    # 如果连续超过20次即一分钟停止监控屏幕
                        logger.warning('已经连续黑屏1分钟，关闭监控屏幕')
                        self.writeDataSlot('关闭监控屏幕')
                        self.is_on = False
            elif image_type == 'light white':
                light_white_continuous_count += 1
                black_continuous_count = 0
                if light_white_continuous_count >= 5:   # 需要连续五次才能判断是浅白屏状态
                    logger.info('usb camera is {} screen state({})'.format(image_type, light_white_continuous_count))
                    self.writeDataSlot('警告可能是异常状态({})'.format(light_white_continuous_count))
                    #light_white_continuous_count = 0
                    if light_white_continuous_count >= 20:    # 如果连续超过20次即一分钟停止监控屏幕
                        logger.warning('已经连续异常1分钟，关闭监控屏幕')
                        self.writeDataSlot('关闭监控屏幕')
                        self.is_on = False
            else:
                black_continuous_count = 0
                light_white_continuous_count = 0

def main():
    """主函数
    """

    app = QApplication(sys.argv)

    monitorScreen = Thread_MonitorScreen()
    #monitorScreen.recv_msg_signal.connect()
    monitorScreen.is_on = True
    monitorScreen.start()
    
    subwindow = ScreenShotArea()
    subwindow.show()

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
