/*******************************************************************************
* 文 件 名: modify_var.c
* 文件描述: 使用hex ediftor neo软件修改变量值
* 备    注: 
* 作    者: HanKin
* 创建日期: 2024.05.18
* 修改日期：2024.05.18
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void example()
{
    int x = 1000, y = 100;
    int var = 5;
    if (x > y) {
        var = 66;
    }
    printf("var = %d\n", var);
    return;
}

int main(int argc, char *argv[])
{
    example();
    return 0;
}