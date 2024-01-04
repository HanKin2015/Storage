# -*- coding: utf-8 -*-
"""
文 件 名: base64_convert_string.py
文件描述: 使用base64编码转换字符串
作    者: HanKin
创建日期: 2023.04.03
修改日期：2023.04.03

Copyright (c) 2023 HanKin. All rights reserved.
"""
from PyQt5.QtWidgets import QApplication, QWidget, QHBoxLayout, \
    QVBoxLayout, QPushButton, QTreeView, QTextEdit, QAbstractItemView, \
    QMenuBar, QStatusBar, QMainWindow, QMenu, QAction, QLabel, QMessageBox, \
    QDesktopWidget, qApp, QTabWidget, QSystemTrayIcon, QToolTip, QListWidgetItem, \
    QListWidget, QInputDialog, QStyledItemDelegate, QLineEdit, QFrame, \
    QComboBox, QFormLayout, QSizePolicy, QGridLayout, QGroupBox, QFileDialog, \
    QToolBar, QRadioButton, QDialog
from PyQt5.QtCore import QModelIndex, Qt, QCoreApplication, QMetaObject, QThread, \
    pyqtSignal, QRect, QTimer, QPoint, QObject, QEvent
from PyQt5.QtGui import QStandardItemModel, QStandardItem, QIcon, \
    QPainter, QColor, QBrush, QPen, QFont, QCursor, QGuiApplication
from PyQt5.QtNetwork import QUdpSocket, QHostAddress
from  PyQt5.QtChart import QChart, QChartView, QPieSeries, QPieSlice
import sys

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setWindowTitle('变量生成器')
        self.setGeometry(100, 100, 400, 200)
        
        # 整体垂直布局
        vbox = QVBoxLayout()
        
        # 第一个QFrame，base64编码字符串
        base64_convert_string_gb = QGroupBox('变量生成器', self)
        original_string_label = QLabel('原变量:', base64_convert_string_gb)
        self.original_string_lineedit = QLineEdit(base64_convert_string_gb)

        base64_string_label = QLabel('新变量:', base64_convert_string_gb)
        self.base64_string_lineedit = QLineEdit(base64_convert_string_gb)
        self.base64_string_lineedit.setReadOnly(True)  # 设置为不可编辑状态

        convert_button = QPushButton('转换', base64_convert_string_gb)
        convert_button.clicked.connect(self.base64_convert_string)
        original_copy_button = QPushButton('复制', base64_convert_string_gb)
        original_copy_button.clicked.connect(self.original_copy_to_clipboard)

        hbox = QHBoxLayout()
        hbox.addWidget(convert_button)
        hbox.addWidget(original_copy_button)

        grid = QGridLayout(base64_convert_string_gb)
        grid.addWidget(original_string_label, 0, 0)
        grid.addWidget(self.original_string_lineedit, 0, 1)
        grid.addWidget(base64_string_label, 1, 0)
        grid.addWidget(self.base64_string_lineedit, 1, 1)
        grid.addLayout(hbox, 2, 0, 1, 2)
        
        #base64_convert_string_gb.setStyleSheet("QFrame { border: 1px solid black; } QFrame QLabel { border: none; }")
        vbox.addWidget(base64_convert_string_gb)

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
        
        original_variable = self.original_string_lineedit.text()
        print('original_variable: {}'.format(original_variable))
        
        new_variable = original_variable.upper()
        new_variable = new_variable.replace(' ', '_')
        print('base64_string: {}'.format(new_variable))
        
        self.base64_string_lineedit.setText(new_variable)

    def original_copy_to_clipboard(self):
        """原字符串内容拷贝
        """
        
        clipboard = QApplication.clipboard()
        clipboard.setText(self.base64_string_lineedit.text())

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())

