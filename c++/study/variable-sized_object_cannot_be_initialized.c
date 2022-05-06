/**
 * 文 件 名: variable-sized_object_cannot_be_initialized.c
 * 文件描述: 使用变量的数组无法直接初始化
 * 作    者: HanKin
 * 创建日期: 2021.09.01
 * 修改日期：2021.09.01
 *
 * Copyright (c) 2021 HanKin. All rights reserved.
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

static void right()
{
    const int buf_size = 1024;
    char a[1024] = {0};
    char b[buf_size];
    memset(b, 0, sizeof(b));
}

static void wrong()
{
    const int buf_size = 1024;
    
    // error: variable-sized object may not be initialized
    //  warning: excess elements in array initializer
    //char b[buf_size] = {0};
}

int main()
{
    right();
    wrong();
    return 0;
}