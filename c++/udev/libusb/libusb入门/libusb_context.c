/**
* 文 件 名: libusb_context.c
* 文件描述: libusb_context到底有没有作用
* 作    者: HanKin
* 创建日期: 2023.07.21
* 修改日期：2023.07.21
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
#define USB_VENDOR_ID  0x1d6b
#define USB_PRODUCT_ID 0x0003

int main(int argc, char *argv[])
{
    int ret = -1;
    
    // 初始化libusb库
    libusb_context *ctx = NULL;
    libusb_init(&ctx);
    
    printf("ctx: %p\n", ctx);
    
    // 打开指定设备
    libusb_device_handle *handle = libusb_open_device_with_vid_pid(ctx, USB_VENDOR_ID, USB_PRODUCT_ID);

    // handle转换成device
    libusb_device* dev = libusb_get_device(handle);
    
    // 打印总线编号
    printf("bus number: %d\n", libusb_get_bus_number(dev));

    // 关闭设备
    libusb_close(handle);
    
    // 反初始化libusb库
    libusb_exit(ctx);
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
ctx: 0x65c010
bus number: 12
[root@ubuntu0006:~/cmake] #vi k.cpp
[root@ubuntu0006:~/cmake] #g++ k.cpp -lusb-1.0 -g
[root@ubuntu0006:~/cmake] #./a.out
ctx: 0x1cff010
bus number: 12
*/