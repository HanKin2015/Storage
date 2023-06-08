# -*- coding: utf-8 -*-
"""
文 件 名: fullscreen_recognition_qrcode.py
文件描述: 截全屏识别二维码
作    者: HanKin
创建日期: 2023.06.08
修改日期：2023.06.08

Copyright (c) 2023 HanKin. All rights reserved.
"""

import sys
from PyQt5.QtWidgets import QApplication, QWidget, QLabel
from PyQt5.QtGui import QPixmap, QImage
import pyzbar.pyzbar as pyzbar
import numpy as np

app = QApplication(sys.argv)
widget = QWidget()
widget.setWindowTitle("截图识别二维码")
widget.setGeometry(100, 100, 800, 600)

# 获取屏幕截图
screenshot = QApplication.primaryScreen().grabWindow(QApplication.desktop().winId())

# 显示截图
label = QLabel(widget)
pixmap = QPixmap(screenshot)
label.setPixmap(pixmap)
label.setGeometry(0, 0, pixmap.width(), pixmap.height())

# 将截图转换为OpenCV格式
image = screenshot.toImage()
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
for obj in decoded_objects:
    print("二维码内容：", obj.data.decode("utf-8"))

widget.show()
sys.exit(app.exec_())
