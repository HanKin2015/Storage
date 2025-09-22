/*******************************************************************************
* 文 件 名: return_example.c
* 文件描述: 居然可以加括号，这两种形式是等价的，编译器会将它们视为相同的语义
           这种灵活性可能源于 C 语言的设计历史，早期的 C 语言受到 B 语言等前辈语言的影响，允许这种书写风格
* 备    注: return 语句后的表达式可以加括号，也可以不加括号，这是语法允许的两种写法，两者在功能上没有任何区别
* 作    者: HanKin
* 创建日期: 2025.09.18
* 修改日期：2025.09.18
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>

int test(int x)
{
    if (x == 1) return 0;
    return(1);
}

int main()
{
    int ret = test(1);
    printf("ret = %d\n", ret);
    ret = test(0);
    printf("ret = %d\n", ret);
    return 0;
}
/*
root@hankin:~/opencv# ./a.out 
ret = 0
ret = 1
*/