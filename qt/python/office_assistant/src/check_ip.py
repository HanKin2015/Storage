# -*- coding: utf-8 -*-
"""
文 件 名: check_ip.py
文件描述: 检测ip存活
作    者: HanKin
创建日期: 2023.04.06
修改日期：2024.02.27

Copyright (c) 2024 HanKin. All rights reserved.
"""

import sys
from PyQt5.QtWidgets import QApplication, QWidget, QLabel, \
    QLineEdit, QGridLayout, QPushButton, QHBoxLayout, QDesktopWidget, \
    QFrame, QListWidget, QListWidgetItem, QVBoxLayout, QHeaderView, \
    QStyledItemDelegate, QMessageBox
import base64
from PyQt5.QtGui import QPen, QPainter
from PyQt5.QtCore import Qt, QThread, pyqtSignal
from log import *
import time
import _thread
from subprocess import Popen, PIPE

class ListDelegate(QStyledItemDelegate):
    def paint(self, painter, option, index):
        super().paint(painter, option, index)
        if index.row() < index.model().rowCount() - 1:
            pen = QPen(Qt.gray, 1, Qt.SolidLine)
            painter.setPen(pen)
            painter.drawLine(option.rect.bottomLeft(), option.rect.bottomRight())

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
        self.check_ip_thread = Thread_CheckIP()
        self.check_ip_thread.check_done_signal.connect(self.check_done_signal_slot)

    def initUI(self):
        self.setWindowTitle('检测IP存活')
        self.setGeometry(100, 100, 500, 300)

        ip_address_range_label = QLabel('IP地址范围:', self)
        point_label1 = QLabel('.', self)
        point_label2 = QLabel('.', self)
        point_label3 = QLabel('.', self)
        right_arrow_label = QLabel('-->', self)
        self.ip_address_lineedit1 = QLineEdit(self)
        self.ip_address_lineedit1.setText('110')
        self.ip_address_lineedit2 = QLineEdit(self)
        self.ip_address_lineedit2.setText('242')
        self.ip_address_lineedit3 = QLineEdit(self)
        self.ip_address_lineedit3.setText('68')
        self.ip_address_lineedit4 = QLineEdit(self)
        self.ip_address_lineedit4.setText('0')
        self.ip_address_lineedit5 = QLineEdit(self)
        self.ip_address_lineedit5.setText('255')
        self.scan_button = QPushButton('扫描', self)
        self.scan_button.clicked.connect(self.scan_button_slot)

        hbox = QHBoxLayout()
        hbox.addWidget(ip_address_range_label)
        hbox.addWidget(self.ip_address_lineedit1)
        hbox.addWidget(point_label1)
        hbox.addWidget(self.ip_address_lineedit2)
        hbox.addWidget(point_label2)
        hbox.addWidget(self.ip_address_lineedit3)
        hbox.addWidget(point_label3)
        
        frame = QFrame()
        frame.setFrameStyle(QFrame.Panel | QFrame.Sunken)
        frame.setLineWidth(2)
        frameLayout = QHBoxLayout(frame)
        frameLayout.addWidget(self.ip_address_lineedit4)
        frameLayout.addWidget(right_arrow_label)
        frameLayout.addWidget(self.ip_address_lineedit5)
        #frame.setStyleSheet("border: 1px solid black;")
        hbox.addWidget(frame)
        
        hbox.addWidget(self.scan_button)
        
        self.ip_up_list_widget = QListWidget()
        self.ip_up_list_widget.setStyleSheet("border: 1px solid black;")
        self.ip_up_list_widget.setItemDelegate(ListDelegate())

        vbox = QVBoxLayout()
        vbox.addLayout(hbox)
        vbox.addWidget(self.ip_up_list_widget)

        self.setStyleSheet("QLineEdit { border: 1px solid black; }")
        self.setLayout(vbox)
        self.center()
        self.show()

    def center(self):
        """居中显示
        """
        
        qr = self.frameGeometry()
        cp = QApplication.desktop().availableGeometry().center()
        qr.moveCenter(cp)
        self.move(qr.topLeft())

    def check_valid(self, lineedit):
        """检查IP地址的合法性
        """

        ip_address_segment = lineedit.text()
        if ip_address_segment == '':
            logger.error('IP address is null')
            return None

        if not ip_address_segment.isdigit():
            logger.error('IP address segment [{}] is not digit'.format(ip_address_segment))
            return None

        if int(ip_address_segment) < 0 or int(ip_address_segment) > 255:
            logger.error('IP address segment [{}] is not in between 0 and 255'.format(ip_address_segment))
            return None
            
        return int(ip_address_segment)

    def scan_button_slot(self):
        """扫描按钮槽函数
        """
        
        ip_address_segment1 = self.check_valid(self.ip_address_lineedit1)
        ip_address_segment2 = self.check_valid(self.ip_address_lineedit2)
        ip_address_segment3 = self.check_valid(self.ip_address_lineedit3)
        ip_address_segment4 = self.check_valid(self.ip_address_lineedit4)
        ip_address_segment5 = self.check_valid(self.ip_address_lineedit5)
        logger.info('ip address: {}.{}.{}.{}->{}'.format(ip_address_segment1,
            ip_address_segment2, ip_address_segment3, ip_address_segment4, ip_address_segment5))
        if any(ip_address_segment is None for ip_address_segment in (ip_address_segment1, ip_address_segment2, \
                                            ip_address_segment3, ip_address_segment4, ip_address_segment5)):
            logger.error('IP address invalid')
            QMessageBox.information(self, 'IP地址合法性', 'IP地址不合法')
            return

        if ip_address_segment4 > ip_address_segment5:
            logger.error('IP address range invalid, {}->{}'.format(ip_address_segment4, ip_address_segment5))
            QMessageBox.information(self, 'IP地址合法性', 'IP地址范围错误')
            return
        
        # 清空QListWidget
        for i in range(self.ip_up_list_widget.count() - 1, -1, -1):
            item = self.ip_up_list_widget.item(i);
            self.ip_up_list_widget.takeItem(self.ip_up_list_widget.row(item))

        self.check_ip_thread.ip_address_segment1 = ip_address_segment1
        self.check_ip_thread.ip_address_segment2 = ip_address_segment2
        self.check_ip_thread.ip_address_segment3 = ip_address_segment3
        self.check_ip_thread.ip_address_segment4 = ip_address_segment4
        self.check_ip_thread.ip_address_segment5 = ip_address_segment5
        self.scan_button.setText("扫描中...")
        self.check_ip_thread.start()

    def check_done_signal_slot(self):
        """扫描完成信号函数
        """
   
        for ip_up in self.check_ip_thread.ip_up_list:
            item = QListWidgetItem(ip_up)
            self.ip_up_list_widget.addItem(item)
        self.scan_button.setText("扫描")
        QMessageBox.information(self, '检测IP存活', '检测完成')

