/**
* 文 件 名: libusb_introduction.h
* 文件描述: 头文件
* 作    者: HanKin
* 创建日期: 2023.07.20
* 修改日期：2023.07.20
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#ifndef LIBUSB_INTRODUCTION_H
#define LIBUSB_INTRODUCTION_H

#include <libusb-1.0/libusb.h>

typedef struct USBDEV
{
    libusb_device_handle* handle;   /* 通过libusb_open或者libusb_open_device_with_vid_pid */
    uint8_t endpoint_in;   /* in 端点*/
    uint8_t endpoint_out;  /* out 端点 */
    uint8_t bulk_interface;/* 接口号 */
    int nb_ifaces;         /* 接口数量 */
} USBDEV_T, PUSBDEV_T*;


class LibusbIntroduction
{
private:
    USBDEV_T m_usbdev;
    uint16_t m_vid; /* VID */
    uint16_t m_pid; /* PID */

    int get_interface_attr(libusb_device_handle* handle);

    void init();
    void exit();
    
public:
    LibusbIntroduction();
    ~LibusbIntroduction();

    void set_vid_pid(uint16_t vid, uint16_t pid);
    int bulkusb_write(void* buffer, int len, int ms);
    int bulkusb_read(void* buffer, int len, int ms);
    int control_write( uint8_t bRequest, void *data, int len, int ms);
    int control_read(uint8_t bRequest, void **data, int len, int ms);
};

#endif // LIBUSB_INTRODUCTION_H
