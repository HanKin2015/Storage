'''
自动桌面提示

这个脚本会自动触发windows桌面通知，提示重要事项，比如说：您已工作两小时，该休息了

我们可以设定固定时间提示，比如隔10分钟、1小时等

用到的第三方库：

win10toast - 用于发送桌面通知的工具
'''

from win10toast import ToastNotifier
import time
toaster = ToastNotifier()

header = input("What You Want Me To Remember\n")
text = input("Releated Message\n")
time_min=float(input("In how many minutes?\n"))

time_min = time_min * 60
print("Setting up reminder..")
time.sleep(2)
print("all set!")
time.sleep(time_min)
toaster.show_toast(f"{header}", f"{text}", duration=10, threaded=True)
while toaster.notification_active(): time.sleep(0.005)


