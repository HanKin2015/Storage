/**
* 文 件 名: libusb_devic_and_libusb_device_handle.cpp
* 文件描述: libusb_device和libusb_device_handle的区别
* 作    者: HanKin
* 备    注: 编译需要安装libusb库,并且需要增加-lusb-1.0参数
* 创建日期: 2023.07.05
* 修改日期：2023.07.05
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>

#define USB_VENDOR_ID  0x1d6b
#define USB_PRODUCT_ID 0x0003

static libusb_device_handle *understand_libusb_device_handle()
{
    libusb_context *ctx = NULL;
    int result = libusb_init(&ctx);
    assert(result >= 0);
    
    // 通过libusb_open_device_with_vid_pid函数
    libusb_device_handle *dev_handle = libusb_open_device_with_vid_pid(NULL, USB_VENDOR_ID, USB_PRODUCT_ID);
    assert(dev_handle);
    
    // 通过libusb_open函数
    
    
    // 验证
    libusb_device *dev = libusb_get_device(dev_handle);
    assert(dev);
    uint8_t busnum = libusb_get_bus_number(dev);
    uint8_t devnum = libusb_get_device_address(dev);
    printf("busnum %d devnum %d\n", busnum, devnum);
    
    libusb_exit(ctx);
    return dev_handle;
}

static libusb_device *understand_libusb_device()
{
    libusb_context *ctx = NULL;
    int result = libusb_init(&ctx);
    assert(result >= 0);
    
    // 通过libusb_open_device_with_vid_pid函数
    libusb_device_handle *dev_handle = libusb_open_device_with_vid_pid(NULL, USB_VENDOR_ID, USB_PRODUCT_ID);
    
    // 通过libusb_open函数
}

int main(int argc, char *argv[])
{
    libusb_device_handle *dev_handle = understand_libusb_device_handle();
    
    
    // 两者之间进行转换

    return 0;
}