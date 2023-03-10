from PyQt5.QtWidgets import QApplication, QMessageBox
import sys

app = QApplication(sys.argv)

msgBox = QMessageBox()
msgBox.setWindowTitle("Message Box")
msgBox.setText("Hello, World!")
msgBox.setGeometry(0, 0, 400, 200)  # 设置对话框大小
msgBox.move(app.desktop().screen().rect().center() - msgBox.rect().center())  # 将对话框放置在屏幕中央
msgBox.setIcon(QMessageBox.Information)  # 设置对话框类型为信息框
msgBox.show()  # 显示对话框

sys.exit(app.exec_())