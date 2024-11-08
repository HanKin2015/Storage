/*******************************************************************************
* 文 件 名: assert_example.c
* 文件描述: assert函数
* 备    注: assert函数中使用或或者与运算时结果是怎么样
* 作    者: HanKin
* 创建日期: 2024.11.05
* 修改日期：2024.11.05
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <assert.h>
#include <stdio.h>

int main()
{
    int num = 100;
    int *p = &num;
    int *q = NULL;
    assert(p || q);
    return 0;
}
/*
两个同时为NULL时才会抛出异常，只有有一个为真就不会抛出异常
[root@ubuntu0006:~/cmake] #./a.out
a.out: l.c:19: main: Assertion `p || q' failed.
已放弃
*/