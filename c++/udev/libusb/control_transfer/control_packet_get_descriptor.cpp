/**
* 文 件 名: control_packet_get_descriptor.cpp
* 文件描述: 通过下发控制包数据来获取配置描述符，同理参考可以获取其他描述符信息
* 作    者: HanKin
* 备    注: 编译需要安装libusb库,并且需要增加-lusb-1.0参数
* 创建日期: 2023.07.05
* 修改日期：2023.07.05
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <assert.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>

#define USB_VENDOR_ID  0x1d6b
#define USB_PRODUCT_ID 0x0003

#define READ_LE16(p) ((uint16_t)    \
    (((uint16_t)((p)[1]) << 8) |    \
     ((uint16_t)((p)[0]))))

#define READ_LE32(p) ((uint32_t)    \
    (((uint32_t)((p)[3]) << 24) |   \
     ((uint32_t)((p)[2]) << 16) |   \
     ((uint32_t)((p)[1]) <<  8) |   \
     ((uint32_t)((p)[0]))))

#define DEVICE_CTX(dev) ((dev)->ctx)
#define HANDLE_CTX(handle) (DEVICE_CTX((handle)->dev))

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

/*
libusb_get_descriptor 调用
libusb_control_transfer 调用
libusb_fill_control_setup众多函数
*/
static void get_descriptor()
{
    libusb_context *ctx = NULL;
    int result = libusb_init(&ctx);
    assert(result >= 0);
    
    // 通过libusb_open_device_with_vid_pid函数
    libusb_device_handle *dev_handle = libusb_open_device_with_vid_pid(NULL, USB_VENDOR_ID, USB_PRODUCT_ID);
    assert(dev_handle);
    
    // 获取设备描述符
    struct libusb_device_descriptor desc;
    uint8_t device_header[LIBUSB_DT_DEVICE_SIZE] = {0};
    //result = libusb_get_descriptor(dev_handle, LIBUSB_DT_DEVICE, 0, device_header, LIBUSB_DT_DEVICE_SIZE);
    result = libusb_control_transfer(dev_handle, LIBUSB_ENDPOINT_IN, LIBUSB_REQUEST_GET_DESCRIPTOR,
        (uint16_t)((LIBUSB_DT_DEVICE << 8) | 0), 0, device_header, (uint16_t)LIBUSB_DT_DEVICE_SIZE, 1000);
    assert(result >= LIBUSB_DT_DEVICE_SIZE);
    parse_descriptor(device_header, "bbwbbbbww", &desc);
    printf("Found device: %04x:%04x\n", desc.idVendor, desc.idProduct);
    printf("bcdUSB : %d bDeviceClass : %d\n", desc.bcdUSB, desc.bDeviceClass);
    
    libusb_exit(ctx);
    return;
}

// 做了修改，无法获取libusb_context，直接使用NULL
static void sync_transfer_wait_for_completion(struct libusb_transfer *transfer)
{
    int r, *completed = reinterpret_cast<int *>(transfer->user_data);
    //struct libusb_context *ctx = HANDLE_CTX(transfer->dev_handle);

    while (!*completed) {
        r = libusb_handle_events_completed(NULL, completed);
        if (r < 0) {
            if (r == LIBUSB_ERROR_INTERRUPTED)
                continue;
            printf("libusb_handle_events failed: %s, cancelling transfer and retrying",
                 libusb_error_name(r));
            libusb_cancel_transfer(transfer);
            continue;
        }
    }
}

static void LIBUSB_CALL sync_transfer_cb(struct libusb_transfer *transfer)
{
    int *completed = reinterpret_cast<int *>(transfer->user_data);
    *completed = 1;
    printf("actual_length = %d\n", transfer->actual_length);
    /* caller interprets result and frees transfer */
}

