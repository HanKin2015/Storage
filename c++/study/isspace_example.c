/*******************************************************************************
* 文 件 名: isspace_example.c
* 文件描述: 一个用于检查字符是否为空白字符的标准库函数
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.03.10
* 修改日期：2025.03.10
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main()
{
    char chs[] = {' ', '\t', '\n', '\r', '\v', '\f', 'h'};
    size_t len = strlen(chs);
    printf("chs length = %ld\n", len);
    for (int i = 0; i < len; i++) {
        if (isspace(chs[i])) {
            printf("'%c' 是一个空白字符。\n", chs[i]);
        } else {
            printf("'%c' 不是一个空白字符。\n", chs[i]);
        }
    }
    return 0;
}
