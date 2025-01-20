/*******************************************************************************
* 文 件 名: array_address.c
* 文件描述: &arr和arr的地址
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.01.03
* 修改日期：2025.01.03
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <string.h>

void test1()
{
    char header[256];
    printf("%p %p\n", header, &header); // 0x7ffe3a521570 0x7ffe3a521570
    memset(&header, 0, sizeof(header));
}

void test2()
{
    char *header = (char *)malloc(256 * sizeof(char)); // 动态分配内存

    printf("header address: %p\n", (void*)header); // 动态分配的内存地址
    printf("&header address: %p\n", (void*)&header); // 指针的地址
    /*
    header address: 0x1667010
    &header address: 0x7ffede4f0400
    */

    memset(header, 0, 256); // 使用 header
    free(header); // 释放动态分配的内存
}

int main()
{
    
    return 0;
}