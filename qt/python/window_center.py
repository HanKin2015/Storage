# -*- coding: utf-8 -*-
"""
文 件 名: window_center.py
文件描述: 窗口居中
作    者: HanKin
创建日期: 2022.09.05
修改日期：2022.09.05

Copyright (c) 2022 HanKin. All rights reserved.
"""

import sys
from PyQt5.QtWidgets import QWidget, QDesktopWidget, QApplication

class Example(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):               
        self.resize(250, 150)
        self.center()
        self.setWindowTitle('Center')    
        self.show()

    def center(self):
        qr = self.frameGeometry()   # 获得主窗口所在的框架
        cp = QDesktopWidget().availableGeometry().center()  # 获取显示器的分辨率
        qr.moveCenter(cp)           # 把主窗口框架的中心点放置到屏幕的中心位置
        self.move(qr.topLeft())     # 通过move函数把主窗口的左上角移动到其框架的左上角，这样就把窗口居中了

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())
