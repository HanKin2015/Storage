import sys
from PyQt5.QtWidgets import *
from PyQt5.QtCore import *
from PyQt5.QtGui import *
 
class TrayIcon(QSystemTrayIcon):
    def __init__(self, parent=None):
        super(TrayIcon, self).__init__(parent)
        self.showMenu()
        self.other()
 
    def showMenu(self):
        "设计托盘的菜单，这里我实现了一个二级菜单"
        self.menu = QMenu()
        self.menu1 = QMenu()
        self.showAction1 = QAction("显示消息1", self, triggered=self.showM)
        self.showAction2 = QAction("显示消息2", self,triggered=self.showM)
        self.quitAction = QAction("退出", self, triggered=self.quit)
 
        self.menu1.addAction(self.showAction1)
        self.menu1.addAction(self.showAction2)
        self.menu.addMenu(self.menu1, )
 
        self.menu.addAction(self.showAction1)
        self.menu.addAction(self.showAction2)
        self.menu.addAction(self.quitAction)
        self.menu1.setTitle("二级菜单")
        self.setContextMenu(self.menu)
 
    def other(self):
        self.activated.connect(self.iconClied)
        #把鼠标点击图标的信号和槽连接
        self.messageClicked.connect(self.mClied)
        #把鼠标点击弹出消息的信号和槽连接
        self.setIcon(QIcon("dog.ico"))
        self.icon = self.MessageIcon()
        #设置图标
 
    def iconClied(self, reason):
        "鼠标点击icon传递的信号会带有一个整形的值，1是表示单击右键，2是双击，3是单击左键，4是用鼠标中键点击"
        if reason == 2 or reason == 3:
            pw = self.parent()
            if pw.isVisible():
                pw.hide()
            else:
                pw.show()
        print(reason)
 
    def mClied(self):
        self.showMessage("提示", "你点了消息", self.icon)
 
    def showM(self):
 
        self.showMessage("测试", "我是消息", self.icon)
 
    def quit(self):
        "保险起见，为了完整的退出"
        self.setVisible(False)
        self.parent().exit()
        qApp.quit()
        sys.exit()
 
class window(QWidget):
    def __init__(self, parent=None):
        super(window, self).__init__(parent)
        ti = TrayIcon(self)
        ti.show()
 
if __name__ == "__main__":
    import sys
    app = QApplication(sys.argv)
    w = window()
    w.show()
    sys.exit(app.exec_())