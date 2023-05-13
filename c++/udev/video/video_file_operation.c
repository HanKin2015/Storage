/**
* 文 件 名: video_file_operation.c.c
* 文件描述: 发现v4l2库中ioctl只能获取摄像头相关的信息
* 作    者: HanKin
* 创建日期: 2023.05.12
* 修改日期：2023.05.13
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
#include <linux/videodev2.h>

#define USB_VENDOR_ID  0x0ac8
#define USB_PRODUCT_ID 0x3500

#define USB_PATH_PORT_MAX 16
#define DEV_PATH_LEN 64

static int video_file_operation()
{
    // 存在这么一个目录'/sys/class/video4linux/video0/'，但没有什么有用信息
    // ioctl函数宏定义在linux-5.15.4/include/uapi/linux/videodev2.h
    
    int fd = open("/dev/video0", O_RDWR);
    if (fd == -1) {
        perror("Failed to open device");
        exit(EXIT_FAILURE);
    }

    struct v4l2_capability cap;
    if (ioctl(fd, VIDIOC_QUERYCAP, &cap) == -1) {
        perror("Failed to query device capabilities");
        exit(EXIT_FAILURE);
    }

    printf("Driver: %s\n", cap.driver);
    printf("Card: %s\n", cap.card);
    printf("Bus info: %s\n", cap.bus_info);
    printf("Version: %u.%u.%u\n", (cap.version >> 16) & 0xFF, (cap.version >> 8) & 0xFF, cap.version & 0xFF);
    printf("Capabilities: 0x%08X\n", cap.capabilities);
    printf("Device capabilities: 0x%08X\n", cap.device_caps);

    // VID和PID是USB设备的属性，而不是视频设备的属性，因此无法通过视频设备的/dev/videoX节点来获取它们。
    printf("VID: 0x%04X\n", (cap.capabilities >> 16) & 0xFFFF);
    printf("PID: 0x%04X\n", cap.capabilities & 0xFFFF);
    
    close(fd);
    return 0 ;
}

int main(int argc, char *argv[])
{
    video_file_operation();
    
    libusb_device_handle *dev_handle = NULL;
    libusb_device *udev = NULL;
    int result, i, fd;
    uint8_t ports[USB_PATH_PORT_MAX];
    int offset = 0;
    char devpath[DEV_PATH_LEN] = { 0 };

    libusb_context *ctx = NULL;
    result = libusb_init(&ctx);
    if (result < 0) {
        fprintf(stderr, "Failed to initialize libusb: %s\n", libusb_error_name(result));
        exit(EXIT_FAILURE);
    }

    // 还是需要调用libusb_init()函数，否则会报错Segmentation fault (core dumped)
    dev_handle = libusb_open_device_with_vid_pid(NULL, USB_VENDOR_ID, USB_PRODUCT_ID);
    if (dev_handle == NULL) {
        fprintf(stderr, "libusb_open_device_with_vid_pid error: %s\n", libusb_error_name(errno));
        return -1;
    }
    udev = libusb_get_device(dev_handle);
    if (udev == NULL) {
        fprintf(stderr, "libusb_open error: %s\n", libusb_error_name(errno));
        return -1;
    }
    
    // 使用命令可以获取udevadm info -a -p $(udevadm info -q path -n /dev/video0)
    // 更简单是lsusb就可以看见Bus 003 Device 065: ID 0ac8:3500 Z-Star Microelectronics Corp.
    uint8_t busnum = libusb_get_bus_number(udev);
    uint8_t devnum = libusb_get_device_address(udev);   // devaddr
    printf("busnum %d devnum %d\n", busnum, devnum);
    
    result = libusb_get_port_numbers(udev, ports, sizeof(ports));
     if(result < 0) {
         printf("cannot get device path %s\n", libusb_strerror(result));
         return -1;
     }
    offset += snprintf(devpath + offset, DEV_PATH_LEN - offset - 1, result == 0 ? "%d" : "%d-", busnum);
    for (i = 0; i < result; i++) {
        offset += snprintf(devpath + offset, DEV_PATH_LEN - offset - 1, "%s%d", i == 0 ? "" : ".", (int)ports[i]);
    }
    printf("offset = %d, device path = %s\n", offset, devpath);
    
    // 获取USB设备文件描述符，思考这个文件描述符是否能进行ioctl函数？？？
    // 答案是不行，报错Failed to query device capabilities: Inappropriate ioctl for device
    char path[64] = { 0 };
    snprintf(path, sizeof(path), "/dev/bus/usb/%03d/%03d", busnum, devnum);
    fd = open(path, O_RDWR);
    if (fd < 0) {
        fprintf(stderr, "open error: %m\n");
        libusb_close(dev_handle);
        return -1;
    }
    
    struct v4l2_capability cap;
    if (ioctl(fd, VIDIOC_QUERYCAP, &cap) == -1) {
        perror("Failed to query device capabilities");
        exit(EXIT_FAILURE);
    }
    printf("Driver: %s\n", cap.driver);
    
    close(fd);
    libusb_close(dev_handle);
    libusb_exit(ctx);
    return 0;
}
/*
root@ubuntu:/home# ./a.out
Driver: uvcvideo
Card: Full HD 1080P PC Camera
Bus info: usb-0000:00:10.0-2
Version: 4.9.168
Capabilities: 0x84200001
Device capabilities: 0x04200001
VID: 0x8420
PID: 0x0001
busnum 3 devnum 65
offset = 3, device path = 3-2
Failed to query device capabilities: Inappropriate ioctl for device
*/
