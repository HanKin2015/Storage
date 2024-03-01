/*******************************************************************************
* 文 件 名: custom_memory_leak_detection_tool.c
* 文件描述: 自定义内存泄漏检测工具
* 备    注: https://mp.weixin.qq.com/s/UOdZsaenSp1SDsglLpofyA
* 作    者: HanKin
* 创建日期: 2024.02.29
* 修改日期：2024.02.29
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 1000

typedef struct {
    void *ptr;
    size_t size;
} Allocation;

Allocation hash_table[HASH_SIZE] = {0};

void* tracked_malloc(size_t size) {
    void *ptr = malloc(size);
    if (ptr) {
        // Store allocation info in hash table
        size_t index = (size_t)ptr % HASH_SIZE;
        hash_table[index].ptr = ptr;
        hash_table[index].size = size;
    }
    return ptr;
}

void tracked_free(void *ptr) {
    size_t index = (size_t)ptr % HASH_SIZE;
    if (hash_table[index].ptr == ptr) {
        free(ptr);
        hash_table[index].ptr = NULL;
        hash_table[index].size = 0;
    }
}

void report_leaks() {
    for (int i = 0; i < HASH_SIZE; i++) {
        if (hash_table[i].ptr) {
            fprintf(stderr, "Memory leak detected: %p (%zu bytes)\n", hash_table[i].ptr, hash_table[i].size);
        }
    }
}

int main() {
    // Track memory allocations
    void *ptr1 = tracked_malloc(10);
    void *ptr2 = tracked_malloc(20);

    // Simulate memory leak
    // void *ptr3 = malloc(30);

    // Free memory
    tracked_free(ptr1);
    //tracked_free(ptr2);

    // Check for leaks
    report_leaks(); // Memory leak detected: 0x1cb2030 (20 bytes)
    return 0;
}