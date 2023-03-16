import usb.core
import usb.util
import usb.backend.libusb1
import usb.control

# 加载libusb-1.0.dll库
# pip install libusb
import ctypes
#libusb0 = ctypes.WinDLL(r"C:\ProgramData\Anaconda3\Lib\site-packages\libusb\_platform\_windows\x64\libusb-1.0.dll")
ctypes.WinDLL(r'C:\ProgramData\Anaconda3\Lib\site-packages\usb1\libusb-1.0.dll')
#backend = usb.backend.libusb1.get_backend(find_library=lambda x: "libusb-1.0.dll")
backend = usb.backend.libusb1.get_backend(find_library=lambda x: r'C:\ProgramData\Anaconda3\Lib\site-packages\usb1\libusb-1.0.dll')

# 获取USB设备
dev = usb.core.find(backend=backend, idVendor=0x090c, idProduct=0x2000)
if dev is None:
    raise ValueError('Device not found')

# 获取设备描述符
print(dev.bLength, usb.util.DESC_TYPE_DEVICE)
desc_size = dev.bLength
desc_type = usb.util.DESC_TYPE_DEVICE
desc_index = 0
desc = usb.control.get_descriptor(dev, desc_size, desc_type, desc_index)
# 将设备描述符转换为字符串格式
desc_str = usb.util._get_full_descriptor_str(desc)
print(desc_str)

# 获取接口描述符
desc_size = 9
desc_type = usb.util.DESC_TYPE_INTERFACE
desc_index = 0
interface_desc = usb.control.get_descriptor(dev, desc_size, desc_type, desc_index)
print(interface_desc)

# 获取端点描述符
desc_size = 7
desc_type = usb.util.DESC_TYPE_ENDPOINT
desc_index = 0
endpoint_desc = usb.control.get_descriptor(dev, desc_size, desc_type, desc_index, wIndex=0x81)
print(endpoint_desc)