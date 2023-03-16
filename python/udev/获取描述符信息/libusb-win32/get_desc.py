import usb.core
import usb.util
import usb.backend.libusb1

import ctypes
libusb0 = ctypes.WinDLL(r"C:\ProgramData\Anaconda3\Lib\site-packages\libusb\_platform\_windows\x64\libusb-1.0.dll")
backend = usb.backend.libusb1.get_backend(find_library=lambda x: "libusb-1.0.dll")

# 获取USB设备
dev = usb.core.find(idVendor=0x090c, idProduct=0x2000)

# 获取设备描述符
dev_desc = usb.util.get_device_descriptor(dev)

# 遍历设备描述符以查找配置
for cfg in dev_desc.configurations:
    # 设置默认配置
    try:
        usb.util.get_string(dev, cfg.iConfiguration)
        dev.set_configuration(cfg)
        break
    except usb.core.USBError as e:
        pass

# get an endpoint instance
cfg = dev.get_active_configuration()
interface_number = cfg[(0,0)].bInterfaceNumber
alternate_setting = usb.control.get_interface(dev, interface_number)
intf = usb.util.find_descriptor(
    cfg, bInterfaceNumber=interface_number,
    bAlternateSetting=alternate_setting
)
ep_in = usb.util.find_descriptor(
    intf,
    # match the first IN endpoint
    custom_match=lambda e: \
        usb.util.endpoint_direction(e.bEndpointAddress) == \
        usb.util.ENDPOINT_IN
)
ep_out = usb.util.find_descriptor(
    intf,
    # match the first OUT endpoint
    custom_match=lambda e: \
        usb.util.endpoint_direction(e.bEndpointAddress) == \
        usb.util.ENDPOINT_OUT
)
# write data to USB device
data = b'\x01\x02\x03\x04'
ep_out.write(data)
# read data from USB device
data = ep_in.read(ep_in.wMaxPacketSize)