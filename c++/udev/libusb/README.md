# 理解libusb库

## 1、实现通过下发控制包获取配置描述符信息
libusb库中有libusb_get_config_descriptor函数，调用get_config_descriptor函数，然后这个函数根据不同的系统使用对应的函数。
Linux主要看os/linux_usbfs.c文件，然后对应op_get_config_descriptor函数。行不通，里面已经获取完毕了。