/*
ffff8800595ca040 1125484244 C Ci:1:068:0 0 9 = 09024200 020100c0 fa
ffff8800595ca040 1125484255 S Ci:1:068:0 s 80 06 0200 0000 0042 66 <
ffff8800595ca040 1125484619 C Ci:1:068:0 0 66 = 09024200 020100c0 fa090400 00020300 00000921 10010001 221b0007 05840320
ffff88005957a640 1125484633 S Ci:1:068:0 s 80 06 0300 0000 00ff 255 <
ffff88005957a640 1125484855 C Ci:1:068:0 0 4 = 04030904
ffff88005957a640 1125484867 S Ci:1:068:0 s 80 06 0302 0409 00ff 255 <
ffff88005957a640 1125485140 C Ci:1:068:0 0 42 = 2a035300 53003700 32003800 4d003000 35002000 43006100 72006400 20005200
ffff88005957a640 1125485152 S Ci:1:068:0 s 80 06 0301 0409 00ff 255 <
ffff88005957a640 1125485421 C Ci:1:068:0 0 40 = 28035300 44005300 45005300 30003000 30003000 31005600 65007200 30003000
ffff88005957a640 1125485433 S Ci:1:068:0 s 80 06 0302 0409 00ff 255 <
ffff88005957a640 1125485699 C Ci:1:068:0 0 42 = 2a035300 53003700 32003800 4d003000 35002000 43006100 72006400 20005200
*/
static int control_packet_get_descriptor()
{
    libusb_context *ctx = NULL;
    int result = libusb_init(&ctx);
    assert(result >= 0);
    
    // 通过libusb_open_device_with_vid_pid函数
    libusb_device_handle *dev_handle = libusb_open_device_with_vid_pid(NULL, USB_VENDOR_ID, USB_PRODUCT_ID);
    assert(dev_handle);
    
    // 通过控制包
    uint8_t  bmRequestType = LIBUSB_ENDPOINT_IN;                        // 80
    uint8_t  bRequest      = LIBUSB_REQUEST_GET_DESCRIPTOR;             // 06
    uint16_t wValue        = (uint16_t)((LIBUSB_DT_DEVICE << 8) | 0);   // 0100
    uint16_t wIndex        = 0;                                         // 0000
    uint16_t wLength       = (uint16_t)LIBUSB_DT_DEVICE_SIZE;           // 0012
    
    uint8_t data[LIBUSB_DT_DEVICE_SIZE] = {0};
    unsigned int timeout = 1000;
    
    struct libusb_transfer *transfer = libusb_alloc_transfer(0);
    assert(transfer);
    
    unsigned char *buffer;
    int completed = 0;
    int r;
    
    buffer = (unsigned char*) malloc(LIBUSB_CONTROL_SETUP_SIZE + wLength);
    if (!buffer) {
        libusb_free_transfer(transfer);
        return LIBUSB_ERROR_NO_MEM;
    }

    libusb_fill_control_setup(buffer, bmRequestType, bRequest, wValue, wIndex,
        wLength);
    if ((bmRequestType & LIBUSB_ENDPOINT_DIR_MASK) == LIBUSB_ENDPOINT_OUT)
        memcpy(buffer + LIBUSB_CONTROL_SETUP_SIZE, data, wLength);

    libusb_fill_control_transfer(transfer, dev_handle, buffer,
            sync_transfer_cb, &completed, timeout);
    transfer->flags = LIBUSB_TRANSFER_FREE_BUFFER;
    r = libusb_submit_transfer(transfer);
    if (r < 0) {
        libusb_free_transfer(transfer);
        return r;
    }

    sync_transfer_wait_for_completion(transfer);

    if ((bmRequestType & LIBUSB_ENDPOINT_DIR_MASK) == LIBUSB_ENDPOINT_IN)
        memcpy(data, libusb_control_transfer_get_data(transfer),
            transfer->actual_length);

    switch (transfer->status) {
    case LIBUSB_TRANSFER_COMPLETED:
        r = transfer->actual_length;
        break;
    case LIBUSB_TRANSFER_TIMED_OUT:
        r = LIBUSB_ERROR_TIMEOUT;
        break;
    case LIBUSB_TRANSFER_STALL:
        r = LIBUSB_ERROR_PIPE;
        break;
    case LIBUSB_TRANSFER_NO_DEVICE:
        r = LIBUSB_ERROR_NO_DEVICE;
        break;
    case LIBUSB_TRANSFER_OVERFLOW:
        r = LIBUSB_ERROR_OVERFLOW;
        break;
    case LIBUSB_TRANSFER_ERROR:
    case LIBUSB_TRANSFER_CANCELLED:
        r = LIBUSB_ERROR_IO;
        break;
    default:
        printf("unrecognised status code %d", transfer->status);
        r = LIBUSB_ERROR_OTHER;
    }

    libusb_free_transfer(transfer);
    
    struct libusb_device_descriptor desc;
    parse_descriptor(data, "bbwbbbbww", &desc);
    printf("Found device: %04x:%04x\n", desc.idVendor, desc.idProduct);
    printf("bcdUSB : %04x bDeviceClass : %d\n", desc.bcdUSB, desc.bDeviceClass);
    
    libusb_exit(ctx);
    return r;
}

int main(int argc, char *argv[])
{
    control_packet_get_descriptor();
    return 0;
}