/*******************************************************************************
* 文 件 名: main.cpp
* 文件描述: 
* 备    注: g++ main.cpp -std=c++11
* 作    者: HanKin
* 创建日期: 2025.04.16
* 修改日期：2025.04.16
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstdio>
#include "class.h"

void spice_cb(void *priv, uint8_t *data, int32_t length)
{
    printf("%d:%s\n", __LINE__, __FUNCTION__);
    printf("spice recv: %s\n", (char *)data);
}

void rdp_cb(void *priv, uint8_t *data, int32_t length)
{
    printf("%d:%s\n", __LINE__, __FUNCTION__);
    printf("rdp recv: %s\n", (char *)data);
}

int main()
{
    IUsbDeviceChannel *usbredir_channel = new UsbRedirChannel();
    IUsbDeviceChannel *usbvideo_channel = new UsbVideoChannel();

    usbredir_channel->set_write_cb(spice_cb);
    usbvideo_channel->set_write_cb(rdp_cb);

    usbredir_channel->execute_callback();
    usbvideo_channel->execute_callback();

    delete usbredir_channel;
    usbredir_channel = NULL;
    delete usbvideo_channel;
    usbvideo_channel = NULL;
    return 0;
}
