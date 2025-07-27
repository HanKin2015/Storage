/*******************************************************************************
* 文 件 名: struct_alignment.cpp
* 文件描述: 结构体对齐
* 备    注: 
* 作    者: HanKin
* 创建日期: 2023.07.14
* 修改日期：2025.07.27
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/

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

#pragma pack(push)
#pragma pack(1)

struct bulk_cache_list_param {
	uint32_t endpoint;          // 4
	uint8_t no_transfers;       // 1
	uint32_t bytes_per_transfer;// 4
};

#pragma pack(pop)

struct bulk_cache_list_param_ {
	uint32_t endpoint;          // 4
	uint8_t no_transfers;       // 4
	uint32_t bytes_per_transfer;// 4
};

typedef struct struct1
{
    short b;        // 2
    char a;         // 3
    unsigned char c;// 4
    int d;          // 8
} struct3;  // 8

// 结构体成员对齐到特定倍数（如 2 的倍数），主要是为了提高 CPU 访问内存的效率，这与硬件的工作机制密切相关
typedef struct
{
    char a;         // 1
    short b;        // 4
    unsigned char c;// 8
    int d;          // 12
} struct2;  // 12

int main(int argc, char *argv[])
{
    printf("%lu\n", sizeof(struct bulk_cache_list_param));  // 9
    printf("%lu\n", sizeof(struct bulk_cache_list_param_)); // 12
    printf("%lu\n", sizeof(struct struct1));                // 8
    printf("%lu\n", sizeof(struct2));                       // 12
    return 0;
}