#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <linux/usbdevice_fs.h> // 关键头文件，定义了 ioctl 命令

// USB 请求定义
#define USB_REQ_GET_DESCRIPTOR 0x06
#define USB_DT_DEVICE 0x01
#define USB_DIR_IN 0x80

struct usb_ctrlrequest {
    __u8 bRequestType;
    __u8 bRequest;
    __u16 wValue;
    __u16 wIndex;
    __u16 wLength;
};
int main (int argc, char *argv [])
{
    int fd;
    struct usbdevfs_ctrltransfer ctrl;
    unsigned char buf [18]; // 设备描述符标准长度是 18 字节
    int ret;
    // 1. 设置默认总线号和设备号
    int bus_num = 1;      // 默认 bus 001
    int dev_num = 2;      // 默认 device 002
    char dev_path [64];    // 用于存储完整路径 "/dev/bus/usb/001/002"
    // 2. 解析命令行参数
    if (argc >= 3) {
        bus_num = atoi (argv [1]);
        dev_num = atoi (argv [2]);
    } else if (argc == 2 && (strcmp (argv [1], "-h") == 0 || strcmp (argv [1], "--help") == 0)) {
        printf ("Usage: % s [bus_number] [device_number]\n", argv [0]);
        printf ("Example: % s 1 2  (reads /dev/bus/usb/001/002)\n", argv [0]);
        printf ("Defaults: bus=1, device=2 if no arguments provided.\n");
        return 0;
    }
    // 3. 构建设备路径字符串 (格式化为三位数，如 001, 002)
    snprintf (dev_path, sizeof (dev_path), "/dev/bus/usb/%03d/%03d", bus_num, dev_num);
    printf ("Attempting to open: % s\n", dev_path);
    // 4. 打开设备
    fd = open (dev_path, O_RDWR);
    if (fd < 0) {
        perror ("Failed to open USB device");
        printf ("Hint: Are you root? Check path with 'ls /dev/bus/usb/*/*'\n");
        return 1;
    }
    printf ("Opened USB device successfully.\n");
    // 5. 构造控制传输请求 (后续逻辑不变)
    memset (&ctrl, 0, sizeof (ctrl));
    ctrl.bRequestType = 0x80; // USB_DIR_IN
    ctrl.bRequest     = 0x06; // USB_REQ_GET_DESCRIPTOR
    ctrl.wValue       = (0x01 << 8) | 0x00; // USB_DT_DEVICE
    ctrl.wIndex       = 0;
    ctrl.wLength      = sizeof (buf);
    ctrl.data         = buf;
    ctrl.timeout      = 5000;
    ret = ioctl (fd, USBDEVFS_CONTROL, &ctrl);
    if (ret < 0) {
        perror ("ioctl USBDEVFS_CONTROL failed");
        close (fd);
        return 1;
    }
    printf ("Successfully read % d bytes.\n", ret);
    // 6. 解析并打印描述符 (后续逻辑不变)
    if (ret >= 18) {
        printf ("--- Device Descriptor ---\n");
        printf ("Length:             % d\n", buf [0]);
        printf ("Descriptor Type:    % d\n", buf [1]);
        printf ("USB Version:        % x.%02x\n", buf [3], buf [2]);
        printf ("Device Class:       % d\n", buf [4]);
        printf ("Device SubClass:    % d\n", buf [5]);
        printf ("Device Protocol:    % d\n", buf [6]);
        printf ("Max Packet Size:    % d\n", buf [7]);
        printf ("Vendor ID:          %04x\n", (buf [9] << 8) | buf [8]);
        printf ("Product ID:         %04x\n", (buf [11] << 8) | buf [10]);
        printf ("Release Number:     % x.%02x\n", buf [13], buf [12]);
        printf ("Manufacturer Index: % d\n", buf [14]);
        printf ("Product Index:      % d\n", buf [15]);
        printf ("Serial Number Index:% d\n", buf [16]);
        printf ("Num Configurations: % d\n", buf [17]);
    }
    close (fd);
    return 0;
}