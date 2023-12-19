/*******************************************************************************
* 文 件 名: strncat_example.cpp
* 文件描述: strncat函数
* 备    注: 
* 作    者: HanKin
* 创建日期: 2023.12.19
* 修改日期：2023.12.19
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

static void base()
{
    char *str = new char[20];
    const char *s = "123";
    strncat(str, s, strlen(s) - 1);
    printf("%lu %lu %lu %lu %s\n", strlen(s), strlen(str), sizeof(s), sizeof(str), str);    // 3 2 8 8 12
    printf("%lu %lu %lu %lu\n", sizeof(char), sizeof(char *), sizeof(int), sizeof(int *));  // 1 8 4 8

    const char *log_file_prefix = "/log/today/log_";
    char tmp[256];
    strncpy(tmp, log_file_prefix, strlen(log_file_prefix));
    printf("tmp: %s, %lu, %lu.\n", tmp, sizeof(log_file_prefix), strlen(log_file_prefix));  // tmp: /log/today/log_, 8, 15.
    return;
}

static void segmentation_fault()
{
    char *str1 = "hello";
    char str2[20] = "hello";
    char *str3 = "world";
    //strncat(str1, str3, strlen(str3));    // 会出现段错误
    strncat(str2, str3, strlen(str3));
    printf("str1: %s\n", str1);
    printf("str2: %s\n", str2);
    return;
}

int main()
{
    segmentation_fault();
    return 0;
}
