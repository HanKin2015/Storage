# -*- coding: utf-8 -*-
"""
文 件 名: hello_pyqt5.py
文件描述: 验证pyqt5的安装情况
作    者: HanKin
创建日期: 2022.09.05
修改日期：2022.09.05

Copyright (c) 2022 HanKin. All rights reserved.
"""

import sys
from PyQt5.QtWidgets import QWidget, QApplication

# 过程式编程
if __name__ == '__main__':
    app = QApplication(sys.argv)
    widget = QWidget()
    widget.resize(250, 150)
    widget.move(300, 300)
    widget.setWindowTitle("Hello, PyQt5!")
    widget.show()
    
    # exec_()之所以有个下划线，是因为exec是一个Python的关键字。但是都可以
    #sys.exit(app.exec())
    sys.exit(app.exec_())