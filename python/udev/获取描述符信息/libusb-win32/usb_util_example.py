import usb.core
import usb.util
import usb.backend.libusb1
import usb.control

# 加载libusb-1.0.dll库
# pip install libusb
import ctypes
libusb0 = ctypes.WinDLL(r"C:\ProgramData\Anaconda3\Lib\site-packages\libusb\_platform\_windows\x64\libusb-1.0.dll")
backend = usb.backend.libusb1.get_backend(find_library=lambda x: "libusb-1.0.dll")

# 获取USB设备
dev = usb.core.find(idVendor=0x090c, idProduct=0x2000)
if dev is None:
    raise ValueError('Device not found')

# 获取设备描述符
print(dev.bLength, usb.util.DESC_TYPE_DEVICE)
desc_size = dev.bLength
desc_type = usb.util.DESC_TYPE_DEVICE
desc_index = 0
#device_desc = usb.util.find_descriptor(dev, bDescriptorType=usb.util.DESC_TYPE_DEVICE)
device_desc = dev._get_full_descriptor_str() 
print(device_desc)

# 获取配置描述符
desc_size = 0
desc_type = usb.util.DESC_TYPE_CONFIG
desc_index = 0
cfg_desc = usb.util.find_descriptor(dev, bDescriptorType=desc_type)
print(cfg_desc)

interface_number = cfg_desc[(0,0)].bInterfaceNumber
alternate_setting = usb.control.get_interface(dev, interface_number)
intf = usb.util.find_descriptor(
    cfg_desc, bInterfaceNumber=interface_number,
    bAlternateSetting=alternate_setting
)

# 获取接口描述符
desc_size = 9
desc_type = usb.util.DESC_TYPE_INTERFACE
desc_index = 0
interface_desc = usb.util.find_descriptor(dev, bDescriptorType=desc_type)
print(interface_desc)

# 获取端点描述符
desc_size = 7
desc_type = usb.util.DESC_TYPE_ENDPOINT
desc_index = 0
endpoint_desc = usb.util.find_descriptor(dev, bDescriptorType=desc_type)
print(endpoint_desc)