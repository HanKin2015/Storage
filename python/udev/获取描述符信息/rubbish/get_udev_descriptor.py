import usb.core
import usb.util
import usb.backend.libusb1
import usb.control
import time

# 加载libusb-1.0.dll库
# pip install libusb
import ctypes
libusb1 = ctypes.WinDLL(r"C:\ProgramData\Anaconda3\Lib\site-packages\libusb\_platform\_windows\x64\libusb-1.0.dll")
backend = usb.backend.libusb1.get_backend(find_library=lambda x: "libusb-1.0.dll")

# 获取USB设备
dev = usb.core.find(idVendor=0x0ac8, idProduct=0x3500)
if dev is None:
    raise ValueError('Device not found')

# 获取完整的描述符信息
#print(dev)

def get_descroptor_by_find_descriptor():
    """
    """
    
    # 获取设备描述符
    print(dev.bLength, usb.util.DESC_TYPE_DEVICE)
    desc_size = dev.bLength
    desc_type = usb.util.DESC_TYPE_DEVICE
    desc_index = 0
    #device_desc = usb.util.find_descriptor(dev, bDescriptorType=usb.util.DESC_TYPE_DEVICE)
    device_desc = dev._get_full_descriptor_str() 
    #print(device_desc)

    # 获取配置描述符
    desc_size = 0
    desc_type = usb.util.DESC_TYPE_CONFIG
    desc_index = 0
    cfg_desc = usb.util.find_descriptor(dev, bDescriptorType=desc_type)
    #print(cfg_desc)

    # 获取输入端口描述符
    intf = cfg_desc[(0,0)]
    ep = usb.util.find_descriptor(
        intf,
        # match the first OUT endpoint
        custom_match = \
        lambda e: \
            usb.util.endpoint_direction(e.bEndpointAddress) == \
            usb.util.ENDPOINT_IN)

    assert ep is not None

    print(intf)
    print('*' * 50)
    print(ep)
    print('*' * 50)

def get_descroptor_by_find_busses():
    """
    """
    
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

def get_descroptor_by():
    """
    """
    
    cfg = usb.util.find_descriptor(dev, bConfigurationValue=1)
    print(cfg)
    
def main():
    """主函数
    """
    
    #get_descroptor_by_find_descriptor()
    #get_descroptor_by_find_busses()
    get_descroptor_by()

if __name__ == '__main__':
    """程序入口
    """
    
    #os.system('chcp 936 & cls')
    print('******** starting ********')
    start_time = time.time()

    main()

    end_time = time.time()
    print('process spend {} s.\n'.format(round(end_time - start_time, 3)))