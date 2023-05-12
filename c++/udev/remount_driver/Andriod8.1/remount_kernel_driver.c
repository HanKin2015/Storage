/**
* 文 件 名: remount_kernel_driver.c
* 文件描述: 卸载和加载内核驱动
* 备    注: 此为安卓编译版本，尝试卸载usbhid驱动
* 作    者: HanKin
* 创建日期: 2023.05.06
* 修改日期：2023.05.06
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/usbdevice_fs.h>
#include <sys/ioctl.h>
#include <libusb/libusb.h>

// ZFM-889触摸屏
#define USB_VENDOR_ID  0xaaec
#define USB_PRODUCT_ID 0xc021

/**
* @brief  卸载内核驱动
* @note   使用ioctl函数，宏定义在linux-5.15.4/include/uapi/linux/usbdevice_fs.h
* @param  fd [in] USB设备文件描述符
* @param  interface [in] 设备接口
* @return LIBUSB_SUCCESS 0
*         LIBUSB_ERROR_INVALID_PARAM -2
*         LIBUSB_ERROR_NO_DEVICE -4
*         LIBUSB_ERROR_NOT_FOUND -5
*         LIBUSB_ERROR_BUSY -6
*         LIBUSB_ERROR_OTHER -99
*         更多参考libusb-1.0.24/libusb/libusb.h
*/
static int op_attach_kernel_driver(int fd, int interface)
{
    struct usbdevfs_ioctl command;
    int r;
    
    command.ifno = interface;
    command.ioctl_code = USBDEVFS_CONNECT;
    command.data = NULL;
    
    r = ioctl(fd, USBDEVFS_IOCTL, &command);
    if (r < 0) {
        if (errno == ENODATA)
            return LIBUSB_ERROR_NOT_FOUND;
        else if (errno == EINVAL)
            return LIBUSB_ERROR_INVALID_PARAM;
        else if (errno == ENODEV)
            return LIBUSB_ERROR_NO_DEVICE;
        else if (errno == EBUSY)
            return LIBUSB_ERROR_BUSY;
    
        printf("attach failed error %d errno %d", r, errno);
        return LIBUSB_ERROR_OTHER;
    } else if (r == 0) {
        return LIBUSB_ERROR_NOT_FOUND;
    }
    printf("attach success\n");
    return LIBUSB_SUCCESS;
}

/**
* @brief  加载内核驱动
* @note   使用ioctl函数，宏定义在linux-5.15.4/include/uapi/linux/usbdevice_fs.h
* @param  fd [in] USB设备文件描述符
* @param  interface [in] 设备接口
* @return LIBUSB_SUCCESS 0
*         LIBUSB_ERROR_INVALID_PARAM -2
*         LIBUSB_ERROR_NO_DEVICE -4
*         LIBUSB_ERROR_NOT_FOUND -5
*         LIBUSB_ERROR_BUSY -6
*         LIBUSB_ERROR_OTHER -99
*         更多参考libusb-1.0.24/libusb/libusb.h
*/
static int op_detach_kernel_driver(int fd, int interface)
{
    struct usbdevfs_ioctl command;
    struct usbdevfs_getdriver getdrv;
    int r;

    command.ifno = interface;
    command.ioctl_code = USBDEVFS_DISCONNECT;
    command.data = NULL;

    getdrv.interface = interface;
    r = ioctl(fd, USBDEVFS_GETDRIVER, &getdrv);
    if (r == 0 && strcmp(getdrv.driver, "usbfs") == 0)
        return LIBUSB_ERROR_NOT_FOUND;

    r = ioctl(fd, USBDEVFS_IOCTL, &command);
    if (r) {
        if (errno == ENODATA)
            return LIBUSB_ERROR_NOT_FOUND;
        else if (errno == EINVAL)
            return LIBUSB_ERROR_INVALID_PARAM;
        else if (errno == ENODEV)
            return LIBUSB_ERROR_NO_DEVICE;

        printf("detach failed error %d errno %d", r, errno);
        return LIBUSB_ERROR_OTHER;
    }

    printf("detach success\n");
    return LIBUSB_SUCCESS;
}

/**
* @brief  请求接口访问权限
* @note   使用ioctl函数，宏定义在linux-5.15.4/include/uapi/linux/usbdevice_fs.h
* @param  fd [in] USB设备文件描述符
* @param  interface [in] 设备接口
* @return LIBUSB_SUCCESS 0
*         LIBUSB_ERROR_INVALID_PARAM -2
*         LIBUSB_ERROR_NO_DEVICE -4
*         LIBUSB_ERROR_NOT_FOUND -5
*         LIBUSB_ERROR_BUSY -6
*         LIBUSB_ERROR_OTHER -99
*         更多参考libusb-1.0.24/libusb/libusb.h
*/
static int claim_interface(int fd, int iface)
{
    int r = ioctl(fd, USBDEVFS_CLAIMINTERFACE, &iface);
    if (r) {
        printf("claim_interface failed\n");
        if (errno == ENOENT)
            return LIBUSB_ERROR_NOT_FOUND;
        else if (errno == EBUSY)
            return LIBUSB_ERROR_BUSY;
        else if (errno == ENODEV)
            return LIBUSB_ERROR_NO_DEVICE;

        printf("claim interface failed, error %d errno %d", r, errno);
        return LIBUSB_ERROR_OTHER;
    }
    printf("claim_interface success\n");
    return LIBUSB_SUCCESS;
}

