import usb.core
import usb.backend.libusb1

# 设置使用libusb后端
backend = usb.backend.libusb1.get_backend(find_library=lambda x: r"C:\ProgramData\Anaconda3\Lib\site-packages\libusb\_platform\_windows\x64\libusb-1.0.dll")

# 设置libusb-win32后端
#backend = usb.backend.libusb1.get_backend(find_library=lambda x: r"C:\Windows\SysWOW64\libusb0.dll")

# 获取USB设备
dev = usb.core.find(idVendor=0x090c, idProduct=0x2000, backend=backend)
print(dev)

# 释放资源
usb.util.dispose_resources(dev)