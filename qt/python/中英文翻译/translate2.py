# -*- coding: utf-8 -*-
from PyQt5 import QtWidgets
from PyQt5.QtCore import QTranslator
import sys
from test import Ui_MainWindow

class Translate(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self):
        super(Translate,self).__init__()
        self.setupUi(self)
        self.pushButton.clicked.connect(self.translate_chinese)
        self.pushButton_2.clicked.connect(self.translate_english)
        self.trans = QTranslator()

    #翻译成中文
    def translate_chinese(self):
        #默认的中文包，不要新建
        self.trans.load('zh_CN')
        _app = QtWidgets.QApplication.instance()
        _app.installTranslator(self.trans)
        self.retranslateUi(self)

    #翻译成英文
    def translate_english(self):
        # 导入语言包，english是刚才创建的english.qm文件
        self.trans.load('./english.qm')
        print(1)
        _app = QtWidgets.QApplication.instance()
        _app.installTranslator(self.trans)
        self.retranslateUi(self)

if __name__ == '__main__':
    app = QtWidgets.QApplication(sys.argv)
    tranlate = Translate()
    tranlate.show()
    sys.exit(app.exec_())