import win32com.client
# 创建WMI服务对象
wmi = win32com.client.GetObject("winmgmts:")
# 枚举Win32_USBControllerDevice类中的所有设备
usb_controllers = wmi.ExecQuery("SELECT * FROM Win32_USBControllerDevice")
# 遍历所有设备，获取其PNPDeviceID
for usb_controller in usb_controllers:
    pnp_device_id = usb_controller.Dependent.split("=")[1].replace('"', '')
    # 获取设备对应的Win32_PnPEntity对象
    devices = wmi.ExecQuery("SELECT * FROM Win32_PnPEntity WHERE PNPDeviceID='" + pnp_device_id + "'")
    if devices:
        device = devices[0]
        # 获取设备对应的Win32_PnPSignedDriver对象
        drivers = wmi.ExecQuery("SELECT * FROM Win32_PnPSignedDriver WHERE DeviceID='" + pnp_device_id + "'")
        if drivers:
            driver = drivers[0]
            for prop in driver.Properties_:
                print(prop.Name, ":", prop.Value)
            #print("设备名称：", device.Name)
            #print("驱动文件路径：", driver.InfName)