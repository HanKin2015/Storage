/**
* 文 件 名: libusb_sample.c
* 文件描述: libusb_introduction.cpp的简写版
* 作    者: HanKin
* 创建日期: 2023.07.20
* 修改日期：2023.07.20
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

// 设备的vid和pid
#define USB_VENDOR_ID  0x090c
#define USB_PRODUCT_ID 0x2000

// 总线编号和总线触角编号
#define BUS_NUMBER  4
#define DEV_ADDRESS 2

// class code
#define MASS_STORAGE_CODE 0x08
#define HUB_CLASS_CODE 0x09

static int init(libusb_context *ctx)
{
    int ret = -1;
    ret = libusb_init(&ctx);
    if (ret < 0) {
        fprintf(stderr, "libusb_init error: %s\n", libusb_error_name(ret));
        return -1;
    }
    return 0;
}

static int open_designated_device(libusb_context *ctx, libusb_device_handle **handle, int open_mode)
{
    int usbbus = 0, usbaddr = 0;
    
    if (open_mode) { // 通过vid和pid
        *handle = libusb_open_device_with_vid_pid(ctx, USB_VENDOR_ID, USB_PRODUCT_ID);
        if (!*handle) {
            fprintf(stderr,
                "Could not open an usb-device with vid:pid %04x:%04x\n",
                USB_VENDOR_ID, USB_PRODUCT_ID);
        }
    } else {
        libusb_device **list = NULL;
        ssize_t i, n;
        n = libusb_get_device_list(ctx, &list);
        for (i = 0; i < n; i++) {
            //printf("bus number %d, device_address %d\n", libusb_get_bus_number(list[i]),
            //        libusb_get_device_address(list[i]));
            if (libusb_get_bus_number(list[i]) == BUS_NUMBER &&
                libusb_get_device_address(list[i]) == DEV_ADDRESS) {
                break;
            }
        }
        if (i < n) {
            if (libusb_open(list[i], handle) != 0) {
                fprintf(stderr,
                    "Could not open usb-device at bus-addr %d-%d\n",
                    usbbus, usbaddr);
            }
        } else {
            fprintf(stderr,
                "Could not find an usb-device at bus-addr %d-%d\n",
                usbbus, usbaddr);
        }
        libusb_free_device_list(list, 1);
    }
    if (*handle == NULL) {
        printf("Get libusb_device_handle failed\n");
        return -1;
    }
    return 0;
}

static int get_interface_attr(libusb_context *ctx, libusb_device_handle *handle, int &interface_number)
{
    assert(handle);
    int ret = -1;

    /* Step1: 将libusb_device_handle转换为libusb_device */
    libusb_device* dev = NULL;
    dev = libusb_get_device(handle);
    if (dev == NULL) {
        printf("libusb_get_device error\n");
        return -1;
    }

    /* Step2: 获取配置描述符 */
    struct libusb_config_descriptor* conf_desc;
    const struct libusb_endpoint_descriptor* endpoint;
    uint8_t endpoint_in = 0, endpoint_out = 0;	// default IN and OUT endpoints
    int nb_ifaces;
    uint8_t interfaceClass;

    ret = libusb_get_config_descriptor(dev, 0, &conf_desc);
    if (ret < 0) {
        fprintf(stderr, "failed to get config descriptor");
        return -1;
    }
    /* Step3：获取接口描述符 */
    nb_ifaces = conf_desc->bNumInterfaces;
    for(int i = 0; i < nb_ifaces; i++) {
        for (int j = 0; j < conf_desc->interface[i].num_altsetting; j++) {
            //获取接口类别为：hub https://www.usb.org/defined-class-codes
            interfaceClass = conf_desc->interface[i].altsetting[j].bInterfaceClass;
            if (interfaceClass != MASS_STORAGE_CODE) {
                continue;
            }
            interface_number = i;
            for (int k = 0; k < conf_desc->interface[i].altsetting[j].bNumEndpoints; k++) {
                endpoint = &conf_desc->interface[i].altsetting[j].endpoint[k];
                // Use the first bulk IN/OUT endpoints as default for testing
                if ((endpoint->bmAttributes & LIBUSB_TRANSFER_TYPE_MASK) & (LIBUSB_TRANSFER_TYPE_BULK)) {//只获取批量传输端点
                    if (endpoint->bEndpointAddress & LIBUSB_ENDPOINT_IN) {
                        if (!endpoint_in) {
                            endpoint_in = endpoint->bEndpointAddress;
                          //  libusb_clear_halt(handle, bdev->endpoint_in);//清除暂停标志
                        }
                    } else {
                        if (!endpoint_out) {
                            endpoint_out = endpoint->bEndpointAddress;
                           // libusb_clear_halt(handle, bdev->endpoint_out);
                        }
                    }
                }
            }
            break;
        }
    }

    libusb_free_config_descriptor(conf_desc);
    conf_desc = NULL;
    printf("interface number %d, ep in 0x%02x, ep out 0x%02x\n", interface_number, endpoint_in, endpoint_out);
    return 0;
}

static int read_device(libusb_device_handle* handle, void *buffer, int len, int ms)
{
    int size, errcode;
    uint8_t endpoint_in = 0x82;
    int interface_number = 0;

    errcode = libusb_bulk_transfer(handle, endpoint_in, (unsigned char*)buffer, len, &size, ms);
    if (errcode < 0) {
        printf("read:   %s\n", libusb_strerror((enum libusb_error)errcode));
        return -1;
    }

    int offset = 0, rsize = 0;
    if (size != len) {
        offset = len - size;
        errcode = libusb_bulk_transfer(handle, endpoint_in, (unsigned char*)buffer + offset, offset, &rsize, ms);
        if (errcode < 0)
        {
            printf("read:   %s\n", libusb_strerror((enum libusb_error)errcode));
            return -1;
        }
    }

    libusb_release_interface(handle, interface_number);
    return size + offset;
}

int main(int argc, char *argv[])
{
    int ret = -1;
    
    // 初始化libusb库
    libusb_context *ctx = NULL;
    init(ctx);
    
    // 打开指定设备
    libusb_device_handle *handle = NULL;
    open_designated_device(ctx, &handle, 1);

    // 获取某个接口
    int interface_number = -1;
    get_interface_attr(ctx, handle, interface_number);
    
    // 接口驱动分离
    libusb_detach_kernel_driver(handle, interface_number);
    
    // 复位设备
    libusb_reset_device(handle);
    
    // 获取接口权限，加载usbfs驱动
    ret = libusb_claim_interface(handle, interface_number);
    assert(ret == LIBUSB_SUCCESS);

    // 读写设备
    unsigned char buffer[256] = { 0 };
    read_device(handle, buffer, 256, 5000);
    
    // 这步一定需要，不然后面函数加载原驱动会失败，并且必须要在读写设备后面
    ret = libusb_release_interface(handle, interface_number);
    assert(ret == LIBUSB_SUCCESS);
    
    // 睡眠5秒
    sleep(5);
    
    // 接口驱动还原
    ret = libusb_attach_kernel_driver(handle, interface_number);
    if (ret == LIBUSB_SUCCESS) {
        printf("libusb_attach_kernel_driver success\n");
    } else {
        printf("libusb_attach_kernel_driver failed, %s\n", libusb_error_name(ret));
    }
    
    // 关闭设备
    libusb_close(handle);
    
    // 反初始化libusb库
    libusb_exit(ctx);
    return 0;
}