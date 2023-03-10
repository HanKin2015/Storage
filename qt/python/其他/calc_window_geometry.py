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

# 不生效
#widget.windowHandle().screen().geometryChanged.connect(calculateContentHeight)

#timer = QTimer()
#timer.timeout.connect(calculateContentHeight)
#timer.start(1000)  # 延迟1秒钟计算窗口内容的高度

# 计算窗口的框架大小
frameGeometry = widget.frameGeometry()
geometry = widget.geometry()
frameSize = frameGeometry.size() - geometry.size()
print("Frame size:", frameSize)
print(widget.frameGeometry().height())
print(widget.frameSize().height())
print(widget.geometry().height())
print(widget.height())

# 计算窗口内容的高度
frameGeometry = widget.frameGeometry()
frameSize = widget.frameSize()
contentHeight = frameGeometry.height() - frameSize.height()
print("Window height:", frameGeometry.height())
print("Content height:", contentHeight)

sys.exit(app.exec_())