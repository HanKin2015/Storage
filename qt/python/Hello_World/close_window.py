# -*- coding: utf-8 -*-
"""
文 件 名: close_window.py
文件描述: 关闭窗口(事件传递系统在PyQt5内建的single和slot机制里面)
作    者: HanKin
创建日期: 2022.09.05
修改日期：2022.09.05

Copyright (c) 2022 HanKin. All rights reserved.
"""

import sys
from PyQt5.QtWidgets import QWidget, QPushButton, QApplication
from PyQt5.QtCore import QCoreApplication

class Example(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):               
        qbtn = QPushButton('Quit', self)
        qbtn.clicked.connect(QCoreApplication.instance().quit)
        qbtn.resize(qbtn.sizeHint())
        qbtn.move(50, 50)       

        self.setGeometry(300, 300, 250, 150)
        self.setWindowTitle('Quit button')    
        self.show()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())