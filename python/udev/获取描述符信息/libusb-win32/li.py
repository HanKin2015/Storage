import usb.core
import usb.util
import usb.backend.libusb1
import ctypes
libusb0 = ctypes.WinDLL(r"C:\ProgramData\Anaconda3\Lib\site-packages\libusb\_platform\_windows\x64\libusb-1.0.dll")

# find USB device
backend = usb.backend.libusb1.get_backend(find_library=lambda x: "libusb-1.0.dll")
dev = usb.core.find(idVendor=0x090c, idProduct=0x2000)
if dev is None:
    raise ValueError('Device not found')
# set the active configuration. With no arguments, the first
# configuration will be the active one
dev.set_configuration()
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