/**
* 文 件 名: control_packet_transfer.cpp
* 文件描述: 通过下发控制包数据来获取设备信息
* 作    者: HanKin
* 备    注: 编译需要安装libusb库, 并且需要增加-lusb-1.0参数
* 创建日期: 2024.08.22
* 修改日期：2024.08.22
*
* Copyright (c) 2024 HanKin. All rights reserved.
*/

#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>

#define READ_LE16(p) ((uint16_t)    \
    (((uint16_t)((p)[1]) << 8) |    \
     ((uint16_t)((p)[0]))))

#define READ_LE32(p) ((uint32_t)    \
    (((uint32_t)((p)[3]) << 24) |   \
     ((uint32_t)((p)[2]) << 16) |   \
     ((uint32_t)((p)[1]) <<  8) |   \
     ((uint32_t)((p)[0]))))
// 这里面用到了c++语法
static void parse_descriptor(const void *source, const char *descriptor, void *dest)
{
    const uint8_t *sp = reinterpret_cast<const uint8_t *>(source);
    uint8_t *dp = reinterpret_cast<uint8_t *>(dest);
    char field_type;

    while (*descriptor) {
        field_type = *descriptor++;
        switch (field_type) {
        case 'b':   /* 8-bit byte */
            *dp++ = *sp++;
            break;
        case 'w':   /* 16-bit word, convert from little endian to CPU */
            dp += ((uintptr_t)dp & 1);  /* Align to 16-bit word boundary */

            *((uint16_t *)dp) = READ_LE16(sp);
            sp += 2;
            dp += 2;
            break;
        case 'd':   /* 32-bit word, convert from little endian to CPU */
            dp += 4 - ((uintptr_t)dp & 3);  /* Align to 32-bit word boundary */

            *((uint32_t *)dp) = READ_LE32(sp);
            sp += 4;
            dp += 4;
            break;
        case 'u':   /* 16 byte UUID */
            memcpy(dp, sp, 16);
            sp += 16;
            dp += 16;
            break;
        }
    }
}

