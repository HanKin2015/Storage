import sys
from PyQt5.QtCore import QTimer
from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QApplication, QSystemTrayIcon
class SystemTrayIcon(QSystemTrayIcon):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.toggleIcon)
        self.icon1 = QIcon("../img/msg.png")  # 未读消息图标
        self.icon2 = QIcon("../img/udev_detect.png")  # 已读消息图标
        self.setIcon(self.icon1)  # 设置初始图标
        self.unread_message_count = 0  # 未读消息数
    def toggleIcon(self):
        if self.isVisible():
            if self.icon().cacheKey() == self.icon1.cacheKey():
                self.setIcon(self.icon2)
            else:
                self.setIcon(self.icon1)
    def showMessage(self, title, message, icon=QSystemTrayIcon.Information, timeout=5000):
        super(SystemTrayIcon, self).showMessage(title, message, icon, timeout)
        self.unread_message_count += 1  # 未读消息数加1
        if not self.timer.isActive():
            self.timer.start(500)  # 开始定时器
    def clearMessage(self):
        self.timer.stop()  # 停止定时器
        self.unread_message_count = 0  # 未读消息数清零
        self.setIcon(self.icon2)  # 设置已读消息图标
if __name__ == '__main__':
    app = QApplication(sys.argv)
    system_tray_icon = SystemTrayIcon()
    system_tray_icon.show()
    system_tray_icon.showMessage("新消息", "您有一条新消息")
    sys.exit(app.exec_())