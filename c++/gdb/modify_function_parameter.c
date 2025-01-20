/*******************************************************************************
* 文 件 名: modify_function_parameter.c
* 文件描述: 修改函数参数
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.01.07
* 修改日期：2025.01.07
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>

void test(int x, int y, int *z)
{
    int n = y;
    printf("x = %d, y = %d, z = %d\n", x, y, *z);
    printf("n = %d\n", n);
    return;
}

int main()
{
    for (int i = 0; i < 10; i++) {
        test(i, i, &i);
    }
    return 0;
}
