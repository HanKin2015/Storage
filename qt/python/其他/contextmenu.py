from PyQt5.QtWidgets import QApplication, QMainWindow, QMenu, QAction
from PyQt5.QtCore import Qt

class MyWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setGeometry(100, 100, 300, 200)
        self.setWindowTitle('右键菜单')

        # 创建一个右键菜单
        self.contextMenu = QMenu(self)
        self.copyAction = QAction('复制', self)
        self.contextMenu.addAction(self.copyAction)

        # 将右键菜单绑定到窗口上
        self.setContextMenuPolicy(Qt.CustomContextMenu)
        self.customContextMenuRequested.connect(self.showContextMenu)

    def showContextMenu(self, pos):
        self.contextMenu.exec_(self.mapToGlobal(pos))

if __name__ == '__main__':
    app = QApplication([])
    window = MyWindow()
    window.show()
    app.exec_()
