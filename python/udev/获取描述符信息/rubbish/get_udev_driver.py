import win32com.client
# 创建WMI服务对象
wmi = win32com.client.GetObject("winmgmts:")
# 枚举Win32_PnPEntity类中的所有设备
#pnp_entities = wmi.ExecQuery("SELECT * FROM Win32_PnPEntity WHERE DeviceID LIKE 'USB*'")
pnp_entities = wmi.ExecQuery("SELECT * FROM Win32_PnPEntity")
print(len(pnp_entities))
# 遍历所有设备，获取设备驱动信息
for pnp_entity in pnp_entities:
    if pnp_entity.Name and '大容量' in pnp_entity.Name:
        print("设备名称：", pnp_entity.Name)
        # 获取PNP ID
        pnp_id = pnp_entity.PNPDeviceID
        # 获取硬件ID
        hardware_ids = pnp_entity.HardwareID
        print(hardware_ids)
        if hardware_ids:
            # 获取设备驱动信息
            #drivers = wmi.ExecQuery("SELECT * FROM Win32_PnPSignedDriver WHERE HardwareID='" + hardware_ids[0] + "'")
            drivers = wmi.ExecQuery("SELECT * FROM Win32_PnPSignedDriver")
            print(len(drivers))
            for driver in drivers:
                if driver.HardwareID in hardware_ids:
                    print(driver.HardwareID)
                    for prop in driver.Properties_:
                        print(prop.Name, ":", prop.Value)
                    #print(driver)
                    #print("驱动名称：", driver.DriverName)
                    #print("驱动文件路径：", driver.PathName)
                    #print(driver.InfName)
                    #print(driver.HardwareID)
        else:
            print("设备未能获取到硬件ID")

print('='*50)

# 创建WMI服务对象
wmi = win32com.client.GetObject("winmgmts:")
# 枚举Win32_SystemDriver类中的所有设备驱动程序
system_drivers = wmi.ExecQuery("SELECT * FROM Win32_SystemDriver")
# 遍历所有设备驱动程序，获取驱动文件路径
for system_driver in system_drivers:
    if 'USBSTOR' in system_driver.Name:
        for prop in system_driver.Properties_:
            print(prop.Name, ":", prop.Value)
        #print("设备名称：", system_driver.Name)
        #print("驱动文件路径：", system_driver.PathName)
    