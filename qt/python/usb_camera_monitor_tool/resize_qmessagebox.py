from PyQt5.QtWidgets import QApplication, QMessageBox

app = QApplication([])
msgBox = QMessageBox()
msgBox.setWindowTitle("My MessageBox") # 设置标题
msgBox.setText("Hello World!") # 设置文本
msgBox.setMaximumHeight(800) # 设置固定高度
msgBox.exec_()
app.exec_()
