# -*- coding: utf-8 -*-
"""
文 件 名: QListWidgetItem_example.py
文件描述: removeItemWidget和takeItem的区别
作    者: HanKin
创建日期: 2023.03.10
修改日期：2023.03.10

Copyright (c) 2023 HanKin. All rights reserved.
"""

from PyQt5.QtWidgets import QApplication, QListWidget, QListWidgetItem, QPushButton

app = QApplication([])

# 创建一个QListWidget
list_widget = QListWidget()

# 设置样式表
list_widget.setStyleSheet('''
    QListWidget {
        border: none;
    }
''')

# 添加一些列表项
for i in range(10):
    item = QListWidgetItem('Item {}'.format(i))
    button = QPushButton('Delete')
    list_widget.addItem(item)
    list_widget.setItemWidget(item, button)
    button.clicked.connect(lambda checked, item=item: list_widget.takeItem(list_widget.row(item)))
    #button.clicked.connect(lambda checked, item=item: list_widget.removeItemWidget(item))

# 设置高度为内容刚好的高度
listWidget.setMinimumHeight(sum([listWidget.sizeHintForRow(i) for i in range(listWidget.count())]) + listWidget.frameWidth() * 2)
listWidget.setMaximumHeight(sum([listWidget.sizeHintForRow(i) for i in range(listWidget.count())]) + listWidget.frameWidth() * 2)

# 显示窗口
list_widget.show()

app.exec_()