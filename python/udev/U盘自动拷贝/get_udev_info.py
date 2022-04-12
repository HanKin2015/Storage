import os
import platform
import usb
from usb.core import USBError
import time
import usb.backend.libusb0
import usb.backend.libusb1

'''
上下文：
我必须检测usb硬盘驱动器何时插入或拔出，并对其执行一些操作。
例如，当一个磁盘被插入时，我要得到挂载点（ex:/media/usb0）和系统点（ex:/dev/sdb1）。我需要两条路径，我不想进行类似于（子进程：mount-l）的系统调用。

我尝试了几种方法：
-pyudev:仅获取添加的EVT_设备上的系统路径（如/dev/sdb1）
-Gio（gi.repository）：使用“mount added”（如/media/usb0）获取装载点，并在第二个事件“volume added”中获取系统点，但Gio add and remove event fail有问题，或者有可疑行为取决于我在其上尝试应用程序的计算机
-DBusGMainLoop（dbus.mainloop.glib）：可以工作，但取决于我尝试过的计算机（所有配置都相同）启动2个事件“DeviceAdded”，有时一个设备被更改，但有时磁盘被插入时不会更改。

你知道一种方法（可能是我暴露的3种方法中的一种，我做了一些不好的事情）来检测U盘何时被插入，调用一个方法，在这个方法中得到我需要的2条路径吗？

参考：https://github.com/dnmellen/pyusbalarm
'''

### Some auxiliary functions ###
def _clean_str(s):
    '''
    Filter string to allow only alphanumeric chars and spaces

    @param s: string
    @return: string
    '''

    return ''.join([c for c in s if c.isalnum() or c in {' '}])


def _get_dev_string_info(device):
    '''
    Human readable device's info

    @return: string
    '''

    try:
        str_info = _clean_str(usb.util.get_string(device, 256, 2))
        str_info += ' ' + _clean_str(usb.util.get_string(device, 256, 3))
        print(str_info)
        return str_info
    except USBError:
        return str_info


def get_usb_devices():
    '''
    Get USB devices

    @return: list of tuples (dev_idVendor, dev_idProduct, dev_name)
    '''
    
    backend = usb.backend.libusb0.get_backend(find_library=find_library)

    return [(device.idVendor, device.idProduct, _get_dev_string_info(device)) 
                for device in usb.core.find(find_all=True, backend=backend)
                    if device.idProduct > 2]

def find_library(libname):
    libname += '.dll'
    path = None
    osVersion = platform.machine()
    if osVersion.upper() == 'x86'.upper():
        libname = os.getcwd() + '\\libusb\\x86\\' + libname
    elif osVersion.upper() == 'amd64'.upper():
        libname = os.getcwd() + '\\libusb\\amd64\\' + libname
    elif osVersion.upper() == 'ia64'.upper():
        libname = os.getcwd() + '\\libusb\\ia64\\' + libname
    
    print('libname: ', libname)
    
    if os.path.exists(libname):
        print('find dll:', libname)
        path = libname
    
    return path

if __name__ == "__main__":
    find_library('libusb0')
    
    #backend = usb.backend.libusb0.get_backend(find_library=find_library)
    backend = usb.backend.libusb0.get_backend(find_library=lambda x: 'D:\\Github\\Storage\\python\\udev\\U盘自动拷贝\\libusb\\amd64\\libusb0.dll')
    print(backend)
    #print(usb.core.find(find_all=True, backend=backend))
    
    # 全局变量：C:\Windows\System32\libusb0.dll
    print(usb.core.find(find_all=True))
    while True:
        time.sleep(2)
        print(get_usb_devices())