import sys
from PyQt5.QtWidgets import QApplication, QMainWindow
from PyQt5.QtChart import QChart, QChartView, QPieSeries
from PyQt5.QtCore import Qt, QTimer

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()

        # 创建一个饼图系列
        self.series = QPieSeries()
        self.series.append("A", 1)
        self.series.append("B", 1)
        self.series.append("C", 1)

        # 创建一个图表并将系列添加到图表中
        self.chart = QChart()
        self.chart.addSeries(self.series)
        self.chart.setTitle("Dynamic Pie Chart")
        self.chart.legend().hide()

        # 创建一个图表视图并将图表设置为视图的图表
        self.chartView = QChartView(self.chart)
        self.setCentralWidget(self.chartView)

        # 创建一个定时器并将其连接到更新函数
        self.timer = QTimer()
        self.timer.timeout.connect(self.updateChart)
        self.timer.start(3)

    def updateChart(self):
        # 更新饼图系列的值
        self.series.clear()
        self.series.append("A", 1)
        self.series.append("B", 2)
        self.series.append("C", 3)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    mainWindow = MainWindow()
    mainWindow.show()
    sys.exit(app.exec_())
