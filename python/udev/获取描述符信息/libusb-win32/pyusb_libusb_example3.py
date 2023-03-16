import usb.core
import usb.util
import usb.backend.libusb1

from infi.devicemanager import DeviceManager

dm = DeviceManager()
devices = dm.all_devices
for d in devices:
    try:
        print(f'{d.friendly_name} : address: {d.address}, bus: {d.bus_number}, location: {d.location}')
    except Exception:
        pass


backend = usb.backend.libusb1.get_backend(find_library=lambda x: "libusb-1.0.dll")
usb_devices = usb.core.find(backend=backend, find_all=True)


def enumerate_usb():  # I use a simple function that scans all known USB connections and saves their info in the file
    with open("EnumerateUSBLog.txt", "w") as wf:
        for i, d in enumerate(usb_devices):
            try:
                wf.write(f"USB Device number {i}:\n")
                wf.write(d._get_full_descriptor_str() + "\n")
                wf.write(d.get_active_configuration() + "\n")
                wf.write("\n")
            except NotImplementedError:
                wf.write(f"Device number {i} is busy.\n\n")
            except usb.core.USBError:
                wf.write(f"Device number {i} is either disconnected or not found.\n\n")