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
    struct bulk_cache_list_param *params;
    uint8_t params_count;
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
int main()
{
    struct usbredirhost_bulk_cache_list_item bulk_cache_list = { 0 };
    
    char str[] = "Ep=82 Aligned=8192;Ep=87 Aligned=4096;Ep=01 Aligned=1024";
    const char delim[] = ";";
    int params_count = 0;
    char **params = split(str, delim, &params_count);
    if (!params) {
        return -1;
    }
    
    bulk_cache_list.params_count = params_count;
    bulk_cache_list.params = (struct bulk_cache_list_param *)calloc(params_count, sizeof(struct bulk_cache_list_param));
    
    for (int i = 0; i < params_count; i++) {
        printf("%d: %s\n", __LINE__, params[i]);
        
        int key_values_cnt = 0;
        char **key_values = split(params[i], " ", &key_values_cnt);
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
                bulk_cache_list.params[i].endpoint = strtoul(elems[1], NULL, 16);
            }
            if (strcmp(elems[0], "Aligned") == 0) {
                printf("Aligned = %lu\n", strtoul(elems[1], NULL, 10));
                bulk_cache_list.params[i].bytes_per_transfer = strtoul(elems[1], NULL, 10);
            }
            bulk_cache_list.params[i].no_transfers = 30;
            free(elems);
        }
        printf("\n");
        free(key_values);
    }
    free(params);
    
    for (int i = 0; i < bulk_cache_list.params_count; i++) {
        printf("parse quirk %d Ep %02x no_transfers %d bytes_per_transfer %d\n", bulk_cache_list.quirk,
            bulk_cache_list.params[i].endpoint, bulk_cache_list.params[i].no_transfers, bulk_cache_list.params[i].bytes_per_transfer);
    }
    return 0;
}
