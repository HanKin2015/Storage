/*******************************************************************************
* 文 件 名: special_writing_style.c
* 文件描述: 几种特殊的写风格
* 备    注: 
* 作    者: HanKin
* 创建日期: 2024.05.23
* 修改日期：2024.05.23
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>

int main()
{
    // 正常
    int x = 10, y = 100;
    if (x > y) {
        printf("hello\n");
    } else
        printf("world\n");
    
    // 正常
    if (x < y) {
        ;//haha
    }
    
    // 正常
    if (x > y) {
        printf("hh\n");
    } else {
    
    }
    return 0;
}