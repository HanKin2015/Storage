/**
* 文 件 名: replace_kernel_driver.c
* 文件描述: 替换USB设备内核驱动
* 备    注: 此为xubuntu编译版本，尝试卸载usb-storage驱动，需要添加编译参数
* 作    者: HanKin
* 创建日期: 2023.05.11
* 修改日期：2023.05.11
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

/**
* @brief  获取USB设备驱动名称，使用ioctl函数，宏定义在linux-5.15.4/include/uapi/linux/usbdevice_fs.h
* @note   op_kernel_driver_active库函数只判断当前驱动是否为usbfs驱动，改写后返回驱动名称
* @param  fd [in] USB设备文件描述符
* @param  interface [in] 设备接口
* @return usbfs等
*/
static char *op_kernel_driver_active(int fd, int interface)
{
    struct usbdevfs_getdriver getdrv;
    int r;

    getdrv.interface = interface;
    r = ioctl(fd, USBDEVFS_GETDRIVER, &getdrv);
    if (r) {
        if (errno == ENODATA) {
            printf("errno: ENODATA(%d)\n", errno);
            return NULL;
        } else if (errno == ENODEV) {
            printf("errno: ENODEV(%d), LIBUSB_ERROR_NO_DEVICE\n", errno);
            return NULL;
        }

        printf("get driver failed error %d errno %d, LIBUSB_ERROR_OTHER\n", r, errno);
        return NULL;
    }

    printf("getdrv.driver: %s\n", getdrv.driver);
    
    // 直接返回getdrv.driver会报错，并且内存被清除了
    printf("strlen(getdrv.driver): %ld\n", strlen(getdrv.driver));
    char *driver_name = (char *)malloc(strlen(getdrv.driver)+1);
    memset(driver_name, 0, strlen(getdrv.driver)+1);
    memcpy(driver_name, getdrv.driver, strlen(getdrv.driver));
    return driver_name;
}

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

            // 获取USB设备驱动名称
            char *driver_name = op_kernel_driver_active(fd, 0);
            printf("driver_name: %s\n", driver_name);

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
                // 请求接口访问权限
#if LIBUSBX_API_VERSION >= 0x01000102
                (void)libusb_set_auto_detach_kernel_driver(handle, 1);
#endif
                result = libusb_claim_interface(handle, 0);
                if (result == LIBUSB_SUCCESS) {
                    printf("libusb_claim_interface auto_detach_kernel_driver 1 success\n");
                } else {
                    printf("libusb_claim_interface auto_detach_kernel_driver 1 failed\n");
                }
            } else if (strcmp(argv[1], "3") == 0) {
                // 请求接口访问权限，如果USB设备加载了驱动则会失败，因为这个0表示告知已卸载了驱动
#if LIBUSBX_API_VERSION >= 0x01000102
                (void)libusb_set_auto_detach_kernel_driver(handle, 0);
#endif
                result = libusb_claim_interface(handle, 0);
                if (result == LIBUSB_SUCCESS) {
                    printf("libusb_claim_interface auto_detach_kernel_driver 0 success\n");
                } else {
                    printf("libusb_claim_interface auto_detach_kernel_driver 0 failed\n");
                }
            } else if (strcmp(argv[1], "4") == 0) {
                // 猜测默认应该是会自动加载了驱动，测试发现默认居然是认为卸载驱动
#if LIBUSBX_API_VERSION < 0x01000102
                libusb_detach_kernel_driver(handle, 0);
#endif
                result = libusb_claim_interface(handle, 0);
                if (result == LIBUSB_SUCCESS) {
                    printf("libusb_claim_interface success\n");
                } else {
                    printf("libusb_claim_interface failed\n");
                }
            } else {
                printf("argument error, argv[1] %s\n", argv[1]);
            }

            printf("waiting 20 seconds\n");
            sleep(20);
            libusb_close(handle);
            close(fd);
            free(driver_name);
            driver_name = NULL;
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
