/**
* 文 件 名: calc_asap_value.cpp
* 文件描述: 计算asap值，之前排查问题怀疑是这个值异常导致的问题，实际上不是
* 作    者: HanKin
* 创建日期: 2023.05.05
* 修改日期：2023.05.05
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <iostream>
#include <cstdio>
#include <inttypes.h>
using namespace std;

#define USB_TOKEN_IN    0x69 /* device -> host */
#define USB_TOKEN_OUT   0xe1 /* host -> device */

#define EP2I(ep_address) (((ep_address & 0x80) >> 3) | (ep_address & 0x0f))
#define USBEP2I(usb_ep) (((usb_ep)->pid == USB_TOKEN_IN) ? \
                         ((usb_ep)->nr | 0x10) : ((usb_ep)->nr))
#define I2USBEP(d, i) (usb_ep_get(&(d)->dev, \
                       ((i) & 0x10) ? USB_TOKEN_IN : USB_TOKEN_OUT, \
                       (i) & 0x0f))
                       
int main()
{
    uint64_t interval = 11, mfindex = 6171367;
    uint64_t asap = ((mfindex + interval - 1) &
                     ~(interval-1));
    printf("%lu\n", asap);
    printf("%02x\n", EP2I(0x82));
    printf("%02x\n", EP2I(0x81));
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
6171377
12
11
*/