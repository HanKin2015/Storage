/**
* 文 件 名: char2struct.cpp
* 文件描述: char数据转换成struct
* 作    者: HanKin
* 创建日期: 2023.07.12
* 修改日期：2023.07.12
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
//#pragma pack(1)

#define ID_LEN 16

// 4 1 4
struct bulk_cache_list_param {
    uint32_t endpoint;
    uint8_t no_transfers;
    uint32_t bytes_per_transfer;
};
struct usb_redir_extend_bulk_cache_packet {
    uint32_t quirk;
    uint8_t param_count;
    struct bulk_cache_list_param param[0];
};

// 16 4 1
struct usbredirhost_bulk_cache_list_item {
    char id[ID_LEN];
    uint32_t quirk;
    uint8_t param_count;
    struct bulk_cache_list_param param[0];
};

#define BULK_CACHE_LIST_ITEM_SIZE(_x) \
    ((sizeof(struct usbredirhost_bulk_cache_list_item)) + \
     ((_x)->param_count * sizeof(struct bulk_cache_list_param)))
#define BULK_CACHE_LIST_ITEM_NEXT(_x) \
    ((char *)(_x) + BULK_CACHE_LIST_ITEM_SIZE(_x))

static void usbredirparser_send_extend_init_packet(uint8_t *data, int data_len)
{
    int i;
    for (i = 0; i < data_len; i++) {
        printf("hejian data[%d] = %d\n", i, data[i]);
    }
    return;
}

int main(int argc, char *argv[])
{
    int bulk_cache_packet_size = 17;
    struct usb_redir_extend_bulk_cache_packet *bulk_cache_packet = (struct usb_redir_extend_bulk_cache_packet *)calloc(1, bulk_cache_packet_size);
    bulk_cache_packet->quirk = 2;
    bulk_cache_packet->param_count = 1;
    bulk_cache_packet->param[0].endpoint = 0x82;
    bulk_cache_packet->param[0].no_transfers = 15;
    bulk_cache_packet->param[0].bytes_per_transfer = 8192;
    
    usbredirparser_send_extend_init_packet((uint8_t *)bulk_cache_packet, bulk_cache_packet_size);
    
    int tmp = BULK_CACHE_LIST_ITEM_SIZE(bulk_cache_packet);
    printf("size %d\n", tmp);
    
    uint8_t data[17] = {2, 0, 0, 0, 1, 130, 0, 0, 0, 15, 0, 32, 0, 0, 0, 0, 0};
    int data_len = 17;
    struct usb_redir_extend_bulk_cache_packet *bulk_cache_info = (struct usb_redir_extend_bulk_cache_packet *)calloc(1, data_len);
    if (bulk_cache_info == NULL) {
        printf("bulk_cache_info calloc failed, data_len %d\n", data_len);
        return -1;
    }
    memcpy(bulk_cache_info, data, data_len);
    printf("data_len %d quirk %d param_count %d\n", data_len,
        bulk_cache_info->quirk, bulk_cache_info->param_count);
    printf("ep 0x%02x\n", bulk_cache_info->param[0].endpoint);
    
    
    
    
    
    printf("%d %d\n", sizeof(struct usbredirhost_bulk_cache_list_item), sizeof(struct bulk_cache_list_param));
    
    
    
    return 0;
}
/*
sizeof(long) 8 sizeof(long int) 8 sizeof(long long) 8
sizeof(NODE) 48 sizeof(q) 48
addr 0x7fffe2217020, token 7
qh.token 0
q.epchar 2 q.epcap 3
qh.epchar 2 qh.epcap 3
qh.token 7
next = 11
other = 8589934603, calc1 = 47244640258, calc2 = 8589934603
qh.next = 11
*/
