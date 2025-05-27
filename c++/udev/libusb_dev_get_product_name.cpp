/*******************************************************************************
* 文 件 名: libusb_dev_get_product_name.cpp
* 文件描述: 获取设备产品描述符
* 备    注: 编译需要安装libusb库,并且需要增加-lusb-1.0参数
* 作    者: HanKin
* 创建日期: 2025.05.23
* 修改日期：2025.05.23
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <iostream>

/**
 * @brief 获取设备sysfs attribute的值
 *
 * @param bus
 * @param address
 * @param attribute
 * @param value
 * @param length
 * @return int 成功时返回获取的value长度
 *             其他错误时返回-1
 *             该设备或者该属性值不存在时，返回-2 (即-ENOENT)
 */
static int get_sysfs_attribute(int bus, int address, const char *attribute,
                               char *value, int length)
{
    struct stat stat_buf;
    FILE *fp = NULL;
    char filename[256];
    char data[4096];
    int count = 4096;
    int read_len = 0;
    int data_len = 0;

    if (attribute == NULL || value == NULL) {
        printf("params error, attribute or value is null\n");
        return -1;
    }

    ::snprintf(filename, sizeof(filename), "/dev/bus/usb/%03d/%03d", bus,
               address);
    printf("stat filename:%s\n", filename);
    if (::stat((const char *)filename, &stat_buf) != 0) {
        printf("stat error failed, filename:%s\n", filename);
        return -1;
    }
    ::snprintf(filename, sizeof(filename), "/sys/dev/char/%d:%d/%s",
               ::major(stat_buf.st_rdev), ::minor(stat_buf.st_rdev), attribute);
    fp = ::fopen(filename, "r");
    if (fp == NULL) {
        if (errno == ENOENT) {
            return -ENOENT;  // -2
        }
        printf("open %s failed errno=%d\n", filename, errno);
        return -1;
    }

    while (read_len < length) {
        data_len = fread(data, sizeof(char), count, fp);
        if (ferror(fp) != 0) {
            printf("read file fail\n");
            ::fclose(fp);
            return -1;
        }
        ::memcpy(value + read_len, data, data_len);
        read_len += data_len;
        if (::feof(fp)) {
            break;
        }
    }
    ::fclose(fp);
    return read_len;
}

std::string libusb_dev_get_product_name(libusb_device *dev)
{
    char product[BUFSIZ] = {0};
    libusb_device_descriptor desc = {};
    std::string result;

    (void)::libusb_get_device_descriptor(dev, &desc);

    int bus = ::libusb_get_bus_number(dev);
    int addr = ::libusb_get_device_address(dev);
    int ret =
        get_sysfs_attribute(bus, addr, "product", product, BUFSIZ);
    if (ret < 0) {
        printf(
            "get device product string failed, use Unkown string replace,"
            "bus=%d addr=%d pvid=%04x:%04x\n",
            bus, addr, desc.idVendor, desc.idProduct);
        result = "Unknown";
        goto out;
    }
    for (int i = 0; i < BUFSIZ; i++) {
        if (product[i] == '\n') {
            product[i] = '\0';
            break;
        }
    }
    result = (const char *)product;

out:
    return result;
}


int main(int argc, char* argv[])
{
    libusb_device **devs;
    libusb_device_handle *dev_handle;
    struct libusb_device_descriptor desc;
    int r, i;

    r = libusb_init(NULL);
    if (r < 0) {
        return r;
    }

    r = libusb_get_device_list(NULL, &devs);
    if (r < 0) {
        return r;
    }

    for (i = 0; devs[i]; i++) {
        std::string product_name = libusb_dev_get_product_name(devs[i]);
        printf("product name: %s\n\n", product_name.c_str());
    }

    libusb_free_device_list(devs, 1);
    libusb_exit(NULL);
    return 0;
}