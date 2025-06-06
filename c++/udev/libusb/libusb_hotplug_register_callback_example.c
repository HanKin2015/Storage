/*******************************************************************************
* 文 件 名: libusb_hotplug_register_callback_example.cpp
* 文件描述: 用于注册热插拔回调函数，以便在 USB 设备插入或拔出时接收通知
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.06.04
* 修改日期：2025.06.04
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <libusb-1.0/libusb.h>

int hotplug_callback(libusb_context *ctx, struct libusb_device *dev, libusb_hotplug_event event, void *user_data)
{
    struct libusb_device_descriptor desc;
    libusb_get_device_descriptor(dev, &desc);

    if (event == LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED) {
        printf("Device connected: Vendor ID: %04x, Product ID: %04x\n", desc.idVendor, desc.idProduct);
    } else if (event == LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT) {
        printf("Device disconnected: Vendor ID: %04x, Product ID: %04x\n", desc.idVendor, desc.idProduct);
    }
    return 0;
}

int main()
{
    libusb_context *ctx = NULL;
    int r = libusb_init(&ctx);
    if (r < 0) {
        fprintf(stderr, "Failed to initialize libusb\n");
        return 1;
    }

    // 注册热插拔回调
    libusb_hotplug_callback_handle handle;
    r = libusb_hotplug_register_callback(ctx,
                                          LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED | LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT,
                                          LIBUSB_HOTPLUG_NO_FLAGS,
                                          LIBUSB_HOTPLUG_MATCH_ANY,  // 监视所有供应商
                                          LIBUSB_HOTPLUG_MATCH_ANY,  // 监视所有产品
                                          LIBUSB_HOTPLUG_MATCH_ANY,  // 监视所有设备类
                                          hotplug_callback,
                                          NULL,  // 用户数据
                                          (libusb_hotplug_callback_handle *)&handle);
    if (r != LIBUSB_SUCCESS) {
        fprintf(stderr, "Failed to register hotplug callback\n");
        libusb_exit(ctx);
        return 1;
    }

    // 进入事件循环
    while (1) {
        libusb_handle_events_completed(ctx, NULL);
    }

    // 清理
    libusb_hotplug_deregister_callback(ctx, handle);
    libusb_exit(ctx);
    return 0;
}
/*
root@hankin:/home# ./a.out
Device connected: Vendor ID: 0951, Product ID: 1666
Device disconnected: Vendor ID: 0951, Product ID: 1666
Device connected: Vendor ID: 0951, Product ID: 1666
Device disconnected: Vendor ID: 0951, Product ID: 1666

LIBUSB_HOTPLUG_ENUMERATE：意味着当前已经插入设备，会调用回调
root@hankin:/home# ./a.out
Device connected: Vendor ID: 1a81, Product ID: 203e
Device connected: Vendor ID: 1a81, Product ID: 223a
Device connected: Vendor ID: 0438, Product ID: 7900
Device connected: Vendor ID: 1d6b, Product ID: 0002
Device connected: Vendor ID: 0438, Product ID: 7900
Device connected: Vendor ID: 1d6b, Product ID: 0002
Device connected: Vendor ID: 1d6b, Product ID: 0003
Device connected: Vendor ID: 1d6b, Product ID: 0002
*/