int main(int argc, char *argv[])
{
    libusb_context *ctx = NULL;
    int result = libusb_init(&ctx);
    assert(result >= 0);
    
    // 通过libusb_open_device_with_vid_pid函数
    uint16_t vid = 0x0409;
    uint16_t pid = 0x55aa;
    libusb_device_handle *dev_handle = libusb_open_device_with_vid_pid(NULL, vid, pid);
    assert(dev_handle);
    
    // 填充设备描述符请求控制包(这一步也完全是多余的)
    libusb_control_setup *setup = NULL;
    setup = (libusb_control_setup *)malloc(sizeof(libusb_control_setup));
	setup->bmRequestType = LIBUSB_ENDPOINT_IN;					// 80(bitmask)
	setup->bRequest = LIBUSB_REQUEST_GET_DESCRIPTOR;			// 06
	setup->wValue = (uint16_t)((LIBUSB_DT_DEVICE << 8) | 0);	// 0100
	setup->wIndex = 0;											// 0000
	setup->wLength = (uint16_t)LIBUSB_DT_DEVICE_SIZE;			// 0012
    
    // 传输控制包请求获取设备描述符信息
    uint32_t timeout = 1000;
    uint8_t device_desc_data[LIBUSB_DT_DEVICE_SIZE] = { 0 };
    int r = LIBUSB_ERROR_NOT_SUPPORTED;
    r = libusb_control_transfer(dev_handle, LIBUSB_ENDPOINT_IN, LIBUSB_REQUEST_GET_DESCRIPTOR, ((LIBUSB_DT_DEVICE << 8) | 0), 0, device_desc_data, LIBUSB_DT_DEVICE_SIZE, timeout);
    r = libusb_control_transfer(dev_handle, LIBUSB_ENDPOINT_IN, LIBUSB_REQUEST_GET_DESCRIPTOR, ((LIBUSB_DT_DEVICE << 8) | 0), 0, device_desc_data, LIBUSB_DT_DEVICE_SIZE, timeout);
    if (r == 0) {
        printf("zero bytes returned in ctrl transfer?\n");
        return -1;
    }
    printf("r = %d, %s\n", r, libusb_error_name(r));  // 返回正数是获取的数据长度，返回负数则是错误码
    struct libusb_device_descriptor device_desc;
    parse_descriptor(device_desc_data, "bbwbbbbww", &device_desc);  // 18
    printf("Found device: %04x:%04x\n", device_desc.idVendor, device_desc.idProduct);
    printf("bcdUSB : %04x bDeviceClass : %d\n", device_desc.bcdUSB, device_desc.bDeviceClass);
    
    // 传输控制包请求获取配置描述符信息(我的理解其实一次获取配置描述符也是能获取成功，只不过长度是不固定的，所以需要获取两次)
    // 出现过一次控制请求数据包为80 06 0201 0000 0009
    uint8_t config_desc_data[LIBUSB_DT_CONFIG_SIZE] = { 0 };
    uint16_t wValue = 0x0201;
    r = libusb_control_transfer(dev_handle, LIBUSB_ENDPOINT_IN, LIBUSB_REQUEST_GET_DESCRIPTOR, wValue, 0, config_desc_data, LIBUSB_DT_CONFIG_SIZE, timeout);
    if (r == 0) {
        printf("zero bytes returned in ctrl transfer?\n");
        return -1;
    }
    printf("wValue %04x, r = %d, %s\n", wValue, r, libusb_error_name(r));  // 返回正数是获取的数据长度，返回负数则是错误码
    struct libusb_config_descriptor config_desc;
    parse_descriptor(config_desc_data, "bbwbbbbb", &config_desc);   // 9
    printf("wTotalLength: %04x bNumInterfaces %02x bConfigurationValue %02x\n", config_desc.wTotalLength,
    config_desc.bNumInterfaces, config_desc.bConfigurationValue);
    
    uint8_t *data = (uint8_t *)malloc(config_desc.wTotalLength);
    r = libusb_control_transfer(dev_handle, LIBUSB_ENDPOINT_IN, LIBUSB_REQUEST_GET_DESCRIPTOR, ((LIBUSB_DT_CONFIG << 8) | 0), 0, data, config_desc.wTotalLength, timeout);
    if (r == 0) {
        printf("zero bytes returned in ctrl transfer?\n");
        return -1;
    }
    printf("r = %d, %s\n", r, libusb_error_name(r));  // 返回正数是获取的数据长度，返回负数则是错误码
    printf("get config descriptor success!\n");
    for (int i = 0; i < r; i++) {
        printf("%02x%c", data[i], i == r - 1 ? '\n' : ' ');
    }
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #g++ a.cpp -lusb-1.0
[root@ubuntu0006:~/cmake] #./a.out
r = 18, **UNKNOWN**
Found device: 0409:55aa
bcdUSB : 0110 bDeviceClass : 9
r = 9, **UNKNOWN**
wTotalLength: 0019 bNumInterfaces 01 bConfigurationValue 01
r = 25, **UNKNOWN**
get config descriptor success!
09 02 19 00 01 01 00 e0 00 09 04 00 00 01 09 00 00 00 07 05 81 03 02 00 ff
[root@ubuntu0006:~/cmake] #vi a.cpp 改成0x0201请求码
[root@ubuntu0006:~/cmake] #g++ a.cpp -lusb-1.0
[root@ubuntu0006:~/cmake] #./a.out
r = 18, **UNKNOWN**
Found device: 0409:55aa
bcdUSB : 0110 bDeviceClass : 9
r = -9, LIBUSB_ERROR_PIPE
wTotalLength: 0000 bNumInterfaces 00 bConfigurationValue 00
zero bytes returned in ctrl transfer?

root@hankin:~# ./a.out U盘使用0x0201请求码获取成功了，Windows上面也是成功
r = 18, **UNKNOWN**
Found device: 0951:1666
bcdUSB : 0210 bDeviceClass : 0
r = 9, **UNKNOWN**
wTotalLength: 0020 bNumInterfaces 01 bConfigurationValue 01
r = 32, **UNKNOWN**
get config descriptor success!
09 02 20 00 01 01 00 80 96 09 04 00 00 02 08 06 50 00 07 05 81 02 00 02 ff 07 05 02 02 00 02 ff

*/