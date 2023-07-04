/**
* 文 件 名: struct_convert.cpp
* 文件描述: 结构体转换
* 作    者: HanKin
* 创建日期: 2023.06.28
* 修改日期：2023.06.28
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#include <cstdlib>
#include <inttypes.h>
using namespace std;

struct usb_redir_extend_bulk_cache_packet {
    uint32_t quirk;
    uint32_t endpoint;
    uint32_t bytes_per_transfer;
};

void struct_convert(uint8_t *data, int data_len)
{
    struct usb_redir_extend_bulk_cache_packet bulk_cache_packet = *(struct usb_redir_extend_bulk_cache_packet *)data;
    printf("data_len %d quirk %d ep %02x bytes_per_transfer %d\n", data_len, bulk_cache_packet.quirk,
        bulk_cache_packet.endpoint, bulk_cache_packet.bytes_per_transfer);
    return;
}

int main(int argc, char *argv[])
{
    struct usb_redir_extend_bulk_cache_packet bulk_cache_packet = { 0 };
    bulk_cache_packet.quirk = 2;
    bulk_cache_packet.endpoint = 0x82;
    bulk_cache_packet.bytes_per_transfer = 4096;
    
    struct_convert((uint8_t *)&bulk_cache_packet, sizeof(bulk_cache_packet));
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
data_len 12 quirk 2 ep 82 bytes_per_transfer 4096
*/