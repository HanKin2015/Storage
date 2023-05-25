# -*- coding: utf-8 -*-
"""
文 件 名: Ui_CheckIP.py
文件描述: 检测ip存活
作    者: HanKin
创建日期: 2023.04.06
修改日期：2023.04.06

Copyright (c) 2023 HanKin. All rights reserved.
"""

from common import *

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
        self.check_ip_thread.ip_up_signal.connect(self.ip_up_signal_slot)

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
        self.ip_address_lineedit4.setText('1')
        self.ip_address_lineedit5 = QLineEdit(self)
        self.ip_address_lineedit5.setText('25')
        scan_button = QPushButton('扫描', self)
        scan_button.clicked.connect(self.scan_button_slot)

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
        
        hbox.addWidget(scan_button)
        
        self.ip_up_list_widget = QListWidget()
        self.ip_up_list_widget.setStyleSheet("border: 1px solid black;")
        self.ip_up_list_widget.setItemDelegate(ListDelegate())

        vbox = QVBoxLayout()
        vbox.addLayout(hbox)
        vbox.addWidget(self.ip_up_list_widget)

        self.setStyleSheet("QLineEdit { border: 1px solid black; }")
        self.setLayout(vbox)
        self.center()

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
            return

        if int(ip_address_segment) < 1 or int(ip_address_segment) > 254:
            logger.error('IP address segment [{}] is not in between 1 and 254'.format(ip_address_segment))
            return
            
        return int(ip_address_segment)

    def scan_button_slot(self):
        """扫描检测IP存活地址
        """
        
        ip_address_segment1 = self.check_valid(self.ip_address_lineedit1)
        ip_address_segment2 = self.check_valid(self.ip_address_lineedit2)
        ip_address_segment3 = self.check_valid(self.ip_address_lineedit3)
        ip_address_segment4 = self.check_valid(self.ip_address_lineedit4)
        ip_address_segment5 = self.check_valid(self.ip_address_lineedit5)
        logger.info('ip address: {}.{}.{}.{}->{}'.format(ip_address_segment1,
            ip_address_segment2, ip_address_segment3, ip_address_segment4, ip_address_segment5))
        if not ip_address_segment1 or not ip_address_segment2 or not ip_address_segment3 \
            or not ip_address_segment4 or not ip_address_segment5:
            logger.error('IP address invalid')
            return

        if ip_address_segment4 > ip_address_segment5:
            logger.error('IP address range invalid, {}->{}'.format(ip_address_segment4, ip_address_segment5))
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
        self.check_ip_thread.start()

    def ip_up_signal_slot(self, ip_up):
        """
        """
        
        item = QListWidgetItem(ip_up)
        self.ip_up_list_widget.addItem(item)

    def check_done_signal_slot(self):
        """
        """
   
        QMessageBox.information(self, '检测IP存活', '检测完成')

class Thread_CheckIP(QThread):
    check_done_signal = pyqtSignal()
    ip_up_signal = pyqtSignal(str)

    def __init__(self):
        super(Thread_CheckIP, self).__init__()
        self.ip_address_segment1 = 0
        self.ip_address_segment2 = 0
        self.ip_address_segment3 = 0
        self.ip_address_segment4 = 0
        self.ip_address_segment5 = 0
        self.ip_up_list = []

    def ping_check(self, index, ip):
        """使用ping命令检测存活
        """
        
        check = Popen('ping {0} \n'.format(ip), stdin=PIPE, stdout=PIPE, shell=True)
        data = check.stdout.read()  # 数据
        data = data.decode('gbk')   # 编码转换:byte->str
        if 'TTL' in data: # 存活
            #sys.stdout.write('%s is up \n' % ip)
            logger.debug('{} is up'.format(ip))
            self.ip_up_list.append((index, '{} is up'.format(ip)))
            
            return True
        return False

    def run(self):
        """
        """
        
        tasks = []
        with ThreadPoolExecutor(max_workers=64) as pool:
            for i in range(self.ip_address_segment4, self.ip_address_segment5 + 1):
                ip = '{}.{}.{}.{}'.format(self.ip_address_segment1, self.ip_address_segment2, self.ip_address_segment3, i)
                logger.info('ping {}......'.format(ip))

                task = pool.submit(self.ping_check, i, ip)
                tasks.append(task)
    
        self.ip_up_list = sorted(self.ip_up_list, key=lambda x: x[0])
        for ip_up in self.ip_up_list:
            self.ip_up_signal.emit(ip_up[1])
        self.check_done_signal.emit()
        
def main():
    app = QApplication(sys.argv)
    window = MyWindow()
    window.show()
    sys.exit(app.exec_())

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    logger.info('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    logger.info('process spend {} s.\n'.format(round(end_time - start_time, 3)))

