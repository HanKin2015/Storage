# -*- coding: utf-8 -*-
"""
Created on Mon Aug 31 13:35:01 2020

@author: Administrator
"""

#!/usr/bin/env python3
from PyQt5.QtGui import QPixmap
from PyQt5 import QtWidgets
from PyQt5.QtCore import Qt
import requests
from os.path import expanduser


class Ui_qrDlg():

    def setupUi(self):
        self.setFixedSize(650, 400)
        self.setWindowTitle('生成二维码/短网址')
        self.setWindowFlags(Qt.WindowCloseButtonHint)
        self.center()

        gBoxStyle = '''QGroupBox{border-width:1px;border-style:solid;border-color:grey;margin-top:0.85ex;}
            QGroupBox::title{subcontrol-origin:margin;subcontrol-position:top left;left:10px;margin-left:0px;padding:0 1px;}'''
        self.gBoxInfo = QtWidgets.QGroupBox(self, title='输入内容')
        self.gBoxInfo.setGeometry(12, 10, 300, 380)
        self.gBoxInfo.setStyleSheet(gBoxStyle)
        self.textEdit = QtWidgets.QTextEdit(self.gBoxInfo)
        self.textEdit.setGeometry(7, 30, 286, 300)
        self.textEdit.setObjectName('textEdit')
        self.urlShow = QtWidgets.QTextEdit(self)
        self.urlShow.setGeometry(385, 12, 253, 30)
        self.urlShow.setObjectName('urlShow')
        self.urlShow.setReadOnly(True)
        self._label = QtWidgets.QLabel(self, text='短网址：')
        self._label.setGeometry(325, 12, 60, 30)
        self._label.setAlignment(Qt.AlignCenter)
        self.btnCreate = QtWidgets.QPushButton(self.gBoxInfo, text='生成')
        self.btnCreate.setGeometry(7, 338, 286, 35)
        self.btnCreate.setObjectName('btnCreate')
        self.gBoxPic = QtWidgets.QGroupBox(self, title='二维码')
        self.gBoxPic.setGeometry(325, 45, 313, 345)
        self.gBoxPic.setStyleSheet(gBoxStyle)
        self.label = QtWidgets.QLabel(self.gBoxPic)
        self.label.setGeometry(0, 14, 313, 313)
        self.label.setAlignment(Qt.AlignCenter)
        self.btnSave = QtWidgets.QPushButton(self.gBoxPic, text='另存为')
        self.btnSave.setGeometry(220, 300, 80, 40)
        self.btnSave.setObjectName('btnSave')
        self.btnSave.hide()

    def center(self):
        screen = QtWidgets.QDesktopWidget().screenGeometry()
        size = self.geometry()
        self.move((screen.width() - size.width()) / 2, (screen.height() - size.height()) / 2)


class qrDlg(QtWidgets.QDialog, Ui_qrDlg):

    def __init__(self, parent=None):
        super(qrDlg, self).__init__(parent)
        self.setupUi()
        self.btnCreate.clicked.connect(self.on_btnCreate_clicked)
        self.btnSave.clicked.connect(self.on_btnSave_clicked)

    def on_btnCreate_clicked(self):
        import qrcode
        info = self.textEdit.toPlainText().strip()
        if not info:
            QtWidgets.QMessageBox.information(self, ('提示'), ('请填写信息'), QtWidgets.QMessageBox.Yes)
            self.btnSave.hide()
            self.label.clear()
        else:
            qr = qrcode.QRCode(version=12, error_correction=qrcode.constants.ERROR_CORRECT_L, box_size=3, border=4)
            qr.add_data(info)
            # qr.make(fit=True)
            img = qr.make_image()
            filename = expanduser('~') + '/.qr_code.png'
            img.save(filename)
            pic = QPixmap(filename)
            self.label.setPixmap(pic)
            self.btnSave.show()
            if info.startswith('http://') or info.startswith('https://'):
                self.urlShow.setText(get_short_url(info))
                self.urlShow.selectAll()

    def on_btnSave_clicked(self):
        qrPic = self.label.pixmap()
        if qrPic:
            filename, extra = QtWidgets.QFileDialog.getSaveFileName(self, '另存为', expanduser('~') + '/Desktop', 'PNG Images (*.png)')
            if filename:
                qrPic.save(filename, 'png')


def get_short_url(url, data=None):
    baseurl = 'http://api.t.sina.com.cn/short_url/shorten.json?source=3271760578&url_long='
    url = baseurl + url
    rep = requests.get(url, timeout=60)
    return rep.json()[0]['url_short']


if __name__ == '__main__':
    import sys
    app = QtWidgets.QApplication(sys.argv)
    Dlg = qrDlg()
    Dlg.show()
    sys.exit(app.exec_())