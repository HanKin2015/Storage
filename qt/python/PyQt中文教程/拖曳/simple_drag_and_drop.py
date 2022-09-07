# -*- coding: utf-8 -*-
"""
文 件 名: simple_drag_and_drop.py
文件描述: 简单的拖放(把一个文本从编辑框里拖到按钮上，更新按钮上的标签文字)
作    者: HanKin
创建日期: 2022.09.07
修改日期：2022.09.07

Copyright (c) 2022 HanKin. All rights reserved.
"""

from PyQt5.QtWidgets import (QPushButton, QWidget, 
    QLineEdit, QApplication)
import sys

class Button(QPushButton):
    def __init__(self, title, parent):
        super().__init__(title, parent)
        self.setAcceptDrops(True)   # 激活组件的拖拽事件

    def dragEnterEvent(self, e):
        if e.mimeData().hasFormat('text/plain'):    # 设定好接受拖拽的数据类型
            e.accept()
        else:
            e.ignore() 

    def dropEvent(self, e):     # 更改按钮接受鼠标的释放事件的默认行为
        self.setText(e.mimeData().text()) 

class Example(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        edit = QLineEdit('', self)
        edit.setDragEnabled(True)   # QLineEdit默认支持拖拽操作，所以我们只要调用setDragEnabled()方法使用就行了
        edit.move(30, 65)

        button = Button("Button", self)
        button.move(190, 65)

        self.setWindowTitle('Simple drag and drop')
        self.setGeometry(300, 300, 300, 150)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Example()
    ex.show()
    app.exec_()