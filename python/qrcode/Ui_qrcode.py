# -*- coding: utf-8 -*-
"""
文 件 名: qrcode_interface.py
文件描述: 截图识别二维码接口
作    者: HanKin
创建日期: 2023.06.09
修改日期：2023.06.12

Copyright (c) 2023 HanKin. All rights reserved.
"""

from PyQt5.QtWidgets import QMessageBox, QAction, QDialog, QApplication
from PyQt5.QtCore import QObject, QEvent, Qt, QRect
from PyQt5.QtGui import QPainter, QGuiApplication, QColor, QPen
import numpy as np
import time
import sys
import pyzbar.pyzbar as pyzbar

class MyMessageBox(QMessageBox):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.initUI()

    def initUI(self):
        pass

    def contextMenuEvent(self, event):
        menu = self.createStandardContextMenu()
        for action in menu.actions():
            print(action.text())
            if action.text() == 'Copy':
                action.setText('复制')
        menu.exec_(event.globalPos())

class EventFilter(QObject):
    def eventFilter(self, obj, event):
        if event.type() != QEvent.UpdateRequest and event.type() != QEvent.Paint:
            print('event.type = {}'.format(event.type()))
        if event.type() == QEvent.MouseButtonPress:
            menu = QMenu()
            copyAction = QAction('复制', menu)
            copyAction.triggered.connect(lambda: self.copyText(obj))
            menu.addAction(copyAction)
            selectAllAction = QAction('全选', menu)
            menu.addAction(selectAllAction)
            menu.exec_(event.globalPos())
            return True
        return False

    def copyText(self, obj):
        clipboard = QApplication.clipboard()
        text = obj.text()
        clipboard.setText(text[7:])
        
