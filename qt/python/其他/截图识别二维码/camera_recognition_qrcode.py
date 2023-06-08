# -*- coding: utf-8 -*-
"""
文 件 名: camera_recognition_qrcode.py
文件描述: 使用摄像头动态识别二维码
作    者: HanKin
参    考：https://blog.csdn.net/qq_47452807/article/details/124233469
创建日期: 2023.06.08
修改日期：2023.06.08

Copyright (c) 2023 HanKin. All rights reserved.
"""

import sys
from datetime import datetime

import qrcode
from PyQt5.QtGui import QPixmap, QImage
from PyQt5.QtWidgets import QApplication, QMainWindow, QFileDialog
from pyzbar import pyzbar

from CameraScan import *
import cv2

capture = cv2.VideoCapture(0)

class MyClass(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super(MyClass, self).__init__(parent)
        self.setupUi(self)
        self.isStartState = True
        # 判断是否启动摄像头
        self.isImageExist = False
        # 判断当前是否存在已经解析的二维码
        self.NowCodeData = ""
        # 当前解析出来的数据，刚开始没解析，所以为空
        self.codeImage = None
        # 右下角当前解析出来的二维码，刚开始没解析，所以为空

        self.PauseButton.clicked.connect(self.startVideo)
        # 绑定事件，开启/关闭摄像头
        self.SaveButton.clicked.connect(self.saveImage)
        # 绑定事件，存储解析生成的二维码


	# 开启 / 关闭摄像头
    def startVideo(self):
        self.isStartState = ~self.isStartState
        while self.isStartState:
            self.VideoLabel.setPixmap(self.nowImage())
            cv2.waitKey(50)

	# 存储二维码图片
    def saveImage(self):
        if self.isImageExist == False:
            return
        FileName = datetime.now().strftime('%Y-%m-%d_%H_%M_%S')
        file, tmp = QFileDialog.getSaveFileName(self, 'Save Image', FileName, '*.png *.jpg *.bmp')
        self.codeImage.save(file)

    # 当前的画面
    def nowImage(self):
        ret, self.img = capture.read()
        print('ret: {}'.format(ret))
        
        # 摄像头读取, ret为是否成功打开摄像头, true, false：frame为视频的每一帧图像
        self.checkCode(self.img)
        
        # 检测二维码
        height, width, channel = self.img.shape
        
        # 提取图像的通道和尺寸，用于将OpenCV下的image转换成Qimage
        bytesPerline = 3 * width
        img = QImage(self.img.data, width, height, bytesPerline, QImage.Format_RGB888).rgbSwapped()
        # 将QImage显示出来
        return QPixmap.fromImage(img.scaled(480, 360))

	# 原理上面已经说明了，就是检测二维码
    def checkCode(self, video):
        gray = cv2.cvtColor(video, cv2.COLOR_BGR2GRAY)
        barcodes = pyzbar.decode(gray)
        for barcode in barcodes:
            (x, y, w, h) = barcode.rect
            cv2.rectangle(video, (x, y), (x + w, y + h), (0, 255, 0), 2)
            barcodeData = barcode.data.decode("utf-8")
            text = "{}".format(barcodeData)
            
            # 防止重复生成二维码影响效率
            if text != self.NowCodeData:
                self.createCode(text)
                
            self.NowCodeData = text
            self.DataLabel.setText("解析数据 : {}".format(self.NowCodeData))
            cv2.putText(video, text, (x, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

    def createCode(self, text):
        # 二维码内容（链接地址或文字）
        code = qrcode.make(data=text)
        self.codeImage = code
        # 存储临时图片 code.temp.jpg
        code.save("code.temp.jpg")
        pix = QPixmap("code.temp.jpg")
         # 展示解析生成的二维码图片
        self.ImageLabel.setPixmap(pix.scaled(200, 200)) 
        self.isImageExist = True

if __name__ == '__main__':
    app = QApplication(sys.argv)
    myWin = MyClass()
    myWin.setWindowTitle("唤醒手腕 - 猫头鹰Code-Scanner-2000")
    myWin.show()
    sys.exit(app.exec_())
