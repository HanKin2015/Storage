# -*- coding: utf-8 -*-
from PyQt5 import QtWidgets
import sys
from test import Ui_MainWindow

class Translate(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self):
        super(Translate,self).__init__()
        self.setupUi(self)
        # self.setWindowTitle("")

if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    tranlate = Translate()
    tranlate.show()
    sys.exit(app.exec_())