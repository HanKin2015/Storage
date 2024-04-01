/**
* 文 件 名: libusb_get_descriptor.cpp
* 文件描述: libusb获取描述符
* 作    者: HanKin
* 备    注: 编译需要安装libusb库,并且需要增加-lusb-1.0参数
* 创建日期: 2023.07.05
* 修改日期：2024.03.20
*
* Copyright (c) 2024 HanKin. All rights reserved.
*/

#include <libusb-1.0/libusb.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    libusb_device **devs;
    libusb_device_handle *dev_handle;
    struct libusb_device_descriptor desc;
    int r, i;

    r = libusb_init(NULL);
    if (r < 0)
        return r;

    r = libusb_get_device_list(NULL, &devs);
    if (r < 0)
        return r;

    for (i = 0; devs[i]; i++) {
        r = libusb_get_device_descriptor(devs[i], &desc);
        if (r < 0)
            continue;

        if (desc.idVendor == 0x1d6b && desc.idProduct == 0x0003) {
            r = libusb_open(devs[i], &dev_handle);
            if (r < 0)
                continue;

            printf("Found device: %04x:%04x\n", desc.idVendor, desc.idProduct);
            printf("bcdUSB : %d bDeviceClass : %d\n", desc.bcdUSB, desc.bDeviceClass);

            libusb_close(dev_handle);
        }
        
        // 获取配置描述符
        struct libusb_config_descriptor *conf_desc = NULL;
        r = libusb_get_config_descriptor(devs[i], 0, &conf_desc);
        if (r < 0) {
            fprintf(stderr, "failed to get config descriptor");
            continue;
        }
        printf("%02x %04x\n", desc.bNumConfigurations, conf_desc->wTotalLength);
        int j = 0;
        uint8_t *tmp = (uint8_t *)conf_desc;    // 注意一定需要unsigned类型，否则异常
        for (j = 0; j < LIBUSB_DT_CONFIG_SIZE; j++) {
            printf("%02x%c", tmp[j], j == LIBUSB_DT_CONFIG_SIZE - 1 ? '\n' : ' ');
        }
    }

    libusb_free_device_list(devs, 1);
    libusb_exit(NULL);

    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
09 02 19 00 01 01 00 ffffffe0 00
09 02 19 00 01 01 00 ffffffe0 00
09 02 1f 00 01 01 00 ffffffe0 00
09 02 19 00 01 01 00 ffffffe0 00
09 02 19 00 01 01 00 ffffffe0 00
09 02 19 00 01 01 00 ffffffe0 00
09 02 19 00 01 01 00 ffffffe0 00
09 02 19 00 01 01 00 ffffffe0 00
09 02 19 00 01 01 00 ffffffe0 00
09 02 19 00 01 01 00 ffffffe0 00
09 02 19 00 01 01 00 ffffffe0 00
09 02 19 00 01 01 00 ffffffe0 00
09 02 19 00 01 01 00 ffffffe0 00
[root@ubuntu0006:~/cmake] #./a.out
01 0019
09 02 19 00 01 01 00 e0 00
01 0019
09 02 19 00 01 01 00 e0 00
01 001f
09 02 1f 00 01 01 00 e0 00
01 0019
09 02 19 00 01 01 00 e0 00
01 0019
09 02 19 00 01 01 00 e0 00
01 0019
09 02 19 00 01 01 00 e0 00
01 0019
09 02 19 00 01 01 00 e0 00
01 0019
09 02 19 00 01 01 00 e0 00
01 0019
09 02 19 00 01 01 00 e0 00
01 0019
09 02 19 00 01 01 00 e0 00
01 0019
09 02 19 00 01 01 00 e0 00
01 0019
09 02 19 00 01 01 00 e0 00
01 0019
09 02 19 00 01 01 00 e0 00
*/