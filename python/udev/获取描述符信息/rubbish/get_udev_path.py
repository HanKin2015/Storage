import win32api
import win32file

# 获取USB设备的厂商ID和产品ID
vendor_id = '090c'
product_id = '2000'

# 枚举所有USB设备
drives = win32api.GetLogicalDriveStrings()
print(len(drives))
print(drives)
for drive in drives.split('\000')[:-1]:
    drive_type = win32file.GetDriveType(drive)
    print(drive_type, win32file.DRIVE_REMOVABLE)
    if drive_type == win32file.DRIVE_REMOVABLE:
        print(drive)
        handle = win32file.CreateFile(drive, win32file.GENERIC_READ, win32file.FILE_SHARE_READ, None, win32file.OPEN_EXISTING, 0, None)
        try:
            device = win32file.DeviceIoControl(handle, 0x222900, None, 0x12)
            device_id = ''.join(['{:02X}'.format(b) for b in device[4:8]])
            if device_id == vendor_id + product_id:
                device_path = '\\\\.\\' + drive[0] + ':'
                print(device_path)
        except:
            pass
        win32file.CloseHandle(handle)