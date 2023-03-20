import sys
from PyQt5.QtWidgets import QApplication, QWidget, QHBoxLayout, QVBoxLayout, QPushButton, QTreeView, QTextEdit, QFileSystemModel, QAbstractItemView
from PyQt5.QtCore import QModelIndex

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()

        # 创建按钮
        button1 = QPushButton('Button 1')
        button2 = QPushButton('Button 2')
        button3 = QPushButton('Button 3')

        # 创建树型结构
        model = QFileSystemModel()
        model.setRootPath('')
        tree_view = QTreeView()
        tree_view.setModel(model)
        tree_view.setRootIndex(model.index(''))
        tree_view.setSelectionMode(QAbstractItemView.SingleSelection)
        tree_view.clicked.connect(self.on_tree_view_clicked)

        # 创建文本框
        text_edit = QTextEdit()

        # 创建布局
        hbox = QHBoxLayout()
        hbox.addWidget(button1)
        hbox.addWidget(button2)
        hbox.addWidget(button3)

        vbox = QVBoxLayout()
        vbox.addLayout(hbox)

        hbox2 = QHBoxLayout()
        hbox2.addWidget(tree_view)
        hbox2.addWidget(text_edit)

        vbox.addLayout(hbox2)

        # 设置主窗口布局
        self.setLayout(vbox)

    def on_tree_view_clicked(self, index: QModelIndex):
        model = index.model()
        file_path = model.filePath(index)
        with open(file_path, 'r', encoding='utf-8') as f:
            content = f.read()
            self.findChild(QTextEdit).setPlainText(content)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())