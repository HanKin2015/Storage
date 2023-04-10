# -*- coding: utf-8 -*-
"""
文 件 名: base64_convert_string.py
文件描述: 使用base64编码转换字符串
作    者: HanKin
创建日期: 2023.04.03
修改日期：2023.04.03

Copyright (c) 2023 HanKin. All rights reserved.
"""

from common import *

class MyWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle('base64编码字符串')
        self.setGeometry(100, 100, 400, 200)
        
        # 整体垂直布局
        vbox = QVBoxLayout()
        
        # 第一个QFrame，base64编码字符串
        base64_convert_string_frame = QFrame(self)
        original_string_label = QLabel('原字符串:', base64_convert_string_frame)
        self.original_string_lineedit = QLineEdit(base64_convert_string_frame)

        base64_string_label = QLabel('新字符串:', base64_convert_string_frame)
        self.base64_string_lineedit = QLineEdit(base64_convert_string_frame)

        convert_button = QPushButton('转换', base64_convert_string_frame)
        convert_button.clicked.connect(self.base64_convert_string)
        copy_button = QPushButton('复制', base64_convert_string_frame)
        copy_button.clicked.connect(self.copy_to_clipboard)

        hbox = QHBoxLayout()
        hbox.addWidget(convert_button)
        hbox.addStretch(1)
        hbox.addWidget(copy_button)

        grid = QGridLayout(base64_convert_string_frame)
        grid.addWidget(original_string_label, 0, 0)
        grid.addWidget(self.original_string_lineedit, 0, 1)
        grid.addWidget(base64_string_label, 1, 0)
        grid.addWidget(self.base64_string_lineedit, 1, 1)
        grid.addLayout(hbox, 2, 0, 1, 2)
        
        base64_convert_string_frame.setStyleSheet("QFrame { border: 1px solid black; } QFrame QLabel { border: none; }")
        vbox.addWidget(base64_convert_string_frame)

        
        # 第二个QFrame， 时间转换
        time_convert_frame = QFrame(self)
        self.time_label    = QLabel('2023-04-10', time_convert_frame)
        self.time_edit     = QLineEdit(time_convert_frame)
        time_btn           = QPushButton('时间转换', time_convert_frame)
        time_btn.clicked.connect(self.time_btn_slot)
        hbox = QHBoxLayout(time_convert_frame)
        hbox.addWidget(self.time_label)
        hbox.addWidget(self.time_edit)
        hbox.addWidget(time_btn)
        
        time_convert_frame.setStyleSheet("QFrame { background-color: white; border: 1px solid black; } QFrame QLabel { border: none; }")
        vbox.addWidget(time_convert_frame)

        self.setLayout(vbox)
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

    def time_btn_slot(self):
        """
        """
        
        time_stamp = int(self.time_edit.text())
        logger.info('time stamp is {}'.format(time_stamp))
        self.time_label.setText(str(datetime.date.fromtimestamp(time_stamp)))

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MyWindow()
    sys.exit(app.exec_())

