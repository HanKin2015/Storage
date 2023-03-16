import usb.core
import usb.util
import usb.backend.libusb1

backend = usb.backend.libusb1.get_backend(find_library=lambda x: r"C:\ProgramData\Anaconda3\Lib\site-packages\libusb\_platform\_windows\x64\libusb-1.0.dll")

# Find your USB device
dev = usb.core.find(idVendor=0x090c, idProduct=0x2000)

# Get the active configuration
cfg = dev.get_active_configuration()

# Get the first interface
intf = cfg[(0,0)]

# Get the endpoint
ep = usb.util.find_descriptor(
    intf,
    custom_match=lambda e: \
        usb.util.endpoint_direction(e.bEndpointAddress) == \
        usb.util.ENDPOINT_OUT)

# Send data to the endpoint
data = b"Hello, USB!"
ep.write(data)