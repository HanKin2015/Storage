import win32com.client
# 创建WMI服务对象
wmi = win32com.client.GetObject("winmgmts:")
# 枚举Win32_USBControllerDevice类中的所有设备
usb_controllers = wmi.ExecQuery("SELECT * FROM Win32_USBControllerDevice")
# 遍历所有设备，获取其PNPDeviceID
for usb_controller in usb_controllers:
    pnp_device_id = usb_controller.Dependent.split("=")[1].replace('"', '')
    # 获取设备对应的Win32_SystemDriver对象
    system_drivers = wmi.ExecQuery("SELECT * FROM Win32_SystemDriver")
    for system_driver in system_drivers:
        if system_driver.PnpDeviceID == pnp_device_id:
            system_driver = system_driver[0]
            print("设备名称：", system_driver.Name)
            print("驱动文件路径：", system_driver.PathName)