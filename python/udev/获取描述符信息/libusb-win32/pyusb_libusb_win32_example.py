import usb.core
import usb.util
import sys

# Find the first USB device
dev = usb.core.find()
if dev == None:
    print('there is not a usb device')
    sys.exit()

# Get the device configuration
cfg = usb.util.find_descriptor(dev, bConfigurationValue=1)

# Get the device descriptor
desc = cfg.extra

# Print the descriptor information
print(desc)




import usb.core

# Find the first USB device
dev = usb.core.find()

# Get the device descriptor
desc = dev.get_active_configuration().extra

# Print the descriptor information
print(desc)