/**
* @brief  卸载操作系统自动加载的驱动程序以及请求接口访问权限
* @note   使用ioctl函数，宏定义在linux-5.15.4/include/uapi/linux/usbdevice_fs.h
* @param  fd [in] USB设备文件描述符
* @param  interface [in] 设备接口
* @return LIBUSB_SUCCESS 0
*         LIBUSB_ERROR_INVALID_PARAM -2
*         LIBUSB_ERROR_NO_DEVICE -4
*         LIBUSB_ERROR_NOT_FOUND -5
*         LIBUSB_ERROR_BUSY -6
*         LIBUSB_ERROR_OTHER -99
*         更多参考libusb-1.0.24/libusb/libusb.h
*/
static int detach_kernel_driver_and_claim(int fd, int interface)
{
    struct usbdevfs_disconnect_claim dc;
    int r;

    dc.interface = interface;
    strcpy(dc.driver, "usbfs");
    dc.flags = USBDEVFS_DISCONNECT_CLAIM_EXCEPT_DRIVER;
    r = ioctl(fd, USBDEVFS_DISCONNECT_CLAIM, &dc);
    if (r == 0 || (r != 0 && errno != ENOTTY)) {
        if (r == 0) {
            printf("detach_kernel_driver_and_claim failed r0\n");
            return 0;
        }
        
        printf("detach_kernel_driver_and_claim failed, errno %d\n", errno);
        switch (errno) {
        case EBUSY:
            return LIBUSB_ERROR_BUSY;
        case EINVAL:
            return LIBUSB_ERROR_INVALID_PARAM;
        case ENODEV:
            return LIBUSB_ERROR_NO_DEVICE;
        }
        printf("disconnect-and-claim failed errno %d", errno);
        return LIBUSB_ERROR_OTHER;
    }

    /* Fallback code for kernels which don't support the
       disconnect-and-claim ioctl */
    r = op_detach_kernel_driver(fd, interface);
    if (r != 0 && r != LIBUSB_ERROR_NOT_FOUND) {
        printf("op_detach_kernel_driver failed\n");
        return r;
    }

    printf("detach_kernel_driver_and_claim success\n");
    return claim_interface(fd, interface);
}

int main()
{
    libusb_device **devs;
    libusb_device_handle *handle;
    int result, i, fd;
    libusb_device_handle *device = NULL;

    // 初始化libusb库
    result = libusb_init(NULL);
    if (result < 0) {
        fprintf(stderr, "libusb_init error: %s\n", libusb_error_name(result));
        exit(1);
    }

    // 获取连接到系统上的所有USB设备
    result = libusb_get_device_list(NULL, &devs);
    if (result < 0) {
        fprintf(stderr, "libusb_get_device_list error: %s\n", libusb_error_name(result));
        exit(1);
    }

    // 遍历USB设备列表，查找指定的设备
    for (i = 0; devs[i] != NULL; i++) {
        struct libusb_device_descriptor desc;
        result = libusb_get_device_descriptor(devs[i], &desc);
        if (result < 0) {
            fprintf(stderr, "libusb_get_device_descriptor error: %s\n", libusb_error_name(result));
            continue;
        }

        unsigned short vid = desc.idVendor;
        unsigned short pid = desc.idProduct;

        printf("Found USB device with VID=0x%04x, PID=0x%04x\n", vid, pid);
        
        if (desc.idVendor == USB_VENDOR_ID && desc.idProduct == USB_PRODUCT_ID) {
            // 找到了指定的设备
            result = libusb_open(devs[i], &handle);
            if (result < 0) {
                fprintf(stderr, "libusb_open error: %s\n", libusb_error_name(result));
                continue;
            }

            // 在这里可以使用handle来访问设备
            printf("Found USB device with VID=0x%04x, PID=0x%04x\n", desc.idVendor, desc.idProduct);

            // 打开USB设备
            unsigned short vid = desc.idVendor;
            unsigned short pid = desc.idProduct;
            device = libusb_open_device_with_vid_pid(NULL, vid, pid);
            if (device == NULL) {
                fprintf(stderr, "libusb_open_device_with_vid_pid error: %s\n", libusb_error_name(result));
                continue;
            }

            // 获取USB设备文件描述符
            int bus_number = libusb_get_bus_number(devs[i]);
            int device_address = libusb_get_device_address(devs[i]);
            char path[64];
            snprintf(path, sizeof(path), "/dev/bus/usb/%03d/%03d", bus_number, device_address);
            fd = open(path, O_RDWR);
            if (fd < 0) {
                fprintf(stderr, "open error: %m\n");
                libusb_close(handle);
                continue;
            }
            
            
            op_attach_kernel_driver(fd, 0);
            op_attach_kernel_driver(fd, 1);
            
            //op_detach_kernel_driver(fd, 0);
            //op_detach_kernel_driver(fd, 1);
            
            //detach_kernel_driver_and_claim(fd, 0);
            //detach_kernel_driver_and_claim(fd, 1);
            claim_interface(fd, 0);
            claim_interface(fd, 1);

            libusb_close(handle);
            break;
        }
    }
    
    // 释放资源
    libusb_free_device_list(devs, 1);
    libusb_exit(NULL);
    return 0;
}