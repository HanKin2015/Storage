# -*- coding: utf-8 -*-
"""
文 件 名: points.py
文件描述: 点的绘画
作    者: HanKin
创建日期: 2022.09.07
修改日期：2022.09.07

Copyright (c) 2022 HanKin. All rights reserved.
"""

from PyQt5.QtWidgets import QWidget, QApplication
from PyQt5.QtGui import QPainter
from PyQt5.QtCore import Qt
import sys, random

class Example(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):      
        self.setGeometry(300, 300, 300, 190)
        self.setWindowTitle('Points')
        self.show()

    def paintEvent(self, e):
        qp = QPainter()
        qp.begin(self)
        self.drawPoints(qp)
        qp.end()

    def drawPoints(self, qp):
        qp.setPen(Qt.red)
        size = self.size()
        for i in range(1000):
            x = random.randint(1, size.width()-1)
            y = random.randint(1, size.height()-1)
            qp.drawPoint(x, y)     

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())