from PyQt5.QtWidgets import QApplication, QMainWindow, QPushButton, QDialog, QWidget

class SubWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('子窗口')
        self.setGeometry(100, 100, 300, 200)

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle('主窗口')
        self.setGeometry(100, 100, 500, 400)

        button = QPushButton('打开子窗口', self)
        button.setGeometry(50, 50, 100, 30)
        button.clicked.connect(self.open_sub_window)

    def open_sub_window(self):
        sub_window = SubWindow()
        sub_window.exec_()

if __name__ == '__main__':
    app = QApplication([])
    main_window = MainWindow()
    main_window.show()
    app.exec_()