class Thread_CheckIP(QThread):
    check_done_signal = pyqtSignal()

    def __init__(self):
        super(Thread_CheckIP, self).__init__()
        self.ip_address_segment1 = 0
        self.ip_address_segment2 = 0
        self.ip_address_segment3 = 0
        self.ip_address_segment4 = 0
        self.ip_address_segment5 = 0
        self.ip_up_list = []

    def ping_check(self, ip):
        """使用ping命令检测存活
        """
        
        check = Popen('ping {0} \n'.format(ip), stdin=PIPE, stdout=PIPE, shell=True)
        data = check.stdout.read()  # 数据
        data = data.decode('gbk')   # 编码转换:byte->str
        if 'TTL' in data: # 存活
            sys.stdout.write('%s is up \n' % ip)
            logger.debug('{} is up'.format(ip))
            self.ip_up_list.append('{} is up'.format(ip))
            return True
        return False

    def run(self):
        """
        """
        
        for i in range(self.ip_address_segment4, self.ip_address_segment5 + 1):
            ip = '{}.{}.{}.{}'.format(self.ip_address_segment1, self.ip_address_segment2, self.ip_address_segment3, i)
            logger.info('ping {}......'.format(ip))
            _thread.start_new_thread(self.ping_check, (ip, ))
            time.sleep(0.1)
        time.sleep(3)
        self.check_done_signal.emit()
        
if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MainWindow()
    sys.exit(app.exec_())

