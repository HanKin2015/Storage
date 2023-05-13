# 明白一个道理

获取libusb_device *udev只能通过libusb_get_device_list遍历比对vpid

获取libusb_device_handle *dev_handle只能通过libusb_open_device_with_vid_pid函数，先获取libusb_device然后再使用libusb_open函数获取

获取USB设备文件描述符fd只能通过open函数打开其节点，即在snprintf(path, sizeof(path), "/dev/bus/usb/%03d/%03d", bus_number, device_address);

更发现并为如此，也可以通过handle获取到libusb_device，函数:
```
/** \ingroup libusb_dev
 * Get the underlying device for a device handle. This function does not modify
 * the reference count of the returned device, so do not feel compelled to
 * unreference it when you are done.
 * \param dev_handle a device handle
 * \returns the underlying device
 */
DEFAULT_VISIBILITY
libusb_device * LIBUSB_CALL libusb_get_device(libusb_device_handle *dev_handle)
{
    return dev_handle->dev;
}
```


