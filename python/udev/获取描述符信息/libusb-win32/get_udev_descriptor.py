import usb.core
import usb.util
import usb.backend.libusb1

backend = usb.backend.libusb1.get_backend(find_library=lambda x: r"C:\ProgramData\Anaconda3\Lib\site-packages\libusb\_platform\_windows\x64\libusb-1.0.dll")
usb_devices = usb.core.find(backend=backend, find_all=True)

def enumerate_usb():  # I use a simple function that scans all known USB connections and saves their info in the file
    with open("EnumerateUSBLog.txt", "w") as wf:
        for i, d in enumerate(usb_devices):
            # Get the device configuration
            cfg = usb.util.find_descriptor(d, bConfigurationValue=1)
            
            print(cfg)

            # Access the 'bConfigurationValue' attribute of the Configuration object
            config_value = cfg.bConfigurationValue
            print(config_value)

            # Get the device descriptor   在某些情况下，extra 属性可能不存在，因此运行上面的代码可能会导致 AttributeError。要解决这个问题，你可以尝试使用其他属性或方法来获取你需要的信息。
            desc = cfg.extra

            # Print the descriptor information
            print(desc)
            
            # get_active_configuration这个函数是不支持的
            if d.get_active_configuration() is None:
                # Configure the device if it is not already configured
                d.set_configuration()
            try:
                wf.write(f"USB Device number {i}:\n")
                wf.write(d._get_full_descriptor_str() + "\n")
                wf.write(d.get_active_configuration() + "\n")
                wf.write("\n")
            except NotImplementedError:
                wf.write(f"Device number {i} is busy.\n\n")
            except usb.core.USBError:
                wf.write(f"Device number {i} is either disconnected or not found.\n\n")

enumerate_usb()