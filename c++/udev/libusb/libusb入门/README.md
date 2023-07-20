## 1、资料
D:\Github\Storage\c++\udev\remount_driver\redir_udev_mount_usbfs_driver.c
D:\Github\Storage\c++\udev\remount_driver\README.md
D:\Github\GitBook\gitbook\USBDevice\libusb.md

## 2、libusb及其应用
https://mp.weixin.qq.com/s/KrxiqmJu35ZcrAsnvaFgPQ

## 3、libusb_device和libusb_device_handle之间的转换
libusb_device转换成libusb_device_handle：
libusb_open(libusb_device, libusb_device_handle)

libusb_device_handle转换成libusb_device：
libusb_device = libusb_get_device(libusb_device_handle)








