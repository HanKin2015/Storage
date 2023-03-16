import usb.core
from usb.backend import libusb1

backend = usb.backend.libusb1.get_backend(find_library=lambda x: r"C:\ProgramData\Anaconda3\Lib\site-packages\libusb\_platform\_windows\x64\libusb-1.0.dll")
usb_devices = usb.core.find(backend=backend, find_all=True)
print(len(list(usb_devices)))

# it should find libusb-1.0.dll at our path variable
back = libusb1.get_backend()
print(type(back))  # return: <class 'usb.backend.libusb1._LibUSB'>

dev = usb.core.find(backend=back)
print(type(dev))  # return: <class 'usb.core.Device'>

# flag 'find_all=True' would return generator
# reprecent connected usb devices

dev_list = usb.core.find(find_all=True, backend=back)
print(sum(1 for _ in dev_list))
print(type(dev_list)) # return: <class 'generator'>
print(dev_list)