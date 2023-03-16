import usb.core
from usb.backend import libusb0, libusb1

# Find the first USB device
backend = usb.backend.libusb1.get_backend(find_library=lambda x: r'C:\Windows\System32\libusb0.dll')
#backend = usb.backend.libusb1.get_backend(find_library=lambda x: r'C:\Windows\SysWOW64\libusb0.dll')
backend = usb.backend.libusb1.get_backend(find_library=lambda x: r"C:\ProgramData\Anaconda3\Lib\site-packages\libusb\_platform\_windows\x64\libusb-1.0.dll")
devs = usb.core.find(backend=backend, find_all=True)
#print(sum(1 for _ in devs))

"""
with open("EnumerateUSBLog.txt", "w") as wf:
    for i, d in enumerate(devs):
        try:
            wf.write(f"USB Device number {i}:\n")
            wf.write(d._get_full_descriptor_str() + "\n")
            wf.write(d.get_active_configuration() + "\n")
            wf.write("\n")
        except NotImplementedError:
            wf.write(f"Device number {i} is busy.\n\n")
        except usb.core.USBError:
            wf.write(f"Device number {i} is either disconnected or not found.\n\n")
"""


with open("EnumerateUSBLog.txt", "w") as wf:
    for dev in devs:
        wf.write(dev._get_full_descriptor_str() + "\n")
        #wf.write(dev.get_active_configuration() + "\n")
        wf.write("\n")
        #print(dev.get_active_configuration().extra)

# Get the device descriptor
#desc = dev.get_active_configuration().extra

# Print the descriptor information
#print(desc)

gen = (i for i in range(10))
print(gen)
print(type(gen))
print(sum(1 for _ in gen))
print(len(list(gen)))
for each in gen:
    print(each)