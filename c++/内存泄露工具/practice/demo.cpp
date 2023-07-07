/**
* 文 件 名: free_0_size_array.cpp
* 文件描述: 释放0长数组结构体内存
* 作    者: HanKin
* 创建日期: 2023.07.07
* 修改日期：2023.07.07
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#include <cstdlib>
#include <inttypes.h>
#include <cassert>
#include <vector>
#define ID_LEN 16
using namespace std;

struct bulk_cache_list_param {
    uint32_t endpoint;
    uint8_t no_transfers;
    uint32_t bytes_per_transfer;
};
struct usbredirhost_bulk_cache_list_item {
    char id[ID_LEN];
    uint32_t quirk;
    uint8_t param_count;
    struct bulk_cache_list_param param[0];
};

struct usb_redir_extend_bulk_cache_packet {
    uint32_t quirk;
    uint8_t param_count;
    struct bulk_cache_list_param param[0];
};

void send_packet(uint8_t *data, int data_len)
{
    struct usb_redir_extend_bulk_cache_packet *bulk_cache_info = NULL;
    bulk_cache_info = (struct usb_redir_extend_bulk_cache_packet *)data;
    printf("hejian data_len %d, quirk %d param_count %d\n", data_len,
        bulk_cache_info->quirk, bulk_cache_info->param_count);
        
    printf("param endpoint %02x\n", bulk_cache_info->param[0].endpoint);
    return;
}

int main()
{
    std::vector<usbredirhost_bulk_cache_list_item *> list;
    
    for (int i = 0; i < 3; i++) {   // 共有三个名单配置
        int param_count = 1;
        
        int info_size = sizeof(struct usbredirhost_bulk_cache_list_item) + param_count * sizeof(struct bulk_cache_list_param);
        struct usbredirhost_bulk_cache_list_item *info = (struct usbredirhost_bulk_cache_list_item *)malloc(info_size);
        if (info) {
            memset(info, 0, info_size);
            
            const char *vpid = "1234:4321";
            memcpy(info->id, vpid, strlen(vpid));
            info->quirk = 2;
            info->param_count = param_count;
            for (int j = 0; j < param_count; j++) {
                info->param[j].endpoint = 0x82;
                info->param[j].no_transfers = 15;
                info->param[j].bytes_per_transfer = 4096;
            }
            list.push_back(info);
            printf("bytes_per_transfer = %u\n", info->param[0].bytes_per_transfer);
            printf("- bytes_per_transfer = %u\n", list[0]->param[0].bytes_per_transfer);
            //free(info);
            //info = NULL;
        }
    }
    printf("list size = %lu\n", list.size());
    printf("bytes_per_transfer = %u\n", list[0]->param[0].bytes_per_transfer);
    
    int count = list.size();
    printf("count %d\n", count);
    struct usbredirhost_bulk_cache_list_item **bulk_cache_list =
        (struct usbredirhost_bulk_cache_list_item **)calloc(count,
        sizeof(struct usbredirhost_bulk_cache_list_item *));
    for (int i = 0; i < count; ++i) {
        //memcpy(&(bulk_cache_list[i]), &(list[i]), sizeof(list[i]));
        bulk_cache_list[i] = list[i];
    }
    printf("hejian 1 %d\n", bulk_cache_list[0]->param[0].bytes_per_transfer);
    
    struct usb_redir_extend_bulk_cache_packet *bulk_cache_packet = NULL;
    for (int i = 0; i < count; ++i) {
         int bulk_cache_packet_size = sizeof(struct usb_redir_extend_bulk_cache_packet) +
                bulk_cache_list[i]->param_count * sizeof(struct bulk_cache_list_param);
        bulk_cache_packet = (struct usb_redir_extend_bulk_cache_packet *)malloc(bulk_cache_packet_size);
        if (bulk_cache_packet) {
            memset(bulk_cache_packet, 0, bulk_cache_packet_size);
            memcpy(bulk_cache_packet, (bulk_cache_list[i]->id)+ID_LEN, bulk_cache_packet_size);
            send_packet((uint8_t *)bulk_cache_packet, bulk_cache_packet_size);
        }
    }
    return 0;
}

