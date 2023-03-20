import wmi
import win32api

# 初始化WMI对象
wmi_obj = wmi.WMI()

# 查询所有USB设备
usb_devices = wmi_obj.query("SELECT * FROM Win32_USBHub")

# 遍历USB设备并判断是否为摄像头
for device in usb_devices:
    print(device)

    # 获取设备描述符信息
    descriptor = device.DeviceID
    print(device.Name, device.DeviceID)

    # 判断设备是否为摄像头
    if "VID_XXXX&PID_XXXX&MI_XX" in descriptor:
        # 获取设备名称
        device_name = device.Name

        # 判断设备是否为摄像头
        if "camera" in device_name.lower():
            print("该USB设备为摄像头")