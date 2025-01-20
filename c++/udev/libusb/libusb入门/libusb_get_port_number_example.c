/*******************************************************************************
* 文 件 名: libusb_get_port_number_example.c
* 文件描述: libusb_get_port_numbers和libusb_get_port_number函数区别
* 备    注: 编译需要安装libusb库,并且需要增加-lusb-1.0参数
* 作    者: HanKin
* 创建日期: 2025.01.06
* 修改日期：2025.01.06
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
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
#define USB_VENDOR_ID  0x1a81
#define USB_PRODUCT_ID 0x223a

int main(int argc, char *argv[])
{
    uint16_t vid = USB_VENDOR_ID;
    uint16_t pid = USB_PRODUCT_ID;
    if (argc == 3) {
        // atoi 只支持十进制字符串的转换
        vid = (uint16_t)strtol(argv[1], NULL, 16);
        pid = (uint16_t)strtol(argv[2], NULL, 16);
    }

    // 初始化libusb库
    libusb_context *ctx = NULL;
    libusb_init(&ctx);
    
    printf("libusb_context ctx: %p, open device(%04x:%04x)\n", ctx, vid, pid);
    
    // 打开指定设备
    libusb_device_handle *handle = libusb_open_device_with_vid_pid(ctx, vid, pid);
    if (!handle) {
        printf("open device(%04x:%04x) failed!\n", vid, pid);
        return -1;
    }

    // handle转换成device
    libusb_device* dev = libusb_get_device(handle);
    
    // 打印总线编号
    printf("bus number: %d\n", libusb_get_bus_number(dev));

    // libusb_get_port_number函数
    int port_number = libusb_get_port_number(dev);
    printf("Device port number: %d\n", port_number);

    // libusb_get_port_numbers函数
    uint8_t port_numbers[8]; // 假设最多有 8 个端口
    int num_ports = libusb_get_port_numbers(dev, port_numbers, sizeof(port_numbers));

    if (num_ports > 0) {
        printf("Device port path: ");
        for (int i = 0; i < num_ports; i++) {
            printf("%d ", port_numbers[i]);
        }
        printf("\n");
    }

    // 关闭设备
    libusb_close(handle);
    
    // 反初始化libusb库
    libusb_exit(ctx);
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #gcc libusb_get_port_number_example.c -lusb-1.0
[root@ubuntu0006:~/cmake] #./a.out 0409 55aa
libusb_context ctx: 0x1afc010, open device(0409:55aa)
bus number: 3
Device port number: 1
Device port path: 1
[root@ubuntu0006:~/cmake] #./a.out 0x0409 0x55aa
libusb_context ctx: 0x1661010, open device(0409:55aa)
bus number: 3
Device port number: 1
Device port path: 1
[root@ubuntu0006:~/cmake] #./a.out
libusb_context ctx: 0x857010, open device(1a81:223a)
open device(1a81:223a) failed!
root@hankin:~# lsusb -t
/:  Bus 04.Port 1: Dev 1, Class=root_hub, Driver=xhci_hcd/2p, 5000M
/:  Bus 03.Port 1: Dev 1, Class=root_hub, Driver=xhci_hcd/2p, 480M
    |__ Port 2: Dev 56, If 0, Class=Audio, Driver=snd-usb-audio, 12M
    |__ Port 2: Dev 56, If 1, Class=Audio, Driver=snd-usb-audio, 12M
    |__ Port 2: Dev 56, If 2, Class=Audio, Driver=snd-usb-audio, 12M
    |__ Port 2: Dev 56, If 3, Class=Human Interface Device, Driver=, 12M
/:  Bus 02.Port 1: Dev 1, Class=root_hub, Driver=ehci-pci/2p, 480M
    |__ Port 1: Dev 2, If 0, Class=Hub, Driver=hub/4p, 480M
/:  Bus 01.Port 1: Dev 1, Class=root_hub, Driver=ehci-pci/2p, 480M
    |__ Port 1: Dev 2, If 0, Class=Hub, Driver=hub/4p, 480M
        |__ Port 2: Dev 12, If 0, Class=Human Interface Device, Driver=usbhid, 12M
        |__ Port 2: Dev 12, If 1, Class=Human Interface Device, Driver=usbhid, 12M
        |__ Port 2: Dev 12, If 2, Class=Human Interface Device, Driver=usbhid, 12M
        |__ Port 3: Dev 7, If 0, Class=Human Interface Device, Driver=usbhid, 12M
        |__ Port 3: Dev 7, If 1, Class=Human Interface Device, Driver=usbhid, 12M
root@hankin:~# ./a.out 0b0e 0420
libusb_context ctx: 0x23af010, open device(0b0e:0420)
bus number: 3
Device port number: 2
Device port path: 2
root@hankin:~# ./a.out 1a81 203e
libusb_context ctx: 0x1282010, open device(1a81:203e)
bus number: 1
Device port number: 2
Device port path: 1 2
root@hankin:~# ./a.out
libusb_context ctx: 0xaf5010, open device(1a81:223a)
bus number: 1
Device port number: 3
Device port path: 1 3
*/