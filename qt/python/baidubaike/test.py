import sys
from PyQt5.QtWidgets import QApplication, QWidget, QHBoxLayout, QVBoxLayout, QLineEdit, QPushButton, QListWidget
import sqlite3

class Example(QWidget):

    def __init__(self):
        super().__init__()

        self.initUI()

    def initUI(self):

        hbox = QHBoxLayout()

        # 创建编辑器
        self.edit = QLineEdit(self)
        hbox.addWidget(self.edit)

        # 创建按钮
        btn = QPushButton('查询', self)
        btn.clicked.connect(self.search)
        hbox.addWidget(btn)

        # 创建列表小部件
        self.listwidget = QListWidget(self)

        # 将编辑器和列表小部件添加到垂直布局中
        vbox = QVBoxLayout()
        vbox.addLayout(hbox)
        vbox.addWidget(self.listwidget)

        self.setLayout(vbox)

        self.setGeometry(300, 300, 350, 300)
        self.setWindowTitle('查询数据库')
        self.show()

    def search(self):

        # 连接到数据库
        conn = sqlite3.connect('example.db')

        # 获取光标
        cur = conn.cursor()

        # 执行查询
        cur.execute("SELECT * FROM table_name WHERE column_name=?", (self.edit.text(),))

        # 获取结果
        results = cur.fetchall()

        # 清空列表小部件
        self.listwidget.clear()

        # 将结果添加到列表小部件中
        for result in results:
            self.listwidget.addItem(str(result))

        # 关闭数据库连接
        conn.close()

if __name__ == '__main__':

    app = QApplication(sys.argv)
    ex = Example()
    sys.exit(app.exec_())
