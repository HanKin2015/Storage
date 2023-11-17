/*******************************************************************************
* 文 件 名: get_string_descriptor_name.c
* 文件描述: 获取字符串描述符名称
* 作    者: HanKin
* 创建日期: 2023.11.16
* 修改日期：2023.11.16
*
* Copyright (c) 2023 HanKin. All rights reserved.
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
#include <sys/types.h>
#include <sys/stat.h>

void get_string_descriptor_name(uint16_t vid, uint16_t pid, uint8_t product_index)
{
    unsigned char dev_name[BUFSIZ];
    printf("%lu %lu\n", sizeof(dev_name), strlen(dev_name));  // 8192 0
    memset(dev_name, 0, sizeof(dev_name));
    int r = 0;
    libusb_device_handle *dev_handle = NULL;

    printf("[%04x:%04x] product_index %d\n", vid, pid, product_index);
    if (product_index == 0) {
        printf("device name is null!\n");
    } else {
        libusb_init(NULL);
        dev_handle = libusb_open_device_with_vid_pid(NULL, vid, pid);
        if (dev_handle == NULL) {
            printf("libusb_open_device_with_vid_pid failed\n");
            return;
        }
        
        //r = libusb_open(dev, &dev_handle);
        if (r < 0) {
            printf("libusb_open failed\n");
            return;
        }
        r = libusb_get_string_descriptor_ascii(dev_handle, product_index, dev_name, BUFSIZ);
        printf("dev_name: %s\n\n", dev_name);
        libusb_close(dev_handle);
        dev_handle = NULL;
    }
    return;
}

// 另外一种方法很戳，但是能做其他事情
int get_sysfs_attribute(int bus, int address, char *value, const char *string_index)
{
    struct stat stat_buf;
    FILE *fp = NULL;
    char filename[BUFSIZ];
    char data[BUFSIZ];
    int count = BUFSIZ;
    int read_len = 0;
    int data_len = 0;
    
    if (value == NULL) {
        printf("params error, attribute or value is null\n");
       	return -1;
    }
    
    snprintf(filename, sizeof(filename), "/dev/bus/usb/%03d/%03d", bus, address);
    printf("filename1: %s\n", filename);
    if (stat((const char *)filename, &stat_buf) != 0) {
        printf("stat error failed, filename:%s\n", filename);
        return -1;
    }
    snprintf(filename, sizeof(filename), "/sys/dev/char/%d:%d/%s", 
        major(stat_buf.st_rdev), minor(stat_buf.st_rdev), string_index);
    printf("filename2: %s\n", filename);
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("open %s failed\n", filename);
        return -1;
    }
    while (read_len < BUFSIZ) {
        data_len = fread(data, sizeof(char), count, fp);
       	if (ferror(fp) != 0) {
            printf("read file fail\n");
            fclose(fp);
            return -1;
        }
        memcpy(value + read_len, data, data_len);
        read_len += data_len;
        if (feof(fp)) {
            break;
        }
    }
    fclose(fp);
    return read_len;
}
void get_device_name(int bus, int address, const char *string_index)
{
    char dev_name[BUFSIZ];
    memset(dev_name, 0, sizeof(dev_name));
    int ret = get_sysfs_attribute(bus, address, dev_name, string_index);
    if (ret <= 0) {
        printf("device name is null!\n");
    } else {
        if (dev_name[ret-1] == '\n') {
            dev_name[ret-1] = '\0';
        }
        printf("%s = %s\n", string_index, dev_name);
    }
}

int main(int argc, char *argv[])
{
    get_string_descriptor_name(0x1d6b, 0x0003, 1);
    get_string_descriptor_name(0x1d6b, 0x0003, 2);
    get_string_descriptor_name(0x1d6b, 0x0003, 3);
    printf("\n\n");
    
    int ret = 0;
    
    libusb_context *context = NULL;
    libusb_init(&context);
    
    libusb_device **devs;
    int dev_cnt = (int)libusb_get_device_list(context, &devs);
    if (dev_cnt < 0 || devs == NULL) {
        printf("libusb get device list fail, error %d", dev_cnt);
        return -1;
    }
    for (int dev_idx = 0; dev_idx < dev_cnt; ++dev_idx) {
        struct libusb_device_descriptor dev_desc;
        ret = libusb_get_device_descriptor(devs[dev_idx], &dev_desc);
        if (ret < 0) {
            printf("failed to get device descriptor\n");
            continue;
        }
        int address = libusb_get_device_address(devs[dev_idx]);
        int bus = libusb_get_bus_number(devs[dev_idx]);
        printf("usb device(%04x:%04x):\n", dev_desc.idVendor, dev_desc.idProduct);
        (void)get_device_name(bus, address, "manufacturer");
        (void)get_device_name(bus, address, "product");
        (void)get_device_name(bus, address, "serial");
        printf("\n");
    }
    return 0;
}