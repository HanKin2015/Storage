/**
* 文 件 名: study_libusb.cpp
* 文件描述: 学习libusb
* 作    者: HanKin
* 备    注: 编译需要安装libusb库,并且需要增加-lusb-1.0 -lpthread -lm参数
* 创建日期: 2021.10.12
* 修改日期：2021.10.12
*
* Copyright (c) 2021 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libusb-1.0/libusb.h>

libusb_device_handle* deviceHandle = NULL;

int DoList();
libusb_device_handle* GetTRSDevice(void);

int main()
{
    int ret = libusb_init(NULL);
    if (ret < 0) {
        printf("Failed to init libusb\n");
        return ret;
    }

    DoList();
    deviceHandle = GetTRSDevice();
    if(!deviceHandle) {
        printf("Failed to locate device\n");
        goto fail_dev_open;
    }

    printf("Device opened\n");

    libusb_close(deviceHandle);
    fail_dev_open:
        libusb_exit(NULL);

    return(ret);
}

int DoList()
{
    libusb_device **devs;
    ssize_t cnt;


    cnt = libusb_get_device_list(NULL, &devs);
    if (cnt < 0)
        return (int) cnt;

    libusb_device *dev;
    int i = 0;

    while ((dev = devs[i++]) != NULL) {
        struct libusb_device_descriptor desc;
        int r = libusb_get_device_descriptor(dev, &desc);
        if (r < 0) {
            fprintf(stderr, "failed to get device descriptor");
            return(-1);
        }

        printf("%04x:%04x (bus %d, device %d)\n",
               desc.idVendor, desc.idProduct,
               libusb_get_bus_number(dev), libusb_get_device_address(dev));
    }
    libusb_free_device_list(devs, 1);
    return 0;
}

libusb_device_handle* GetTRSDevice(void)
{
    int i = 0;
    ssize_t cnt;
    libusb_device *dev;
    libusb_device **devs;
    libusb_device_handle* handle = NULL;

    cnt = libusb_get_device_list(NULL, &devs);
    if (cnt < 0) {
        printf("Failed libusb_get_device_list\n");
        return(0);
    }

    while ((dev = devs[i++]) != NULL) {
        struct libusb_device_descriptor desc;
        int ret = libusb_get_device_descriptor(dev, &desc);
        if (ret < 0) {
            printf("Failed libusb_get_device_descriptor\n");
            continue;
        }
        if(desc.idVendor == 0X0781 && desc.idProduct == 0x557d) {
            int ret = libusb_open(dev, &handle);
            if (ret < 0) {
                printf("Failed libusb_open: %d\n\r",ret);
                break;
            }
            #ifndef WIN32
                libusb_detach_kernel_driver(handle, 0);
            #endif
            ret = libusb_claim_interface(handle,0);
            if (ret < 0) {
                libusb_close(handle);
                handle=NULL;
                break;
            }
            break;
        }
    }
    libusb_free_device_list(devs, 1);
    return(handle);
}