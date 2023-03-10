from PyQt5.QtWidgets import QApplication, QWidget
from PyQt5.QtCore import QTimer
import sys

app = QApplication(sys.argv)

widget = QWidget()
widget.setWindowTitle("Window Title")
widget.setGeometry(100, 100, 400, 300)
widget.show()

# 延迟计算窗口内容的高度
def calculateContentHeight():
    frameGeometry = widget.frameGeometry()
    frameSize = widget.frameSize()
    contentHeight = frameGeometry.height() - frameSize.height()
    print("Window height:", frameGeometry.height())
    print("Content height:", contentHeight)

#timer = QTimer()
#timer.timeout.connect(calculateContentHeight)
#timer.start(1000)  # 延迟1秒钟计算窗口内容的高度
print(widget.frameGeometry().height())
print(widget.frameSize().height())
print(widget.geometry().height())
print(widget.height())

sys.exit(app.exec_())