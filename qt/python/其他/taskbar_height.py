from PyQt5.QtWidgets import QApplication
import sys

app = QApplication(sys.argv)
dw = app.desktop()  # dw = QDesktopWidget() also works if app is created
taskbar_height = dw.screenGeometry().height() - dw.availableGeometry().height()
print(taskbar_height)