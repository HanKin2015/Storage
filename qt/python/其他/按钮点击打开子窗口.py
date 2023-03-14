import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QWidget, QLabel, QPushButton
class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()
    def initUI(self):
        self.setWindowTitle('Main Window')
        self.setGeometry(100, 100, 800, 600)
        # 向主窗口添加按钮，点击后创建子窗口
        btn = QPushButton('Open Sub Window', self)
        btn.move(50, 300)
        btn.clicked.connect(self.createSubWindow)
    def createSubWindow(self):
        # 创建子窗口，并将主窗口设置为其父窗口
        self.subwindow = QWidget(self)
        self.subwindow.setGeometry(50, 50, 200, 200)
        # 向子窗口添加控件
        label = QLabel('This is a subwindow', self.subwindow)
        label.move(50, 50)
        # 显示子窗口
        self.subwindow.show()
if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())