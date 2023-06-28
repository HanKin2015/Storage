/**
* 文 件 名: and_or_not.cpp
* 文件描述: 与或非
* 作    者: HanKin
* 创建日期: 2023.06.27
* 修改日期：2023.06.27
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#include <cstdlib>
using namespace std;

/* In bulk endpoints are streaming data sources (iow behave like isoc eps) */
#define USB_QUIRK_BUFFER_BULK_IN        0x01
/* Bulk pkts in FTDI format, need special handling when combining packets */
#define USB_QUIRK_IS_FTDI               0x02
#define USB 0x4
#define HJ  0x8

int main(int argc, char *argv[])
{
    int quirks = 0;
    quirks |= USB_QUIRK_BUFFER_BULK_IN;
    printf("%d\n", quirks);
    quirks &= ~USB_QUIRK_BUFFER_BULK_IN;
    printf("%d\n", quirks);
    
    quirks |= USB_QUIRK_IS_FTDI;
    printf("%d\n", quirks);
    quirks &= ~USB_QUIRK_IS_FTDI;
    printf("%d\n", quirks);
    
    quirks |= USB_QUIRK_BUFFER_BULK_IN | USB_QUIRK_IS_FTDI | USB | HJ;
    printf("%d\n", quirks);
    quirks &= ~USB_QUIRK_IS_FTDI;
    printf("%d\n", quirks);
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
1
0
2
0
15
13
*/