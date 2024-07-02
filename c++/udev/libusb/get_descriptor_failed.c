/**
* 文 件 名: get_descriptor_failed.c
* 文件描述: libusb获取描述符失败（安全管控软件影响）
* 作    者: HanKin
* 备    注: 编译需要安装libusb库,并且需要增加-lusb-1.0参数
* 创建日期: 2024.06.19
* 修改日期：2024.06.19
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
        if (r < 0) {
            fprintf(stderr, "failed to get device descriptor\n");
            continue;
        }
        printf("usb device: %04x:%04x\n", desc.idVendor, desc.idProduct);

        if (desc.idVendor == 0x3a59 && desc.idProduct == 0x445a) {
            r = libusb_open(devs[i], &dev_handle);
            if (r < 0) {
                fprintf(stderr, "failed to libusb_open\n");
                continue;
            }

            printf("Found device: %04x:%04x\n", desc.idVendor, desc.idProduct);
            printf("bcdUSB : %d bDeviceClass : %d\n", desc.bcdUSB, desc.bDeviceClass);

            libusb_close(dev_handle);
        }
        
        // 获取配置描述符
        struct libusb_config_descriptor *conf_desc = NULL;
        r = libusb_get_config_descriptor(devs[i], 0, &conf_desc);
        if (r < 0) {
            fprintf(stderr, "failed to get config descriptor\n");
            continue;
        }
        printf("bNumConfigurations: 0x%02x, wTotalLength: 0x%04x\n", desc.bNumConfigurations, conf_desc->wTotalLength);
        int j = 0;
        uint8_t *tmp = (uint8_t *)conf_desc;    // 注意一定需要unsigned类型，否则异常
        for (j = 0; j < LIBUSB_DT_CONFIG_SIZE; j++) {
            printf("%02x%c", tmp[j], j == LIBUSB_DT_CONFIG_SIZE - 1 ? '\n' : ' ');
        }
        printf("\n");
    }

    libusb_free_device_list(devs, 1);
    libusb_exit(NULL);

    return 0;
}