import sys
import time
from PyQt5.QtCore import Qt
from PyQt5.QtWidgets import QApplication, QWidget, QPushButton, QLabel, QVBoxLayout


class Demo(QWidget):
    def __init__(self):
        super(Demo, self).__init__()
        self.count = 0

        self.button = QPushButton('Count', self)
        self.button.clicked.connect(self.count_func)
        self.label = QLabel('0', self)
        self.label.setAlignment(Qt.AlignCenter)

        self.v_layout = QVBoxLayout()
        self.v_layout.addWidget(self.label)
        self.v_layout.addWidget(self.button)
        self.setLayout(self.v_layout)

    def count_func(self):
        while True:
            self.count += 1
            print(self.count)
            self.label.setText(str(self.count))
            time.sleep(1)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    demo = Demo()
    demo.show()
    sys.exit(app.exec_())