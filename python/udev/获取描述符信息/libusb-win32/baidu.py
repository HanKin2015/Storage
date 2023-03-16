import usb.core
import usb.util
import usb.backend.libusb1
import usb.control

# 加载libusb-1.0.dll库
# pip install libusb
import ctypes
libusb0 = ctypes.WinDLL(r"C:\ProgramData\Anaconda3\Lib\site-packages\libusb\_platform\_windows\x64\libusb-1.0.dll")
backend = usb.backend.libusb1.get_backend(find_library=lambda x: "libusb-1.0.dll")

#help(usb.core) 
busses = usb.busses()
for bus in busses:
  devices = bus.devices
  for dev in devices:
    #_name = usb.util.get_string(dev.dev,256,0)  #This is where I'm having trouble
    #print("device name=",_name)
    print("Device:", dev.filename)
    print("  Device class:",dev.deviceClass)
    print("  Device sub class:",dev.deviceSubClass)
    print("  Device protocol:",dev.deviceProtocol)
    print("  Max packet size:",dev.maxPacketSize)
    print("  idVendor:",hex(dev.idVendor))
    print("  idProduct:",hex(dev.idProduct))
    print("  Device Version:",dev.deviceVersion)
    for config in dev.configurations:
      print("  Configuration:", config.value)
      print("    Total length:", config.totalLength )
      print("    selfPowered:", config.selfPowered)
      print("    remoteWakeup:", config.remoteWakeup)
      print("    maxPower:", config.maxPower)
      for intf in config.interfaces:
        print("    Interface:",intf[0].interfaceNumber)
        for alt in intf:
          print("    Alternate Setting:",alt.alternateSetting)
          print("      Interface class:",alt.interfaceClass)
          print("      Interface sub class:",alt.interfaceSubClass)
          print("      Interface protocol:",alt.interfaceProtocol)
          for ep in alt.endpoints:
            print("      Endpoint:",hex(ep.address))
            print("        Type:",ep.type)
            print("        Max packet size:",ep.maxPacketSize)
            print("        Interval:",ep.interval)