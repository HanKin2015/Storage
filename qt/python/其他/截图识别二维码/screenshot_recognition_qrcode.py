# -*- coding: utf-8 -*-
"""
文 件 名: screenshot_recognition_qrcode.py
文件描述: 将截图和截全屏识别二维码合体成为想要的截图工具
作    者: HanKin
创建日期: 2023.06.08
修改日期：2023.06.08

Copyright (c) 2023 HanKin. All rights reserved.
"""

import sys
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, QMainWindow, QFileDialog
from PyQt5.QtGui import QPixmap, QImage
import pyzbar.pyzbar as pyzbar
import numpy as np
import time
import screenshot_interface
import qrcode

from Ui_Qrcode import *

class MainWindow(QMainWindow, Ui_MainWindow):
    def __init__(self, parent=None):
        super(MainWindow, self).__init__(parent)
        self.setupUi(self)

        self.isStartState = True    # 判断是否启动摄像头
        self.isImageExist = False   # 判断当前是否存在已经解析的二维码
        self.NowCodeData = ""       # 当前解析出来的数据，刚开始没解析，所以为空
        self.codeImage = None       # 右下角当前解析出来的二维码，刚开始没解析，所以为空
        self.screenshot = None

        self.PauseButton.clicked.connect(self.startVideo)   # 绑定事件，开启/关闭摄像头
        self.RecognitionButton.clicked.connect(self.recognitionQrcode)     # 绑定事件，识别二维码
        self.SaveButton.clicked.connect(self.saveImage)     # 绑定事件，存储解析生成的二维码

    def startVideo(self):
        """# 开启 / 关闭摄像头
        """
        
        self.hide()
        time.sleep(0.2)
        screenshot_window = screenshot_interface.Screenshot()
        screenshot_window.screenshot_signal.connect(self.screenshot_signal_slot)
        screenshot_window.show()
        screenshot_window.exec_()

    def screenshot_signal_slot(self, screenshot_data):
        """
        """
        
        print(screenshot_data)
        self.show()
        self.screenshot = screenshot_data
        self.VideoLabel.setPixmap(screenshot_data)

    def recognitionQrcode(self):
        """
        """
        
        # 将截图转换为OpenCV格式
        image = self.screenshot.toImage()
        width, height = image.width(), image.height()
        ptr = image.constBits()
        print(type(ptr))
        print(ptr)

        # chatgpt真有点坑，自己写的代码指不出来错误ValueError: cannot reshape array of size 1 into shape (1080,1920,4)
        ptr.setsize(image.byteCount())

        # 将Qt的图像数据转换为NumPy数组，并去除了Alpha通道，只保留RGB三个通道的数据，使用切片操作[:, :, :3]去除Alpha通道
        arr = np.array(ptr).reshape(height, width, 4)[:, :, :3]

        # 使用pyzbar库识别二维码
        decoded_objects = pyzbar.decode(arr)

        # 显示识别结果
        #for obj in decoded_objects:
        #    print("二维码内容：", obj.data.decode("utf-8"))
        print(decoded_objects)
        if len(decoded_objects) == 0:
            self.DataLabel.setText('解析失败')
        else:
            self.DataLabel.setText("解析成功 : {}".format(decoded_objects[0].data.decode('utf-8')))
            self.createCode(decoded_objects[0].data.decode('utf-8'))

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
        self.ImageLabel.setPixmap(pix.scaled(150, 150)) 
        self.isImageExist = True
        
def main():
    """主函数
    """

    # 创建活跃 app 句柄
    app = QApplication(sys.argv)

    # 关闭全部窗口后程序不退出
    #app.setQuitOnLastWindowClosed(False)

    # 声明界面句柄
    mainWindow = MainWindow()

    # 程序启动时打开主界面
    mainWindow.show()

    sys.exit(app.exec_())

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    #logger.info('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    #logger.info('process spend {} s.\n'.format(round(end_time - start_time, 3)))
