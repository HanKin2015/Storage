/*******************************************************************************
* 文 件 名: amazing.c
* 文件描述: 奇怪的未定义
* 作    者: HanKin
* 创建日期: 2023.11.16
* 修改日期：2023.11.16
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>

int func(int x)
{
    return x;
}

int main(void)
{
    int y = func(x);    // error: ‘x’ undeclared (first use in this function)
    printf("%d\n", y);
    
    int x = func(x);
    printf("%d\n", x);  // 能正常的编译运行
    return 0;
}
