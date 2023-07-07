/**
* 文 件 名: struct_dynamic_allocation.cpp
* 文件描述: 结构体动态分配
* 作    者: HanKin
* 创建日期: 2023.07.03
* 修改日期：2023.07.03
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
    struct bulk_cache_list_param *param;
    uint8_t param_count;
};

static char **split(char *str, const char *delim, int *count)
{
    assert(str && strlen(str));
    assert(delim && strlen(delim));
    
    char **result = NULL;
    char *token = NULL;
    char *saveptr = NULL;
    int i = 0;

    token = strtok_r(str, delim, &saveptr);
    while (token != NULL) {
        result = (char **)realloc(result, (i + 1) * sizeof(char *));
        if (result == NULL) {
            printf("realloc failed\n");
            return NULL;
        }
        result[i] = token;
        i++;
        token = strtok_r(NULL, delim, &saveptr);
    }

    *count = i;
    return result;
}

// <Dev ID="0c45:1d7d" Desc="usb kx-2 sound card" Quirk="2" Ep="82" Aligned="8192" ></Dev>
// ID="0c45:1d7d" Desc="usb kx-2 sound card" Quirk="2" Param="Ep=82 Aligned=8192;Ep=87 Aligned=4096;Ep=01 Aligned=1024"
static int parse_param()
{
    struct usbredirhost_bulk_cache_list_item bulk_cache_list = { 0 };
    
    char str[] = "Ep=82 Aligned=8192;Ep=87 Aligned=4096;Ep=01 Aligned=1024";
    const char delim[] = ";";
    int param_count = 0;
    char **param = split(str, delim, &param_count);
    if (!param) {
        return -1;
    }
    
    bulk_cache_list.param_count = param_count;
    bulk_cache_list.param = (struct bulk_cache_list_param *)calloc(param_count, sizeof(struct bulk_cache_list_param));
    
    for (int i = 0; i < param_count; i++) {
        printf("%d: %s\n", __LINE__, param[i]);
        
        int key_values_cnt = 0;
        char **key_values = split(param[i], " ", &key_values_cnt);
        if (!key_values || key_values_cnt != 2) {
            printf("key_values is NULL, or key_values_cnt is not 2 (%d)\n", key_values_cnt);
            return -1;
        }
        
        for (int j = 0; j < key_values_cnt; j++) {
            int elem_cnt = 0;
            char **elems = split(key_values[j], "=", &elem_cnt);
            if (!elems || elem_cnt != 2) {
                printf("key_values is NULL, or elem_cnt is not 2 (%d)\n", elem_cnt);
                return -1;
            }
            if (strcmp(elems[0], "Ep") == 0) {
                printf("Ep = %02lx ", strtoul(elems[1], NULL, 16));
                bulk_cache_list.param[i].endpoint = strtoul(elems[1], NULL, 16);
            }
            if (strcmp(elems[0], "Aligned") == 0) {
                printf("Aligned = %lu\n", strtoul(elems[1], NULL, 10));
                bulk_cache_list.param[i].bytes_per_transfer = strtoul(elems[1], NULL, 10);
            }
            bulk_cache_list.param[i].no_transfers = 30;
            free(elems);
        }
        printf("\n");
        free(key_values);
    }
    free(param);
    
    for (int i = 0; i < bulk_cache_list.param_count; i++) {
        printf("parse quirk %d Ep %02x no_transfers %d bytes_per_transfer %d\n", bulk_cache_list.quirk,
            bulk_cache_list.param[i].endpoint, bulk_cache_list.param[i].no_transfers, bulk_cache_list.param[i].bytes_per_transfer);
    }
    return 0;
}

struct usb_redir_extend_bulk_cache_packet {
    uint32_t quirk;
    struct bulk_cache_list_param *param;
    uint8_t param_count;
};

void send_packet(uint8_t *data, int data_len)
{
    struct usb_redir_extend_bulk_cache_packet bulk_cache_info;
    bulk_cache_info = *(struct usb_redir_extend_bulk_cache_packet *)data;
    printf("hejian data_len %d, quirk %d param_count %d\n", data_len,
        bulk_cache_info.quirk, bulk_cache_info.param_count);
        
    printf("param endpoint %02x\n", bulk_cache_info.param[0].endpoint);
    return;
}

int main()
{
    std::vector<usbredirhost_bulk_cache_list_item> list;
    
    usbredirhost_bulk_cache_list_item info;
    info.param_count = 1;
    info.param = (struct bulk_cache_list_param *)calloc(info.param_count, sizeof(struct bulk_cache_list_param));
    const char *vpid = "1234:4321000000";
    memcpy(info.id, vpid, strlen(vpid));
    info.param[0].endpoint = 0x82;
    info.param[0].no_transfers = 15;
    info.param[0].bytes_per_transfer = 4096;
    list.push_back(info);
    list.push_back(info);
    
    int count = list.size();
    printf("count %d\n", count);
    struct usbredirhost_bulk_cache_list_item *bulk_cache_list =
        (struct usbredirhost_bulk_cache_list_item *)calloc(count,
        sizeof(struct usbredirhost_bulk_cache_list_item));
    for (int i = 0; i < count; ++i) {
        memcpy(&(bulk_cache_list[i]), &(list[i]), sizeof(list[i]));
    }
    printf("hejian 1 %d\n", bulk_cache_list[1].param[0].bytes_per_transfer);
    
    struct usb_redir_extend_bulk_cache_packet bulk_cache_packet = { 0 };
    for (int i = 0; i < count; ++i) {
        memset(&bulk_cache_packet, 0, sizeof(bulk_cache_packet));
        printf("hejian before %d %s\n", bulk_cache_list[i].param[0].bytes_per_transfer, bulk_cache_list[i].id);
        //memcpy(&bulk_cache_packet, &(bulk_cache_list[i])+ID_LEN, sizeof(bulk_cache_list[i])-ID_LEN);
        bulk_cache_packet.quirk = bulk_cache_list[i].quirk;
        bulk_cache_packet.param = bulk_cache_list[i].param;
        bulk_cache_packet.param_count = bulk_cache_list[i].param_count;
        
        printf("hejian param_count %d\n", bulk_cache_packet.param_count);
        printf("hejian 2 %d\n", bulk_cache_packet.param[0].bytes_per_transfer);
    }
    
    send_packet((uint8_t *)&bulk_cache_packet, sizeof(bulk_cache_packet));
    return 0;
}

