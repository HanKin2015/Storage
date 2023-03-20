import wmi

# 创建WMI对象
wmi_obj = wmi.WMI()

# 查询设备状态
for device in wmi_obj.Win32_PnPEntity():
    #print(device.Name)
    if device.Name and 'USB\VID' in device.DeviceID:
        print(device.Name, device.DeviceID)
        if device.ConfigManagerErrorCode != 0:
            print('设备未安装驱动, ErrorCode {}'.format(device.ConfigManagerErrorCode))
        else:
            print('设备已安装驱动')