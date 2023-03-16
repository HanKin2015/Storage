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

print(dev)


# set the active configuration. With no arguments, the first
# configuration will be the active one
#dev.set_configuration()

# get an endpoint instance
cfg = usb.util.find_descriptor(dev, bDescriptorType=2)
intf = cfg[(0,0)]

ep = usb.util.find_descriptor(
    intf,
    # match the first OUT endpoint
    custom_match = \
    lambda e: \
        usb.util.endpoint_direction(e.bEndpointAddress) == \
        usb.util.ENDPOINT_OUT)

assert ep is not None

print(intf)
print('*' * 50)
print(ep)
print('*' * 50)

from usb.control import get_descriptor
buf = get_descriptor(
            dev,
            254,
            usb.util.DESC_TYPE_STRING,
            0
        )
print(buf)

# write the data
#ep.write('test')