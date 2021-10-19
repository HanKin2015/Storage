/**
* 文 件 名: study_libusb.cpp
* 文件描述: 学习libusb
* 作    者: HanKin
* 备    注: 编译需要安装libusb库,并且需要增加-lusb-1.0 -lpthread -lm参数
* 创建日期: 2021.10.12
* 修改日期：2021.10.12
*
* Copyright (c) 2021 HanKin. All rights reserved.
*/

#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <sys/types.h>

#if 0
enum libusb_speed {
    /** The OS doesn't report or know the device speed. */
    LIBUSB_SPEED_UNKNOWN = 0,

    /** The device is operating at low speed (1.5MBit/s). */
    LIBUSB_SPEED_LOW = 1,

    /** The device is operating at full speed (12MBit/s). */
    LIBUSB_SPEED_FULL = 2,

    /** The device is operating at high speed (480MBit/s). */
    LIBUSB_SPEED_HIGH = 3,

    /** The device is operating at super speed (5000MBit/s). */
    LIBUSB_SPEED_SUPER = 4,

    /** The device is operating at super speed plus (10000MBit/s). */
    LIBUSB_SPEED_SUPER_PLUS = 5
};

/** \ingroup libusb_desc
 * Device and/or Interface Class codes */
enum libusb_class_code {
    /** In the context of a \ref libusb_device_descriptor "device descriptor",
     * this bDeviceClass value indicates that each interface specifies its
     * own class information and all interfaces operate independently.
     */
    LIBUSB_CLASS_PER_INTERFACE = 0x00,

    /** Audio class */
    LIBUSB_CLASS_AUDIO = 0x01,

    /** Communications class */
    LIBUSB_CLASS_COMM = 0x02,

    /** Human Interface Device class */
    LIBUSB_CLASS_HID = 0x03,

    /** Physical */
    LIBUSB_CLASS_PHYSICAL = 0x05,

    /** Image class */
    LIBUSB_CLASS_IMAGE = 0x06,
    LIBUSB_CLASS_PTP = 0x06, /* legacy name from libusb-0.1 usb.h */

    /** Printer class */
    LIBUSB_CLASS_PRINTER = 0x07,

    /** Mass storage class */
    LIBUSB_CLASS_MASS_STORAGE = 0x08,

    /** Hub class */
    LIBUSB_CLASS_HUB = 0x09,

    /** Data class */
    LIBUSB_CLASS_DATA = 0x0a,

    /** Smart Card */
    LIBUSB_CLASS_SMART_CARD = 0x0b,

    /** Content Security */
    LIBUSB_CLASS_CONTENT_SECURITY = 0x0d,

    /** Video */
    LIBUSB_CLASS_VIDEO = 0x0e,

    /** Personal Healthcare */
    LIBUSB_CLASS_PERSONAL_HEALTHCARE = 0x0f,

    /** Diagnostic Device */
    LIBUSB_CLASS_DIAGNOSTIC_DEVICE = 0xdc,

    /** Wireless class */
    LIBUSB_CLASS_WIRELESS = 0xe0,

    /** Miscellaneous class */
    LIBUSB_CLASS_MISCELLANEOUS = 0xef,

    /** Application class */
    LIBUSB_CLASS_APPLICATION = 0xfe,

    /** Class is vendor-specific */
    LIBUSB_CLASS_VENDOR_SPEC = 0xff
};
#endif

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

        printf("%04x:%04x (bus %d, port %d, device %d, speed %d, class 0x%x)\n",
            desc.idVendor, desc.idProduct, libusb_get_bus_number(dev), 
            libusb_get_port_number(dev), libusb_get_device_address(dev), 
            libusb_get_device_speed(dev), desc.bDeviceClass);
            
        // 
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