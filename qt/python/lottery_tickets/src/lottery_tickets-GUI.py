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
import lottery_tickets_interface

class Ui_MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()
        self.ssq_number = None
        self.generate_randrom_numbers_thread = Thread_GenerateRandomNumbers()
        self.generate_randrom_numbers_thread.random_numbers_signal.connect(self.random_numbers_signal_slot)
        
    def initUI(self):
        self.setWindowTitle('福利彩票分析工具')
        self.setGeometry(100, 100, 800, 600)
        self.setFont(QFont("Arial", 18))
        
        #设置饼图数据
        self.pieSeries = QPieSeries()
        self.pieSeries.setHoleSize(0.35)
        self.pieSeries.append('一等奖 1.5%', 1.5)
        self.pieSeries.append('二等奖 8.5%', 8.5)
        self.pieSeries.append('三等奖 12.5%', 12.5)
        self.pieSeries.append('四等奖 17.5%', 17.5)
        self.pieSeries.append('五等奖 20.5%', 20.5)
        pieSlice = self.pieSeries.append('六等奖 20.5%', 20.5)
        pieSlice.setExploded()
        pieSlice.setLabelVisible() #设置标签可见,缺省不可见
        self.pieSeries.append('未中奖 19.0%', 19.0)
        
        
        #图表视图
        self.chartView = QChartView()
        self.chartView.setRenderHint(QPainter.Antialiasing)
        self.chartView.chart().setTitle('该号码历史中奖(0/0)')
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
        self.setStyleSheet('QLabel { border: 1px solid blue; color: blue}')
        self.number_label7.setStyleSheet('border: 1px solid red; color: red')
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

    def visualize_prize_list(self):
        """可视化该号码历史中奖情况
        """
        
        history_data = lottery_tickets_interface.get_history_data(False)
        prize_list = lottery_tickets_interface.is_win_a_prize_in_a_lottery(history_data, self.ssq_number)
        
        first_prize_ratio  = round(prize_list.count(1) * 100 / len(prize_list), 1)
        second_prize_ratio = round(prize_list.count(2) * 100 / len(prize_list), 1)
        third_prize_ratio  = round(prize_list.count(3) * 100 / len(prize_list), 1)
        fourth_prize_ratio = round(prize_list.count(4) * 100 / len(prize_list), 1)
        fifth_prize_ratio  = round(prize_list.count(5) * 100 / len(prize_list), 1)
        sixth_prize_ratio  = round(prize_list.count(6) * 100 / len(prize_list), 1)
        """
        在计算机中，浮点数的存储和运算都有精度限制，可能会出现舍入误差。在这个例子中，0.1 和 0.6 这两个数在二进制下是无限循环小数，因此在计算机中无法精确表示。因此，计算机在进行浮点数运算时，可能会出现一些微小的误差，导致最终结果与预期结果略有不同。
        
        python计算100 - 0.1 - 0.6 - 5.8， 输出是93.50000000000001
        """
        losing_prize_ratio = round(100 - first_prize_ratio - second_prize_ratio - third_prize_ratio - \
            fourth_prize_ratio - fifth_prize_ratio - sixth_prize_ratio, 1)
        
        self.pieSeries.clear()
        self.pieSeries.append('一等奖 {}%'.format(first_prize_ratio), first_prize_ratio)
        self.pieSeries.append('二等奖 {}%'.format(second_prize_ratio), second_prize_ratio)
        self.pieSeries.append('三等奖 {}%'.format(third_prize_ratio), third_prize_ratio)
        self.pieSeries.append('四等奖 {}%'.format(fourth_prize_ratio), fourth_prize_ratio)
        self.pieSeries.append('五等奖 {}%'.format(fifth_prize_ratio), fifth_prize_ratio)
        pieSlice = self.pieSeries.append('六等奖 {}%'.format(sixth_prize_ratio), sixth_prize_ratio)
        pieSlice.setExploded()
        pieSlice.setLabelVisible() #设置标签可见,缺省不可见
        self.pieSeries.append('未中奖 {}%'.format(losing_prize_ratio), losing_prize_ratio)

        self.chartView.chart().setTitle('该号码历史中奖({}/{})'.format( \
            len(prize_list) - prize_list.count(7), len(prize_list)))

    def random_button_slot(self):
        """随机按钮槽函数
        """
        
        if self.generate_randrom_numbers_thread.is_on == True:
            self.generate_randrom_numbers_thread.is_on = False
            self.random_button.setText('开始随机')
            
            self.visualize_prize_list()
            
        else:
            self.generate_randrom_numbers_thread.is_on = True
            self.generate_randrom_numbers_thread.start()
            self.random_button.setText('结束随机')

    def random_numbers_signal_slot(self, random_numbers):
        """
        """
        
        self.ssq_number = ' '.join(str(x) for x in random_numbers)
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
            logger.debug(selected_numbers) # 输出选取的6个数字
            
            red_numbers = list(range(1, 17))
            red_number  = random.sample(red_numbers, 1)
            selected_numbers.append(red_number[0])
            self.random_numbers_signal.emit(selected_numbers)
            time.sleep(0.05) # 必须要设置睡眠时间，不然QLabel来不及切换，使用logger.info打印数字也能解决

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
