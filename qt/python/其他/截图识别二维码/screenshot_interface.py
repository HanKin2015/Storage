# -*- coding: utf-8 -*-
"""
文 件 名: screenshot_interface.py
文件描述: 截图操作
作    者: HanKin
创建日期: 2023.06.08
修改日期：2023.06.08

Copyright (c) 2023 HanKin. All rights reserved.
"""

import sys, time, logging
from PyQt5.QtCore import Qt, QRect, pyqtSignal
from PyQt5.QtGui import QPen, QPainter, QColor, QGuiApplication, QPixmap
from PyQt5.QtWidgets import QApplication, QWidget, QFileDialog, QDialog

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
    
    # 将截图数据传递出去
    screenshot_signal = pyqtSignal(QPixmap)

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
        self.screenshot_signal.emit(self.captureImage)
        self.close()

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

