# -*- coding: utf-8 -*-
"""
文 件 名: QPushButton_example.py
文件描述: 切换按钮
作    者: HanKin
创建日期: 2022.09.06
修改日期：2022.09.06

Copyright (c) 2022 HanKin. All rights reserved.
"""

from PyQt5.QtWidgets import (QWidget, QPushButton, 
    QFrame, QApplication)
from PyQt5.QtGui import QColor
import sys

class Example(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        redb = QPushButton('Red', self)
        redb.setCheckable(True)     # setCheckable()函数就把这个按钮编程了切换按钮
        redb.move(10, 10)
        redb.clicked[bool].connect(self.setColor)   # 把点击信号和我们定义好的函数关联起来，这里是把点击事件转换成布尔值

        greenb = QPushButton('Green', self)
        greenb.setCheckable(True)
        greenb.move(10, 60)
        greenb.clicked[bool].connect(self.setColor)

        blueb = QPushButton('Blue', self)
        blueb.setCheckable(True)
        blueb.move(10, 110)
        blueb.clicked[bool].connect(self.setColor)

        self.square = QFrame(self)
        self.square.setGeometry(150, 20, 100, 100)
        self.col = QColor(0, 0, 0)
        self.square.setStyleSheet("QWidget { background-color: %s }" %  
            self.col.name())

        self.setGeometry(300, 300, 280, 170)
        self.setWindowTitle('Toggle button')
        self.show()

    def setColor(self, pressed):
        source = self.sender()
        if pressed:
            val = 255
        else: val = 0

        if source.text() == "Red":
            self.col.setRed(val)                
        elif source.text() == "Green":
            self.col.setGreen(val)             
        else:
            self.col.setBlue(val) 

        self.square.setStyleSheet("QFrame { background-color: %s }" %
            self.col.name())  

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())