# -*- coding: utf-8 -*-
"""
文 件 名: qicon_example.py
文件描述: 带窗口图标
作    者: HanKin
创建日期: 2022.09.05
修改日期：2022.09.05

Copyright (c) 2022 HanKin. All rights reserved.
"""

import sys
from PyQt5.QtWidgets import QApplication, QWidget
from PyQt5.QtGui import QIcon

# 面向对象编程
class Example(QWidget):
    
    def __init__(self):
        super().__init__()

        self.initUI()


    def initUI(self):

        self.setGeometry(300, 300, 300, 220)
        self.setWindowTitle('Icon')
        self.setWindowIcon(QIcon('icon/huawei.ico'))        

        self.show()


if __name__ == '__main__':

    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())