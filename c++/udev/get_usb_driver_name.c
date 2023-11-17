/**
* 文 件 名: remount_kernel_driver.c
* 文件描述: 卸载和加载内核驱动
* 备    注: 此为xubuntu编译版本，尝试卸载usb-storage驱动
* 作    者: HanKin
* 创建日期: 2023.05.06
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
#include <assert.h>
#include <linux/usbdevice_fs.h>
#include <sys/ioctl.h>
#include <libusb-1.0/libusb.h>

// 一款USB3.0协议的U盘
#define USB_VENDOR_ID  0x0c45
#define USB_PRODUCT_ID 0x636d

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

            struct libusb_config_descriptor *config = NULL;
            int r = libusb_get_active_config_descriptor(devs[i], &config);
            if (r < 0 && r != LIBUSB_ERROR_NOT_FOUND) {
                if (r == LIBUSB_ERROR_NO_MEM)
                    return -ENOMEM;
                return -EIO;
            }
            assert(config);
            printf("usb device has %d interfaces\n", config->bNumInterfaces);
            for (int j = 0; j < config->bNumInterfaces; j++) {
                
                int interface = config->interface[j].altsetting[0].bInterfaceNumber;
                struct usbdevfs_getdriver getdrv;
                getdrv.interface = interface;
                r = ioctl(fd, USBDEVFS_GETDRIVER, &getdrv);
                if (r == 0) {
                    printf("usb driver name: %s\n", getdrv.driver);
                }
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