# -*- coding: utf-8 -*-
"""
文 件 名: base64_convert_string.py
文件描述: 使用base64编码转换字符串
作    者: HanKin
创建日期: 2023.04.03
修改日期：2023.04.03

Copyright (c) 2023 HanKin. All rights reserved.
"""

import sys
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, \
    QLineEdit, QGridLayout, QPushButton, QHBoxLayout, QDesktopWidget
import base64

class MyWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle('base64编码字符串')
        self.setGeometry(100, 100, 400, 100)

        original_string_label = QLabel('原字符串:', self)
        self.original_string_lineedit = QLineEdit(self)

        base64_string_label = QLabel('新字符串:', self)
        self.base64_string_lineedit = QLineEdit(self)

        convert_button = QPushButton('转换', self)
        convert_button.clicked.connect(self.base64_convert_string)
        copy_button = QPushButton('复制', self)
        copy_button.clicked.connect(self.copy_to_clipboard)

        hbox = QHBoxLayout()
        hbox.addWidget(convert_button)
        hbox.addStretch(1)
        hbox.addWidget(copy_button)

        grid = QGridLayout()
        grid.addWidget(original_string_label, 0, 0)
        grid.addWidget(self.original_string_lineedit, 0, 1)
        grid.addWidget(base64_string_label, 1, 0)
        grid.addWidget(self.base64_string_lineedit, 1, 1)
        grid.addLayout(hbox, 2, 0, 1, 2)

        self.setLayout(grid)
        self.center()
        self.show()

    def center(self):
        qr = self.frameGeometry()
        cp = QApplication.desktop().availableGeometry().center()
        qr.moveCenter(cp)
        self.move(qr.topLeft())

    def base64_convert_string(self):
        """
        """
        
        original_string = self.original_string_lineedit.text()
        print('original_string: {}'.format(original_string))
        
        # 编码： 字符串 -> 二进制 -> base64编码
        base64_string = base64.b64encode(original_string.encode())
        print('base64_string: {}'.format(base64_string))
        
        self.base64_string_lineedit.setText(str(base64_string))

    def copy_to_clipboard(self):
        """
        """
        
        clipboard = QApplication.clipboard()
        clipboard.setText(self.base64_string_lineedit.text())

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MyWindow()
    sys.exit(app.exec_())