class Screenshot(QDialog):
    """截图"""

    # 初始化变量
    fullScreenImage = None
    captureImage = None
    isMousePressLeft = None
    beginPosition = None
    endPosition = None

    # 创建 QPainter 对象
    painter = QPainter()

    def __init__(self):
        super().__init__()
        self.initWindow()             # 初始化窗口
        self.captureFullScreen()      # 捕获全屏

    def initWindow(self):
        """初始化窗口"""
        self.setCursor(Qt.CrossCursor)               # 设置光标
        self.setWindowFlag(Qt.FramelessWindowHint)   # 产生无边框窗口，用户不能通过窗口系统移动或调整无边界窗口的大小
        self.setWindowState(Qt.WindowFullScreen)     # 窗口全屏无边框

    def captureFullScreen(self):
        """捕获全屏"""
        # 捕获当前屏幕，返回像素图
        self.fullScreenImage = QGuiApplication.primaryScreen().grabWindow(QApplication.desktop().winId())

    def mousePressEvent(self, event):
        """鼠标按下事件"""
        # 如果鼠标事件为左键，则记录起始鼠标光标相对于窗口的位置
        if event.button() == Qt.LeftButton:
            self.beginPosition = event.pos()
            self.isMousePressLeft = True
        # 如果鼠标事件为右键，如果已经截图了则重新开始截图，如果没有截图就退出
        if event.button() == Qt.RightButton:
            if self.captureImage is not None:
                self.captureImage = None
                self.update()    # 更新，会擦除之前的选框
            else:
                self.close()

    def mouseMoveEvent(self, event):
        """鼠标移动事件"""
        if self.isMousePressLeft is True:
            self.endPosition = event.pos()
            self.update()

    def mouseReleaseEvent(self, event):
        """鼠标释放事件"""
        self.endPosition = event.pos()
        self.isMousePressLeft = False

    def mouseDoubleClickEvent(self, event):
        """鼠标双击事件"""
        #self.saveImage()
        self.recognitionQrcode()
        self.close()

    def recognitionQrcode(self):
        """识别二维码"""
        
        if self.captureImage == None:
            QMessageBox.about(None, '截图结果', '截图失败，截图的区域太小')
            return
        
        # 将截图转换为OpenCV格式
        image = self.captureImage.toImage()
        width, height = image.width(), image.height()
        ptr = image.constBits()
        print(type(ptr))
        print(ptr)

        # chatgpt真有点坑，自己写的代码指不出来错误ValueError: cannot reshape array of size 1 into shape (1080,1920,4)
        ptr.setsize(image.byteCount())

        # 将Qt的图像数据转换为NumPy数组，并去除了Alpha通道，只保留RGB三个通道的数据，使用切片操作[:, :, :3]去除Alpha通道
        arr = np.array(ptr).reshape(height, width, 4)[:, :, :3]
        import struct

        # 假设每个像素点占用4个字节，即RGBA格式
        pixel_size = 4

        # 将constBits()返回的QByteArray转换成bytearray
        byte_array = bytearray(ptr)

        # 计算每行像素点所占用的字节数
        bytes_per_line = pixel_size * width

        # 将bytearray转换成三维数组
        pixels = []
        for y in range(height):
            row = []
            for x in range(width):
                pixel_start = y * bytes_per_line + x * pixel_size
                pixel_bytes = byte_array[pixel_start:pixel_start + pixel_size]
                pixel = struct.unpack('BBBB', pixel_bytes)
                row.append(pixel)
            pixels.append(row)
        
        #arr = np.array(pixels)[:, :, :3]
        print(type(pixels))
        print(type(pixels[0]))
        print(type(pixels[0][0]))
        print(len(pixels), len(pixels[0]), len(pixels[0][0]))
        for i in range(len(pixels)):
            for j in range(len(pixels[i])):
                pixels[i][j] = list(pixels[i][j])
                pixels[i][j] = pixels[i][j][:-1]
        print(len(pixels), len(pixels[0]), len(pixels[0][0]))
        print(np.array(pixels).shape)
        
        # 使用pyzbar库识别二维码
        decoded_objects = pyzbar.decode(arr)

        # 显示识别结果
        #for obj in decoded_objects:
        #    print("二维码内容：", obj.data.decode("utf-8"))
        print(decoded_objects)
        if len(decoded_objects) == 0:
            QMessageBox.about(None, '二维码内容', '解析失败，可能不存在二维码')
        else:
            # 自定义对话框
            box = MyMessageBox()
            box.setWindowTitle('二维码内容')
            # b'\xe8\xad\x8f\xef\xbd\xaf'
            # b'fds\xe6\x88\x9112'
            print(decoded_objects[0].data)
            box.setText('解析成功 : {}'.format(decoded_objects[0].data.decode('utf-8')))
            box.setIcon(QMessageBox.Information)    # NoIcon/Information/Warning/Critical/Question 
            box.setTextInteractionFlags(Qt.TextSelectableByMouse)
            eventFilter = EventFilter()
            box.installEventFilter(eventFilter)
            box.exec_()

    def paintBackgroundImage(self):
        """绘制背景图"""
        # 填充颜色，黑色半透明
        fillColor = QColor(0, 0, 0, 100)
        # 加载显示捕获的图片到窗口
        self.painter.drawPixmap(0, 0, self.fullScreenImage)
        # 填充颜色到给定的矩形
        self.painter.fillRect(self.fullScreenImage.rect(), fillColor)

    def getRectangle(self, beginPoint, endPoint):
        """获取矩形选框"""
        # 计算矩形宽和高
        rectWidth = int(abs(beginPoint.x() - endPoint.x()))
        rectHeight = int(abs(beginPoint.y() - endPoint.y()))
        # 计算矩形左上角 x 和 y
        rectTopleftX = beginPoint.x() if beginPoint.x() < endPoint.x() else endPoint.x()
        rectTopleftY = beginPoint.y() if beginPoint.y() < endPoint.y() else endPoint.y()
        # 构造一个以（x，y）为左上角，给定宽度和高度的矩形
        pickRect = QRect(rectTopleftX, rectTopleftY, rectWidth, rectHeight)
        # 调试日志
        # logging.info('开始坐标：%s,%s', beginPoint.x(),beginPoint.y())
        # logging.info('结束坐标：%s,%s', endPoint.x(), endPoint.y())
        return pickRect

    def paintSelectBox(self):
        """绘制选框"""
        # 画笔颜色，蓝色
        penColor = QColor(30, 150, 255)  # 画笔颜色
        # 设置画笔属性，蓝色、2px大小、实线
        self.painter.setPen(QPen(penColor, 2, Qt.SolidLine))
        if self.isMousePressLeft is True:
            pickRect = self.getRectangle(self.beginPosition, self.endPosition)  # 获得要截图的矩形框
            self.captureImage = self.fullScreenImage.copy(pickRect)             # 捕获截图矩形框内的图片
            self.painter.drawPixmap(pickRect.topLeft(), self.captureImage)      # 填充截图的图片
            self.painter.drawRect(pickRect)     # 绘制矩形边框

    def paintEvent(self,event):
        """接收绘制事件开始绘制"""
        self.painter.begin(self)        # 开始绘制
        self.paintBackgroundImage()     # 绘制背景
        self.paintSelectBox()           # 绘制选框
        self.painter.end()              # 结束绘制

    def saveImage(self):
        """保存图片"""
        # 获取用户选择的文件名的完整路径
        fileName = QFileDialog.getSaveFileName(self, '保存图片', time.strftime("%Y%m%d%H%M%S"), ".png")
        # 保存用户选择的文件。如果选取了区域，就保存区域图片；如果没有选取区域，就保存全屏图片
        if self.captureImage is not None:
            self.captureImage.save(fileName[0] + fileName[1])
        else:
            self.fullScreenImage.save(fileName[0] + fileName[1])

    def keyPressEvent(self, event):
        """按键事件"""
        # 如果按下 ESC 键，则退出截图
        if event.key() == Qt.Key_Escape:
            self.close()
        # 如果按下 Enter 键，并且已经选取了区域，就截图选区图片
        if event.key() == Qt.Key_Enter or event.key() == Qt.Key_Return:
            if self.captureImage is not None:
                self.saveImage()
                self.close()

def main():
    """主函数
    
    很是奇怪，《来是come，去是go》识别正常，但是单独《来》或者《是》都不行，识别的数据有误
    替换了其他版本的libzbar-64.dll文件已解决，发现只有C:\Windows\System32目录下生效，其他目录C:\ProgramData\anaconda3\Lib\site-packages\pyzbar和当前项目目录都不生效
    """
    app = QApplication(sys.argv)

    screenshot_window = Screenshot()
    screenshot_window.show()
    
    # 这一行代码加上去后怎么都拯救不了无法关闭的风险
    #screenshot_window.exec_()
    #screenshot_window.close()
    #QCoreApplication.quit()
    #app.setQuitOnLastWindowClosed(True)
    #print(1)
    sys.exit(app.exec_())

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))
