/*******************************************************************************
* 文 件 名: strtok_example.c
* 文件描述: 莫名其妙地崩溃
* 备    注: 
* 作    者: HanKin
* 创建日期: 2024.04.01
* 修改日期：2024.04.01
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <string.h>

static void test1()
{
    const char *path = "./test1/test2/test3";
    const char *sep = "/";
    char *token = strtok((char *)path, sep);
    return;
}

static void test2()
{
    char *path = "./test1/test2/test3";
    const char *sep = "/";
    char *token = strtok((char *)path, sep);
    return;
}

// 真的很神奇，不能弄成指针
static void test3()
{
    const char path[] = "./test1/test2/test3";
    const char *sep = "/";
    char *token = strtok((char *)path, sep);
    return;
}

static void test4()
{
    char path[] = "./test1/test2/test3";
    const char *sep = "/";
    char *token = strtok(path, sep);
    while (token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL, sep);
    }
    return;
}

int main()
{
    test3();
    return 0;
}