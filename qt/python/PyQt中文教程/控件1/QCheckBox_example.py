# -*- coding: utf-8 -*-
"""
文 件 名: QCheckBox_example.py
文件描述: 控件
作    者: HanKin
创建日期: 2022.09.06
修改日期：2022.09.06

Copyright (c) 2022 HanKin. All rights reserved.
"""

from PyQt5.QtWidgets import QWidget, QCheckBox, QApplication
from PyQt5.QtCore import Qt
import sys

class Example(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):      
        cb = QCheckBox('Show title', self)
        cb.move(20, 20)
        cb.toggle()     # 默认情况下，单选框未选中
        cb.stateChanged.connect(self.changeTitle)

        self.setGeometry(300, 300, 250, 150)
        self.setWindowTitle('QCheckBox')
        self.show()

    def changeTitle(self, state):
        if state == Qt.Checked:
            self.setWindowTitle('QCheckBox')
        else:
            self.setWindowTitle(' ')

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())