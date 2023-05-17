# -*- coding: utf-8 -*-
"""
文 件 名: clear_tool.py
文件描述: 清理工具
作    者: HanKin
创建日期: 2023.04.10
修改日期：2023.04.10

Copyright (c) 2023 HanKin. All rights reserved.
"""

from common import *

class MyWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
        self.clear_tool_thread = Thread_ClearTool()
        self.clear_tool_thread.clear_signal.connect(self.clear_signal_slot)
        self.clear_tool_thread.move_signal.connect(self.move_signal_slot)
        self.clear_tool_thread.done_signal.connect(self.done_signal_slot)
        
    def initUI(self):
        self.setWindowTitle('清理工具')
        self.setGeometry(100, 100, 800, 600)
        
        #设置饼图数据
        self.pieSeries = QPieSeries()
        self.pieSeries.setHoleSize(0.35)
        self.pieSeries.append('蛋白质 4.2%', 4.2)
        pieSlice = self.pieSeries.append('脂肪 15.6%', 15.6)
        pieSlice.setExploded()
        pieSlice.setLabelVisible() #设置标签可见,缺省不可见
        self.pieSeries.append('其他 23.8%', 23.8)
        self.pieSeries.append('碳水化合物 56.4%', 56.4)
        
        
        #图表视图
        self.chartView = QChartView()
        self.chartView.setRenderHint(QPainter.Antialiasing)
        self.chartView.chart().setTitle('文件数量(0/0)')
        self.chartView.chart().addSeries(self.pieSeries)
        self.chartView.chart().legend().setAlignment(Qt.AlignBottom)
        self.chartView.chart().setTheme(QChart.ChartThemeBlueCerulean)
        self.chartView.chart().legend().setFont(QFont('Arial', 8)) #图例字体
        
        self.roll_file_path_label = QLabel('滚动的文字', self)
        self.roll_file_path_label.setAlignment(Qt.AlignCenter)

        vbox = QVBoxLayout()
        vbox.addWidget(self.chartView)        
        vbox.addWidget(self.roll_file_path_label)

        delete_files_path_cb = QComboBox(self)
        delete_files_path_cb.addItem(r'D:\Users\Administrator\My Document\WeChat Files\wxid_2gh9d5knc6th21\FileStorage\MsgAttach')
        delete_files_path_cb.addItem(r'D:\Github\Storage\python\project\files_classify_delete-duplication\a')
        delete_files_path_cb.addItem(r'C:\Users\Administrator\AppData\Local\口袋助理\files')
        clear_button = QPushButton('清理空间', self)
        clear_button.clicked.connect(self.clear_button_slot)
        
        hbox = QHBoxLayout()
        hbox.addWidget(delete_files_path_cb)
        hbox.addWidget(clear_button)
        hbox.setStretch(0, 2)
        fromlayout = QFormLayout()
        fromlayout.addRow(hbox)
        vbox.addLayout(fromlayout)

        # 一条线
        line = QFrame()
        line.setFrameShape(QFrame.HLine)
        line.setFrameShadow(QFrame.Sunken)
        line.setStyleSheet("background-color: #ccc;")
        vbox.addWidget(line) 
        
        delete_files_path_cb = QComboBox(self)
        delete_files_path_cb.addItem(r'D:\hj')
        move_button = QPushButton('移动文件', self)
        move_button.clicked.connect(self.move_button_slot)
        
        hbox = QHBoxLayout()
        hbox.addWidget(delete_files_path_cb, 2)
        hbox.addWidget(move_button)
        vbox.addLayout(hbox)
        
        vbox.setSpacing(20)

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

    def clear_button_slot(self):
        """
        """
        
        self.clear_tool_thread.start()
    
    def done_signal_slot(self):
        """
        """
        
        self.pieSeries.clear()
        self.pieSeries.append('蛋白质 10.2%', 10.2)
        pieSlice = self.pieSeries.append('脂肪 15.6%', 15.6)
        pieSlice.setExploded()
        pieSlice.setLabelVisible()
        self.pieSeries.append('其他 23.8%', 23.8)
        self.pieSeries.append('碳水化合物 50.4%', 50.4)
        #self.chartView.chart().legend().update()

        self.chartView.chart().setTitle('文件数量({})'.format(self.clear_tool_thread.files_count))

    def clear_signal_slot(self, file):
        """
        """
        
        self.roll_file_path_label.setText(file)

    def move_button_slot(self):
        """
        """
        
        self.clear_tool_thread.start()

    def move_signal_slot(self, file):
        """
        """
        
        self.roll_file_path_label.setText(file)

class Thread_ClearTool(QThread):
    clear_signal = pyqtSignal(str)
    move_signal = pyqtSignal(str)
    done_signal = pyqtSignal()

    def __init__(self):
        super(Thread_ClearTool, self).__init__()
        self.files_count = 0

    def delete_specify_type_files(self, root, file):
        self.clear_signal.emit(file)
        return file

    def run_with_ThreadPoolExecutor(self):
        """
        """

        self.files_count = 0
        with ThreadPoolExecutor(max_workers=64) as pool:
            path = r'D:\Users\Administrator\My Document\WeChat Files\wxid_2gh9d5knc6th21\FileStorage\MsgAttach'
            for root, dirs, files in os.walk(path):
                for file in files:
                    self.files_count += 1
                    file_path = os.path.join(root, file)
                    pool.submit(self.delete_specify_type_files, root, file)
        self.done_signal.emit()

    def delete_specify_type_files(self, path):
        """删除指定类型的文件
        后缀名长度大于10的，目前看见最长的比较正常的是.patch
        
        """
        
        delete_files_cnt = 0
        specify_types = ['.log', '.dat', '.rst', '.cpm', '.deb', '.wxtmp', '.gz', '.cd', '.clog']
        for root, dirs, files in os.walk(path):
            for file in files:
                self.files_count += 1
                self.clear_signal.emit(file)
                
                file_path = os.path.join(root, file)
                #print(file_path)
                suffix = os.path.splitext(file_path)[-1]
                try:
                    # 删除后缀名长度过长的
                    if len(suffix) > 10:
                        os.remove(file_path)
                        delete_files_cnt += 1
                    # 删除后缀名长度为0的
                    if len(suffix) == 0:
                        #print(file_path)
                        os.remove(file_path)
                        delete_files_cnt += 1
                    # 删除指定后缀名的（不排除的原因怕有没有记录到的格式被删除）
                    if suffix in specify_types:
                        os.remove(file_path)
                        delete_files_cnt += 1
                    # 删除末尾两个都是数字的
                    if suffix[-1].isdigit() and suffix[-2].isdigit():
                        os.remove(file_path)
                        delete_files_cnt += 1
                except Exception as err:
                    logger.error('delete file [{}] failed, {}'.format(file, err))
        logger.info('there are {} files which are deleted'.format(delete_files_cnt))

    def run(self):
        """
        """

        self.files_count = 0
        path = r'D:\Users\Administrator\My Document\WeChat Files\wxid_2gh9d5knc6th21\FileStorage\MsgAttach'
        self.delete_specify_type_files(path)

        self.done_signal.emit()

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
