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
        base64_convert_string_gb = QGroupBox('base64编解码', self)
        original_string_label = QLabel('原字符串:', base64_convert_string_gb)
        self.original_string_lineedit = QLineEdit(base64_convert_string_gb)

        base64_string_label = QLabel('新字符串:', base64_convert_string_gb)
        self.base64_string_lineedit = QLineEdit(base64_convert_string_gb)

        convert_button = QPushButton('转换', base64_convert_string_gb)
        convert_button.clicked.connect(self.base64_convert_string)
        original_copy_button = QPushButton('原复制', base64_convert_string_gb)
        original_copy_button.clicked.connect(self.original_copy_to_clipboard)
        
        reverse_button = QPushButton('反转', base64_convert_string_gb)
        reverse_button.clicked.connect(self.base64_reverse_string)
        new_copy_button = QPushButton('新复制', base64_convert_string_gb)
        new_copy_button.clicked.connect(self.new_copy_to_clipboard)

        hbox = QHBoxLayout()
        hbox.addWidget(convert_button)
        hbox.addWidget(original_copy_button)
        hbox.addStretch(1)
        hbox.addWidget(reverse_button)
        hbox.addWidget(new_copy_button)

        grid = QGridLayout(base64_convert_string_gb)
        grid.addWidget(original_string_label, 0, 0)
        grid.addWidget(self.original_string_lineedit, 0, 1)
        grid.addWidget(base64_string_label, 1, 0)
        grid.addWidget(self.base64_string_lineedit, 1, 1)
        grid.addLayout(hbox, 2, 0, 1, 2)
        
        #base64_convert_string_gb.setStyleSheet("QFrame { border: 1px solid black; } QFrame QLabel { border: none; }")
        vbox.addWidget(base64_convert_string_gb)

        
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
        
        # 第三个QFrame，字符串编码
        string_encode_gb = QGroupBox('gbk编解码', self)
        string_decode_label = QLabel('解码字符串:', string_encode_gb)
        self.string_decode_lineedit = QLineEdit(string_encode_gb)

        string_encode_label = QLabel('编码字符串:', string_encode_gb)
        self.string_encode_lineedit = QLineEdit(string_encode_gb)

        encode_button = QPushButton('编码', string_encode_gb)
        encode_button.clicked.connect(self.encode_button_slot)
        decode_button = QPushButton('解码', string_encode_gb)
        decode_button.clicked.connect(self.decode_button_slot)
        
        hbox = QHBoxLayout()
        hbox.addWidget(encode_button)
        hbox.addStretch(1)
        hbox.addWidget(decode_button)

        grid = QGridLayout(string_encode_gb)
        grid.addWidget(string_decode_label, 0, 0)
        grid.addWidget(self.string_decode_lineedit, 0, 1)
        grid.addWidget(string_encode_label, 1, 0)
        grid.addWidget(self.string_encode_lineedit, 1, 1)
        grid.addLayout(hbox, 2, 0, 1, 2)
        
        #string_encode_gb.setStyleSheet("QGroupBox { border: 1px solid black; } QGroupBox QLabel { border: none; }")
        vbox.addWidget(string_encode_gb)

        self.setLayout(vbox)
        self.center()

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

    def base64_reverse_string(self):
        """
        """
        
        base64_string = self.base64_string_lineedit.text()
        print('base64_string: {}'.format(base64_string))
        
        # 解码： 字符串 -> 二进制 -> base64编码
        base64_string = eval(base64_string)
        original_string = base64.b64decode(base64_string).decode()
        print('original_string: {}'.format(original_string))
        
        self.original_string_lineedit.setText(str(original_string))

    def original_copy_to_clipboard(self):
        """原字符串内容拷贝
        """
        
        clipboard = QApplication.clipboard()
        clipboard.setText(self.original_string_lineedit.text())

    def new_copy_to_clipboard(self):
        """新字符串内容拷贝
        """
        
        clipboard = QApplication.clipboard()
        clipboard.setText(self.base64_string_lineedit.text())

    def time_btn_slot(self):
        """
        """
        
        time_stamp = int(self.time_edit.text())
        logger.info('time stamp is {}'.format(time_stamp))
        self.time_label.setText(str(datetime.date.fromtimestamp(time_stamp)))

    def decode_button_slot(self):
        """解码
        搞了半天，还问了半天chagpt，始终不能明白我的心，害
        还好我机灵，万物皆可eval
        """
        
        string_encode = self.string_encode_lineedit.text()
        # 在Qt中，QLineEdit的text()函数返回的字符串已经是取消转义的，因此不需要再添加反斜杠
        #string_encode = string_encode.replace('\\', '\\\\')
        print('string_encode: {}'.format(string_encode))
        print(type(string_encode))
        #new_string_encode = "b'{}'".format(string_encode)
        #print(new_string_encode)
        
        # b'\xba\xcd\xc9\xd0'，字符串需要增加反斜杠
        #string_encode = "b'\\xba\\xcd\\xc9\\xd0'"
        print(string_encode)
        string_encode = eval(string_encode)
        print(type(string_encode))
        string_decode = string_encode.decode('gbk')
        print('string_decode: {}'.format(string_decode))
        
        self.string_decode_lineedit.setText(str(string_decode))
        
    def encode_button_slot(self):
        """编码
        """
        
        string_decode = self.string_decode_lineedit.text()
        print('string_decode: {}'.format(string_decode))
        
        string_encode = string_decode.encode('gbk')
        print('string_encode: {}'.format(string_encode))
        
        self.string_encode_lineedit.setText(str(string_encode))

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MyWindow()
    window.show()
    sys.exit(app.exec_())

