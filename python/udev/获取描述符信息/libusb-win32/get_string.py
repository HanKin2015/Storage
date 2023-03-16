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

# read data from USB device
data = dev.ctrl_transfer(
    usb.util.ENDPOINT_IN,
    usb.core.REQ_GET_DESCRIPTOR,
    (usb.util.DESC_TYPE_OTHER << 8) | 0,
    0,
    ep_in.wMaxPacketSize
)

# 获取设备描述符
dev_desc = dev.get_device_descriptor()

# 获取设备的所有配置描述符
cfgs = dev.get_configurations()
# 设置缺省配置
dev.set_configuration(cfgs[0])
    
# 获取配置描述符
cfg = dev.get_active_configuration()
# 获取接口
intf = cfg[(0,0)]  # 替换(0,0)为你需要的接口索引
# 配置接口
usb.util.claim_interface(dev, intf)
    
# 获取设备字符串描述符
print(help(usb.util.get_string))
str_desc = usb.util.get_string(dev, dev.iManufacturer)  # 替换dev.iManufacturer为你需要的字符串描述符索引