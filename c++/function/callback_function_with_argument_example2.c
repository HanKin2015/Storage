/**
* 文 件 名: callback_function_with_argument_example2.c
* 文件描述: 带参数的回调函数
* 作    者: HanKin
* 创建日期: 2023.05.18
* 修改日期：2023.05.18
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>
 
int add(int a,int b);
int sub(int a,int b);
 
void functionchoose(int a, int b, int (*pf)(int, int));

int main()
{
    int a1 = 3, a2 = 4;
    functionchoose(a1, a2, add);
    functionchoose(a1, a2, sub);
    return 0;
}
 
int add(int a, int b)
{
    printf("add function \n");
    return a+b;
 
}
 
int sub(int a, int b)
{
    printf("sub function \n");
    return a-b;
}
 
void functionchoose(int a,int b,int (*pf)(int,int))
{
    printf("the result is %d \n",(*pf)( a, b));
    return;
}
/*
[root@ubuntu0006:~] #./a.out
add function
the result is 7
sub function
the result is -1
*/