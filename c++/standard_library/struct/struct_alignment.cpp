/**
* 文 件 名: struct_alignment.cpp
* 文件描述: 结构体对齐
* 作    者: HanKin
* 创建日期: 2023.07.14
* 修改日期：2023.07.14
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#include <cstdlib>
#include <vector>
#include <inttypes.h>
// 判断当前标准是否使用的是C++11
#if __cplusplus >= 201103L
#include <unordered_map>
#endif
#include <map>
using namespace std;
#define ID_LEN 16

#pragma pack(push)
#pragma pack(1)

struct bulk_cache_list_param {
	uint32_t endpoint;
	uint8_t no_transfers;
	uint32_t bytes_per_transfer;
};

typedef struct tagBulkCacheListItem {
	char id[ID_LEN];
	uint32_t quirk;
	uint8_t param_count;
	struct bulk_cache_list_param param[0];
}BulkCacheListItem, *PBulkCacheListItem;

#pragma pack(pop)

struct bulk_cache_list_param_ {
	uint32_t endpoint;
	uint8_t no_transfers;
	uint32_t bytes_per_transfer;
};

int main(int argc, char *argv[])
{
    printf("%lu\n", sizeof(struct bulk_cache_list_param));
    printf("%lu\n", sizeof(struct bulk_cache_list_param_));
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
9
12
*/
