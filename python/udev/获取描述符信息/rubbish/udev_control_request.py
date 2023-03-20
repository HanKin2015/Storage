import usb.core
import usb.util
import usb.backend.libusb1
import usb.control
import time

# 加载libusb-1.0.dll库
# pip install libusb
import ctypes
libusb1 = ctypes.WinDLL(r"C:\ProgramData\Anaconda3\Lib\site-packages\libusb\_platform\_windows\x64\libusb-1.0.dll")
backend = usb.backend.libusb1.get_backend(find_library=lambda x: "libusb-1.0.dll")

# 获取USB设备
#dev = usb.core.find(idVendor=0x0ac8, idProduct=0x3500)
dev = usb.core.find(idVendor=0x090c, idProduct=0x2000)
if dev is None:
    raise ValueError('Device not found')

# 设置设备配置
#dev.set_configuration()

# 发送控制请求
bmRequestType = usb.util.build_request_type(
    direction=usb.util.CTRL_OUT,
    type=usb.util.CTRL_TYPE_VENDOR,
    recipient=usb.util.CTRL_RECIPIENT_DEVICE
)
bRequest = 0x01
wValue = 0x0001
wIndex = 0x0001
data = b'\x00\x01\x02\x03\x04\x05\x06\x07'

ret = dev.ctrl_transfer(bmRequestType, bRequest, wValue, wIndex, data)

# 打印返回值
print(ret)