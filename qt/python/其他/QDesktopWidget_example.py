from PyQt5.QtWidgets import QApplication, QDesktopWidget

app = QApplication([])
desktop = QDesktopWidget()

# 获取桌面的大小和屏幕数量
print('桌面大小:', desktop.screenGeometry())
print('屏幕数量:', desktop.screenCount())

# 获取主屏幕的大小和位置
print('主屏幕大小:', desktop.screenGeometry(0))
print('主屏幕位置:', desktop.screenGeometry(0).topLeft())

# 获取所有屏幕的大小和位置
for i in range(desktop.screenCount()):
    print('屏幕{}大小:'.format(i), desktop.screenGeometry(i))
    print('屏幕{}位置:'.format(i), desktop.screenGeometry(i).topLeft())

app.exec_()