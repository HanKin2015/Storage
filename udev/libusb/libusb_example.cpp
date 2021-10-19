/**
* 文 件 名: libusb_example.cpp
* 文件描述: libusb参考例子
* 作    者: HanKin
* 创建日期: 2021.10.12
* 修改日期：2021.10.12
*
* Copyright (c) 2021 HanKin. All rights reserved.
*/

#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <sys/types.h>

static void print_devs(libusb_device **devs)
{
    libusb_device *dev;
    int i = 0;

    while ((dev = devs[i++]) != NULL) {
        struct libusb_device_descriptor desc;
        int r = libusb_get_device_descriptor(dev, &desc);
        if (r < 0) {
            fprintf(stderr, "failed to get device descriptor");
            return;
        }

        printf("%04x:%04x (bus %d, device %d)\n",
            desc.idVendor, desc.idProduct,
            libusb_get_bus_number(dev), libusb_get_device_address(dev));
    }
    return;
}

int main(int argc, char *argv[])
{
    libusb_device **devs;
    int r;
    ssize_t cnt;

    r = libusb_init(NULL);
    if (r < 0)
        return r;

    cnt = libusb_get_device_list(NULL, &devs);
    if (cnt < 0) {
        return (int) cnt;
    }

    print_devs(devs);
    libusb_free_device_list(devs, 1);

    libusb_exit(NULL);

    return 0;
}