# -*- coding: utf-8 -*-
"""
文 件 名: lottery_tickets-GUI.py
文件描述: 福利彩票分析工具
作    者: HanKin
创建日期: 2022.09.16
修改日期：2022.09.16

Copyright (c) 2022 HanKin. All rights reserved.
"""

import sys
from PyQt5.QtWidgets import QMainWindow, QAction, qApp, QApplication, QMenu, QTextEdit
from PyQt5.QtGui import QIcon
from log import *

class Example(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        # 状态栏是用来显示应用的状态信息的组件
        self.statusbar = self.statusBar()
        self.statusbar.showMessage('Ready')
        
        # 菜单栏是一组命令的集合
        menubar = self.menuBar()
        fileMenu = menubar.addMenu('&File')
        
        exitAct = QAction(QIcon('../img/logo.png'), '&Exit', self)        
        exitAct.setShortcut('Ctrl+Q')
        exitAct.setStatusTip('Exit application')
        exitAct.triggered.connect(qApp.quit)
        fileMenu.addAction(exitAct)
        
        # 子菜单是嵌套在菜单里面的二级或者三级等的菜单
        impMenu = QMenu('Import', self)
        impAct = QAction('Import mail', self) 
        impMenu.addAction(impAct)
        newAct = QAction('New', self)        
        fileMenu.addAction(newAct)
        fileMenu.addMenu(impMenu)
    
        # 勾选菜单
        viewMenu = menubar.addMenu('View')
        viewStatAct = QAction('View statusbar', self, checkable=True)
        viewStatAct.setStatusTip('View statusbar')
        viewStatAct.setChecked(True)    # 默认设置为选中状态
        viewStatAct.triggered.connect(self.toggleMenu)
        viewMenu.addAction(viewStatAct)

        # 工具栏就是常用的命令的集合
        self.toolbar = self.addToolBar('Exit')
        self.toolbar.addAction(exitAct)

        # 文本编辑区域
        textEdit = QTextEdit()
        self.setCentralWidget(textEdit)

        self.setGeometry(300, 300, 300, 200)
        self.setWindowTitle('福利双色球')
        self.setWindowIcon(QIcon('../img/logo.png'))
        self.show()

    def toggleMenu(self, state):
        if state:
            self.statusbar.show()
        else:
            self.statusbar.hide()

    def contextMenuEvent(self, event):
        """右键菜单也叫弹出框
        """
        cmenu = QMenu(self)
        newAct = cmenu.addAction("New")
        opnAct = cmenu.addAction("Open")
        quitAct = cmenu.addAction("Quit")
        action = cmenu.exec_(self.mapToGlobal(event.pos()))
        if action == quitAct:
            qApp.quit()

if __name__ == '__main__':
    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())