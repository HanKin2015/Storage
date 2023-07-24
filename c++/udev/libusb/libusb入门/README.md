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

## 4、卡住还原驱动失败
libusb_claim_interface声明一个接口后记得释放。
libusb_release_interface

## 5、libusb_set_auto_detach_kernel_driver和libusb_detach_kernel_driver的区别
libusb_set_auto_detach_kernel_driver函数是在libusb 1.0.16版本中引入的，因此只有在该版本或更高版本的libusb中才可用。
libusb_detach_kernel_driver函数是在libusb 0.1.8版本中引入的，因此只有在该版本或更高版本的libusb中才可用。

libusb_set_auto_detach_kernel_driver函数：
```
static int op_claim_interface(struct libusb_device_handle *handle, int iface)
{
    if (handle->auto_detach_kernel_driver)
        return detach_kernel_driver_and_claim(handle, iface);
    else
        return claim_interface(handle, iface);
}

static int op_release_interface(struct libusb_device_handle *handle, int iface)
{
    int r;

    r = release_interface(handle, iface);
    if (r)
        return r;

    if (handle->auto_detach_kernel_driver)
        op_attach_kernel_driver(handle, iface);

    return 0;
}

static int detach_kernel_driver_and_claim(struct libusb_device_handle *handle,
    int interface)
{
    struct usbfs_disconnect_claim dc;
    int r, fd = _device_handle_priv(handle)->fd;

    ......

    r = op_detach_kernel_driver(handle, interface);
    if (r != 0 && r != LIBUSB_ERROR_NOT_FOUND)
        return r;

    return claim_interface(handle, interface);
}

```
