import win32file

# 获取USB设备的设备路径
#device_path = '\\\\.\\USBSTOR\\Disk&Ven_SanDisk&Prod_Cruzer_Glide&Rev_1.00\\4C530001090819101162&0'
device_path = '\\\\?\\usb#vid_090c&pid_2000#ccyymmddipzfh52f#{a5dcbf10-6530-11d2-901f-00c04fb951ed}'
#device_path = 'USBSTOR\DISK&VEN_AIGO&PROD_U330&REV_1100\CCYYMMDDIPZFH52F&0'
#device_path = '\\\\.\\USB\VID_090C&PID_2000\CCYYMMDDIPZFH52F'

# 打开设备
handle = win32file.CreateFile(device_path, win32file.GENERIC_READ, win32file.FILE_SHARE_READ, None, win32file.OPEN_EXISTING, 0, None)

# 读取设备数据
data = win32file.ReadFile(handle, 1024)

# 关闭设备
win32file.CloseHandle(handle)