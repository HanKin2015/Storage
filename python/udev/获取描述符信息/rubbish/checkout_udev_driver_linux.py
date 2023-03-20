import wmi

# 创建WMI对象
wmi_obj = wmi.WMI()

# 监听USB设备连接事件
watcher = wmi_obj.watch_for_notification(notification_type="Creation", wmi_class="Win32_USBControllerDevice")

# 处理USB设备连接事件
while True:
    usb_device = watcher()
    print('USB设备已连接')