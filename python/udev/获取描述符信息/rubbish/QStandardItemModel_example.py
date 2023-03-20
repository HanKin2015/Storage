import sys
from PyQt5.QtWidgets import QApplication, QWidget, QHBoxLayout, QVBoxLayout, QPushButton, QTreeView, QTextEdit, QAbstractItemView, QTableView, QHeaderView
from PyQt5.QtCore import QModelIndex, Qt
from PyQt5.QtGui import QStandardItemModel, QStandardItem

app = QApplication([])
table_view = QTableView()

# 创建模型并设置数据
model = QStandardItemModel(4, 3)
for row in range(4):
    for column in range(3):
        item = QStandardItem(f"({row}, {column})")
        model.setItem(row, column, item)

# 设置标题行
model.setHeaderData(0, Qt.Horizontal, "Column 1")
model.setHeaderData(1, Qt.Horizontal, "Column 2")
model.setHeaderData(2, Qt.Horizontal, "Column 3")

# 设置模型和视图
table_view.setModel(model)
table_view.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
table_view.show()
app.exec_()