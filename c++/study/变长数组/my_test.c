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

struct bulk_cache_list_param {
    uint32_t x;
    uint32_t y;
    uint32_t z;
};

struct usb_redir_extend_bulk_cache_packet {
    uint32_t m;
    struct bulk_cache_list_param *param;
    uint32_t n;
};

// 解决方式，0长数组
struct usb_redir_extend_bulk_cache_packet_ {
    char id[ID_LEN];
    uint32_t m;
    uint32_t n;
    uint32_t count;
    struct bulk_cache_list_param param[0];
};

struct usb_redir_extend_bulk_cache_packet__ {
    uint32_t m;
    uint32_t n;
    uint32_t count;
    struct bulk_cache_list_param param[0];
};

void send_packet(uint8_t *data, int data_len)
{
    int i = 0;
    for (i = 0; i < data_len; i++) {
        printf("hejian %d: %d\n", i, data[i]);
    }
    return;
}

int main()
{
    struct usb_redir_extend_bulk_cache_packet test = { 0 };
    test.m = 1;
    test.param = (struct bulk_cache_list_param *)calloc(1, sizeof(struct bulk_cache_list_param));
    test.param[0].x = 2;
    test.param[0].y = 3;
    test.param[0].z = 4;
    test.n = 5;

    send_packet((uint8_t *)&test, sizeof(struct usb_redir_extend_bulk_cache_packet));
    printf("\n\n");
    
    int len = sizeof(struct usb_redir_extend_bulk_cache_packet_) + sizeof(struct bulk_cache_list_param) * 1;
    struct usb_redir_extend_bulk_cache_packet_ *p = (struct usb_redir_extend_bulk_cache_packet_ *)malloc(len);
    p->m = 1;
    p->n = 2;
    const char *vpid = "0b95:772b";
    memcpy(p->id, vpid, strlen(vpid));
    p->count = 1;
    p->param[0].x = 3;
    p->param[0].y = 4;
    p->param[0].z = 5;
    
    int bulk_cache_packet_size = sizeof(struct usb_redir_extend_bulk_cache_packet__) + sizeof(struct bulk_cache_list_param) * 1;
    struct usb_redir_extend_bulk_cache_packet__ *bulk_cache_packet = (struct usb_redir_extend_bulk_cache_packet__ *)malloc(bulk_cache_packet_size);
    memset(bulk_cache_packet, 0, bulk_cache_packet_size);

    printf("%lu %lu\n", sizeof(struct usb_redir_extend_bulk_cache_packet_), sizeof(struct usb_redir_extend_bulk_cache_packet__));
    printf("%d %d %d\n", len, bulk_cache_packet_size, len-ID_LEN);
    memcpy(bulk_cache_packet, p+ID_LEN, len-ID_LEN);
    
    //memset(p, 0, len);
    send_packet((uint8_t *)bulk_cache_packet, bulk_cache_packet_size);
    return 0;
}

