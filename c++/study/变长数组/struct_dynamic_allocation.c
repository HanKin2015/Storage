/**
* 文 件 名: struct_dynamic_allocation.c
* 文件描述: 结构体动态分配
* 作    者: HanKin
* 创建日期: 2023.07.06
* 修改日期：2023.07.06
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <assert.h>
#define ID_LEN 16
#pragma pack(1)

// 4+1+4=9
struct bulk_cache_list_param {
    uint32_t endpoint;
    uint8_t no_transfers;
    uint32_t bytes_per_transfer;
};
struct usbredirhost_bulk_cache_list_item {
    char id[ID_LEN];
    uint32_t quirk;
    struct bulk_cache_list_param *param;
    uint8_t param_count;
};

// 4+8+1=13
struct usb_redir_extend_bulk_cache_packet {
    uint32_t quirk;
    struct bulk_cache_list_param *param;
    uint8_t param_count;
};

void send_packet(uint8_t *data, int data_len)
{
    int i = 0;
    for (i = 0; i < data_len; i++) {
        printf("hejian %d: %02x\n", i, data[i]);
    }
            
    struct usb_redir_extend_bulk_cache_packet bulk_cache_info;
    bulk_cache_info = *(struct usb_redir_extend_bulk_cache_packet *)data;
    printf("hejian data_len %d, quirk %d param_count %d\n", data_len,
        bulk_cache_info.quirk, bulk_cache_info.param_count);
        
    printf("param endpoint %02x\n", bulk_cache_info.param[0].endpoint);
    return;
}

// 定义一个不是指针的
struct usb_redir_extend_bulk_cache_packet_ {
    uint32_t quirk;
    struct bulk_cache_list_param param;
    uint8_t param_count;
};

int main()
{
    struct usbredirhost_bulk_cache_list_item info;
    info.param_count = 1;
    info.param = (struct bulk_cache_list_param *)calloc(info.param_count, sizeof(struct bulk_cache_list_param));
    const char *vpid = "0b95:772b";
    memcpy(info.id, vpid, strlen(vpid));
    info.quirk = 2;
    info.param[0].endpoint = 0x82;
    info.param[0].no_transfers = 15;
    info.param[0].bytes_per_transfer = 8192;

    struct usb_redir_extend_bulk_cache_packet bulk_cache_packet = { 0 };
    bulk_cache_packet.quirk = info.quirk;
    bulk_cache_packet.param = info.param;
    bulk_cache_packet.param_count = info.param_count;

    printf("%lu %lu %lu\n", sizeof(bulk_cache_packet), sizeof(struct usb_redir_extend_bulk_cache_packet), sizeof(struct bulk_cache_list_param));
    send_packet((uint8_t *)&bulk_cache_packet, 14);
    
    struct usb_redir_extend_bulk_cache_packet_ hj = { 0 };
    hj.quirk = info.quirk;
    hj.param.endpoint = 0x82;
    hj.param.no_transfers = 15;
    hj.param.bytes_per_transfer = 8192;
    hj.param_count = info.param_count;
    send_packet((uint8_t *)&hj, sizeof(struct usb_redir_extend_bulk_cache_packet_));
    return 0;
}

