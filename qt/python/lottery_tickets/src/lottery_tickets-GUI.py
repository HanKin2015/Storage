# -*- coding: utf-8 -*-
"""
文 件 名: lottery_tickets-GUI.py
文件描述: 福利彩票分析工具
作    者: HanKin
创建日期: 2022.09.16
修改日期：2023.04.11

Copyright (c) 2023 HanKin. All rights reserved.
"""

from common import *

class Ui_MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
        self.generate_randrom_numbers_thread = Thread_GenerateRandomNumbers()
        self.generate_randrom_numbers_thread.random_numbers_signal.connect(self.random_numbers_signal_slot)
        
    def initUI(self):
        self.setWindowTitle('福利彩票分析工具')
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

        vbox = QVBoxLayout()
        vbox.addWidget(self.chartView)
        
        
        self.number_label1 = QLabel('0', self)
        self.number_label2 = QLabel('0', self)
        self.number_label3 = QLabel('0', self)
        self.number_label4 = QLabel('0', self)
        self.number_label5 = QLabel('0', self)
        self.number_label6 = QLabel('0', self)
        horizontal_line    = QLabel('-', self)
        self.number_label7 = QLabel('0', self)
        self.setStyleSheet('QLabel { border: 1px solid blue; }')
        self.number_label7.setStyleSheet('border: 1px solid red')
        horizontal_line.setStyleSheet('border: none')
        
        hbox = QHBoxLayout()
        hbox.addWidget(self.number_label1)
        hbox.addWidget(self.number_label2)
        hbox.addWidget(self.number_label3)
        hbox.addWidget(self.number_label4)
        hbox.addWidget(self.number_label5)
        hbox.addWidget(self.number_label6)
        hbox.addWidget(horizontal_line)
        hbox.addWidget(self.number_label7)
        hbox.setAlignment(Qt.AlignCenter)

        vbox.addLayout(hbox)
        
        self.random_button = QPushButton('开始随机', self)
        self.random_button.clicked.connect(self.random_button_slot)
        vbox.addWidget(self.random_button)
        
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


    def random_button_slot(self):
        """
        """
        
        if self.generate_randrom_numbers_thread.is_on == True:
            self.generate_randrom_numbers_thread.is_on = False
            self.random_button.setText('开始随机')
        else:
            self.generate_randrom_numbers_thread.is_on = True
            self.generate_randrom_numbers_thread.start()
            self.random_button.setText('结束随机')

    def random_numbers_signal_slot(self, random_numbers):
        """
        """
        
        self.number_label1.setText(str(random_numbers[0]))
        self.number_label2.setText(str(random_numbers[1]))
        self.number_label3.setText(str(random_numbers[2]))
        self.number_label4.setText(str(random_numbers[3]))
        self.number_label5.setText(str(random_numbers[4]))
        self.number_label6.setText(str(random_numbers[5]))
        self.number_label7.setText(str(random_numbers[6]))

class Thread_GenerateRandomNumbers(QThread):
    random_numbers_signal = pyqtSignal(list)

    def __init__(self):
        super(Thread_GenerateRandomNumbers, self).__init__()
        self.is_on = False

    def run(self):
        """线程run函数
        """

        while self.is_on:
            blue_numbers = list(range(1, 33))  # 生成1到32的数字列表
            selected_numbers = random.sample(blue_numbers, 6)  # 从数字列表中随机选取6个数字
            selected_numbers = sorted(selected_numbers)
            logger.info(selected_numbers) # 输出选取的6个数字
            
            red_numbers = list(range(1, 17))
            red_number  = random.sample(red_numbers, 1)
            selected_numbers.append(red_number[0])
            self.random_numbers_signal.emit(selected_numbers)

def main():
    """主函数
    """

    app = QApplication(sys.argv)
    mainwindow = Ui_MainWindow()
    mainwindow.show()
    sys.exit(app.exec_())

if __name__ == '__main__':
    #os.system('chcp 936 & cls')
    logger.info('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    logger.info('process spend {} s.\n'.format(round(end_time - start_time, 3)))
