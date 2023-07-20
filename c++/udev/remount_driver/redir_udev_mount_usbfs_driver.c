/**
* 文 件 名: redir_udev_mount_usbfs_driver.c
* 文件描述: 加载usbfs驱动其实就是调用usbfs接口需要进行操作usb设备进行的一番操作
* 备    注: 此为xubuntu编译版本，以U盘为例，睡眠中使用另外一个窗口查看驱动情况
* 作    者: HanKin
* 创建日期: 2023.05.12
* 修改日期：2023.05.12
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
#include <libusb-1.0/libusb.h>

// 一款USB3.0协议的U盘
#define USB_VENDOR_ID  0x090c
#define USB_PRODUCT_ID 0x2000

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("need a argument, 0 detach 1 attach.\n");
        return -1;
    }
    
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
        
        if (desc.idVendor == USB_VENDOR_ID && desc.idProduct == USB_PRODUCT_ID) {
            // 找到了指定的设备
            result = libusb_open(devs[i], &handle);
            if (result < 0) {
                fprintf(stderr, "libusb_open error: %s\n", libusb_error_name(result));
                continue;
            }

            // 在这里可以使用handle来访问设备
            printf("Found USB device with VID=0x%04x, PID=0x%04x\n", desc.idVendor, desc.idProduct);

            if (strcmp(argv[1], "0") == 0) {
                // 卸载设备驱动
                result = libusb_detach_kernel_driver(handle, 0);
                if (result == LIBUSB_SUCCESS) {
                    printf("detach kernel_driver success\n");
                } else {
                    printf("detach kernel_driver failed\n");
                }
            } else if (strcmp(argv[1], "1") == 0) {
                // 加载设备驱动
                result = libusb_attach_kernel_driver(handle, 0);
                if (result == LIBUSB_SUCCESS) {
                    printf("attach kernel_driver success\n");
                } else {
                    printf("attach kernel_driver failed\n");
                }
            } else if (strcmp(argv[1], "2") == 0) {
                // USB设备重定向加载usbfs驱动
#if LIBUSBX_API_VERSION >= 0x01000102
                (void)libusb_set_auto_detach_kernel_driver(handle, 1);
#endif
#if LIBUSBX_API_VERSION < 0x01000102
                libusb_detach_kernel_driver(handle, 0);
#endif
                result = libusb_claim_interface(handle, 0);
                if (result == LIBUSB_SUCCESS) {
                    printf("libusb_claim_interface success\n");
                } else {
                    printf("libusb_claim_interface failed\n");
                }
                printf("waiting 20 seconds\n");
                sleep(10);
            } else if (strcmp(argv[1], "3") == 0) {
                // 恢复回来
                result = libusb_attach_kernel_driver(handle, 0);
                if (result == LIBUSB_SUCCESS) {
                    printf("libusb_attach_kernel_driver success\n");
                } else {
                    printf("libusb_attach_kernel_driver failed\n");
                }
            } else {
                printf("argument error, argv[1] %s\n", argv[1]);
            }
            
            libusb_close(handle);
            break;
        }
    }
    
    // 释放资源
    libusb_free_device_list(devs, 1);
    libusb_exit(NULL);
    return 0;
}
/*
root@ubuntu:/home# ./a.out 2
Found USB device with VID=0x090c, PID=0x2000
libusb_claim_interface success
waiting 20 seconds

root@ubuntu:~# lsusb -t
/:  Bus 04.Port 1: Dev 1, Class=root_hub, Driver=xhci_hcd/2p, 5000M
    |__ Port 1: Dev 28, If 0, Class=Mass Storage, Driver=usbfs, 5000M
/:  Bus 03.Port 1: Dev 1, Class=root_hub, Driver=xhci_hcd/2p, 480M
/:  Bus 02.Port 1: Dev 1, Class=root_hub, Driver=ehci-pci/2p, 480M
    |__ Port 1: Dev 2, If 0, Class=Hub, Driver=hub/4p, 480M
/:  Bus 01.Port 1: Dev 1, Class=root_hub, Driver=ehci-pci/2p, 480M
    |__ Port 1: Dev 2, If 0, Class=Hub, Driver=hub/4p, 480M
root@ubuntu:~# lsusb -t
/:  Bus 04.Port 1: Dev 1, Class=root_hub, Driver=xhci_hcd/2p, 5000M
    |__ Port 1: Dev 28, If 0, Class=Mass Storage, Driver=, 5000M
/:  Bus 03.Port 1: Dev 1, Class=root_hub, Driver=xhci_hcd/2p, 480M
/:  Bus 02.Port 1: Dev 1, Class=root_hub, Driver=ehci-pci/2p, 480M
    |__ Port 1: Dev 2, If 0, Class=Hub, Driver=hub/4p, 480M
/:  Bus 01.Port 1: Dev 1, Class=root_hub, Driver=ehci-pci/2p, 480M
    |__ Port 1: Dev 2, If 0, Class=Hub, Driver=hub/4p, 480M

root@ubuntu:/home# ./a.out 3
Found USB device with VID=0x090c, PID=0x2000
libusb_attach_kernel_driver success

root@ubuntu:~# lsusb -t
/:  Bus 04.Port 1: Dev 1, Class=root_hub, Driver=xhci_hcd/2p, 5000M
    |__ Port 1: Dev 28, If 0, Class=Mass Storage, Driver=usb-storage, 5000M
/:  Bus 03.Port 1: Dev 1, Class=root_hub, Driver=xhci_hcd/2p, 480M
/:  Bus 02.Port 1: Dev 1, Class=root_hub, Driver=ehci-pci/2p, 480M
    |__ Port 1: Dev 2, If 0, Class=Hub, Driver=hub/4p, 480M
/:  Bus 01.Port 1: Dev 1, Class=root_hub, Driver=ehci-pci/2p, 480M
    |__ Port 1: Dev 2, If 0, Class=Hub, Driver=hub/4p, 480M
*/
