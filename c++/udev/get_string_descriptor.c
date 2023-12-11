/*******************************************************************************
* 文 件 名: get_string_descriptor.c
* 文件描述: 获取字符串描述符
* 备    注: 编译需要安装libusb库,并且需要增加-lusb-1.0参数
* 作    者: HanKin
* 创建日期: 2023.10.20
* 修改日期：2023.10.20
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <sys/stat.h>

int libusb_get_string_descriptor_ascii_(libusb_device_handle *dev,
    uint8_t desc_index, unsigned char *data, int length)
{
    unsigned char tbuf[255];
    int r, si, di;
    uint16_t langid;

    if (desc_index == 0)
        return LIBUSB_ERROR_INVALID_PARAM;
    
    r = libusb_get_string_descriptor(dev, 0, 0, tbuf, sizeof(tbuf));
    if (r < 0)
        return r;
    
    if (r < 4)
        return LIBUSB_ERROR_IO;
    printf("langid: ");
    for (int i = 0; i < r; i++) {
        printf("%02x ", tbuf[i]);
    }
    printf("\n");

    langid = tbuf[2] | (tbuf[3] << 8);
    
    r = libusb_get_string_descriptor(dev, desc_index, langid, tbuf,
        sizeof(tbuf));
    if (r < 0)
        return r;
    
    if (tbuf[1] != LIBUSB_DT_STRING)
        return LIBUSB_ERROR_IO;
    
    if (tbuf[0] > r)
        return LIBUSB_ERROR_IO;
    
    printf("tbuf[0] tbuf[1] %02x %02x\n", tbuf[0], tbuf[1]);
    
    // 字符串描述符前两个数据分别是不需要的长度和类型
    for (di = 0, si = 2; si < tbuf[0]; si += 2) {
        if (di >= (length - 1))
            break;
    
        if ((tbuf[si] & 0x80) || (tbuf[si + 1])) /* non-ASCII */
            data[di++] = '?';
        else
            data[di++] = tbuf[si];
    }
    
    data[di] = 0;
    return di;
}

/*
 * 数型字符串描述符转换为ASCII格式
 * @param [in]libusb_device  usb设备对象
 * @return 无
 * @remark 字符串描述符数据高字节一般是00, 转换时舍去即可
 */
static int get_device_name(libusb_device* dev)
{
    int address = libusb_get_device_address(dev);
    int bus = libusb_get_bus_number(dev);
    printf("bus-address: %d-%d\n", bus, address);
    
    char dev_name[256] = { 0 };
    char filename[256] = { 0 };
    struct stat stat_buf;
    snprintf(filename, sizeof(filename), "/dev/bus/usb/%03d/%03d", bus, address);
    printf("filename: %s\n", filename);
    if (stat((const char *)filename, &stat_buf) != 0) {
        printf("stat error failed, filename:%s\n", filename);
        return -1;
    }
    // st_dev：表示文件所在的设备的ID     st_rdev：如果文件是特殊设备文件，则表示设备的ID
    printf("dev %d rdev %d\n", stat_buf.st_dev, stat_buf.st_rdev);
    
    snprintf(filename, sizeof(filename), "/sys/dev/char/%d:%d/%s",
        major(stat_buf.st_rdev), minor(stat_buf.st_rdev), "product");
    printf("filename: %s\n", filename);
    // 我才发现原来是这样找到usb设备的pci地址的，但是这种去找usb设备的字符串描述符的字符串是愚蠢的
    return 0;
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
        r = libusb_get_device_descriptor(devs[i], &desc);
        if (r < 0) {
            continue;
        }

        // 以一个hub为例
        if (desc.idVendor == 0x0409 && desc.idProduct == 0x55aa) {
            r = libusb_open(devs[i], &dev_handle);
            if (r < 0) {
                continue;
            }

            printf("Found device: %04x:%04x\n", desc.idVendor, desc.idProduct);
            printf("bcdUSB : %d bDeviceClass : %d\n", desc.bcdUSB, desc.bDeviceClass);

            // 获取字符串描述符
            int length = 256;
            unsigned char data[length] = { 0 };
            for (uint8_t desc_index = 0x01; desc_index < 0x05; desc_index++) {
                r = libusb_get_string_descriptor_ascii(dev_handle, desc_index, data, length);
                printf("desc_index %02x r = %d\n", desc_index, r);
                printf("data = %s\n", data);
                
                libusb_get_string_descriptor_ascii_(dev_handle, desc_index, data, length);
                (void)get_device_name(devs[i]);
            }
            libusb_close(dev_handle);
        }
    }

    libusb_free_device_list(devs, 1);
    libusb_exit(NULL);
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #g++ k.cpp -lusb-1.0
[root@ubuntu0006:~/cmake] #./a.out
Found device: 0409:55aa
bcdUSB : 272 bDeviceClass : 9
desc_index 01 r = 7
data = SANGFOR
langid: 04 03 09 04
tbuf[0] tbuf[1] 10 03
bus-address: 3-2
filename: /dev/bus/usb/003/002
dev 6 rdev 1096961
filename: /sys/dev/char/189:257/product
desc_index 02 r = 15
data = SANGFOR USB Hub
langid: 04 03 09 04
tbuf[0] tbuf[1] 20 03
bus-address: 3-2
filename: /dev/bus/usb/003/002
dev 6 rdev 1096961
filename: /sys/dev/char/189:257/product
desc_index 03 r = 21
data = 314159-0000:00:01.2-1
langid: 04 03 09 04
tbuf[0] tbuf[1] 2c 03
bus-address: 3-2
filename: /dev/bus/usb/003/002
dev 6 rdev 1096961
filename: /sys/dev/char/189:257/product
desc_index 04 r = -1
data = 314159-0000:00:01.2-1
langid: 04 03 09 04
bus-address: 3-2
filename: /dev/bus/usb/003/002
dev 6 rdev 1096961
filename: /sys/dev/char/189:257/product
*/