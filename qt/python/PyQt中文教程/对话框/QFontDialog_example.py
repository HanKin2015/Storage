# -*- coding: utf-8 -*-
"""
文 件 名: QFontDialog_example.py
文件描述: 选择字体
作    者: HanKin
创建日期: 2022.09.06
修改日期：2022.09.06

Copyright (c) 2022 HanKin. All rights reserved.
"""

from PyQt5.QtWidgets import (QWidget, QVBoxLayout, QPushButton, 
    QSizePolicy, QLabel, QFontDialog, QApplication)
import sys

class Example(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):      
        btn = QPushButton('Dialog', self)
        btn.setSizePolicy(QSizePolicy.Fixed,
            QSizePolicy.Fixed)
        btn.move(20, 20)
        btn.clicked.connect(self.showDialog)

        self.lbl = QLabel('Knowledge only matters', self)   # 知识才重要
        self.lbl.move(130, 20)

        vbox = QVBoxLayout()
        vbox.addWidget(btn)
        vbox.addWidget(self.lbl)
        self.setLayout(vbox)          

        self.setGeometry(300, 300, 250, 180)
        self.setWindowTitle('Font dialog')
        self.show()

    def showDialog(self):
        font, ok = QFontDialog.getFont()
        if ok:
            self.lbl.setFont(font)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())