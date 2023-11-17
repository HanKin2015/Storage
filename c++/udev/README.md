# usb设备编程

## 1、获取usb设备驱动名称
D:\Github\Storage\c++\udev\get_usb_driver_name.c

## 2、获取字符串描述符名称
D:\Github\Storage\c++\udev\get_string_descriptor_name.c

第二种方法根本没有办法获取usb设备加载的驱动名称，因为：
```
真正的驱动在这里：
[root@ubuntu0006:/sys/dev/char/189:257] #cat 3-1\:1.0/uevent
DEVTYPE=usb_interface
DRIVER=hub
PRODUCT=409/55aa/101
TYPE=9/0/0
INTERFACE=9/0/0
MODALIAS=usb:v0409p55AAd0101dc09dsc00dp00ic09isc00ip00in00

而这里只是一个usb驱动：
[root@ubuntu0006:/sys/dev/char/189:257] #cat uevent
MAJOR=189
MINOR=257
DEVNAME=bus/usb/003/002
DEVTYPE=usb_device
DRIVER=usb
PRODUCT=409/55aa/101
TYPE=9/0/0
BUSNUM=003
DEVNUM=002

而遇到复杂的设备如摄像头，还需要麻烦匹配路径：
root@hankin:/sys/devices/pci0000:00/0000:00:10.0/usb3/3-1# cat 3-1.2/3-1.2\:1.0/uevent
DEVTYPE=usb_interface
DRIVER=snd-usb-audio
PRODUCT=d8c/103/10
TYPE=0/0/0
INTERFACE=1/1/0
MODALIAS=usb:v0D8Cp0103d0010dc00dsc00dp00ic01isc01ip00in00
root@hankin:/sys/devices/pci0000:00/0000:00:10.0/usb3/3-1# cat 3-1.2/3-1.2\:1.1/uevent
DEVTYPE=usb_interface
DRIVER=snd-usb-audio
PRODUCT=d8c/103/10
TYPE=0/0/0
INTERFACE=1/2/0
MODALIAS=usb:v0D8Cp0103d0010dc00dsc00dp00ic01isc02ip00in01
```


