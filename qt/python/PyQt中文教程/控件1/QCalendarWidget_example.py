# -*- coding: utf-8 -*-
"""
文 件 名: QCalendarWidget_example.py
文件描述: 日历
作    者: HanKin
创建日期: 2022.09.06
修改日期：2022.09.06

Copyright (c) 2022 HanKin. All rights reserved.
"""

from PyQt5.QtWidgets import (QWidget, QCalendarWidget, 
    QLabel, QApplication, QVBoxLayout)
from PyQt5.QtCore import QDate
import sys

class Example(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):      
        cal = QCalendarWidget(self)
        cal.setGridVisible(True)
        cal.clicked[QDate].connect(self.showDate)

        vbox = QVBoxLayout(self)
        vbox.addWidget(cal)

        self.lbl = QLabel(self)
        date = cal.selectedDate()
        self.lbl.setText(date.toString())

        vbox.addWidget(self.lbl)

        self.setLayout(vbox)
        self.setGeometry(300, 300, 350, 300)
        self.setWindowTitle('Calendar')
        self.show()

    def showDate(self, date):     
        self.lbl.setText(date.toString())

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())