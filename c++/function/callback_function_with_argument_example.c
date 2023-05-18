/**
* 文 件 名: callback_function_with_argument_example.c
* 文件描述: 带参数的回调函数
* 作    者: HanKin
* 创建日期: 2023.05.18
* 修改日期：2023.05.18
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include<stdio.h>

int Callback_1(int x) // Callback Function 1
{
    printf("Hello, this is Callback_1: x = %d\n", x);
    return 0;
}

int Callback_2(int x) // Callback Function 2
{
    printf("Hello, this is Callback_2: x = %d\n", x);
    return 0;
}

int Callback_3(int x) // Callback Function 3
{
    printf("Hello, this is Callback_3: x = %d\n", x);
    return 0;
}

// 这个相当于是一个第三方库，无法对其进行修改
int Handle(int y, int (*Callback)(int))
{
    printf("Entering Handle Function.\n");
    Callback(y);
    printf("Leaving Handle Function.\n");
    return 0;
}

int main()
{
    int a = 2;
    int b = 4;
    int c = 6;
    printf("Entering Main Function.\n");

    Handle(a, Callback_1);
    Handle(b, Callback_2);
    Handle(c, Callback_3);

    printf("Leaving Main Function.\n");
    return 0;
}
/*
[root@ubuntu0006:~] #./a.out
Entering Main Function.
Entering Handle Function.
Hello, this is Callback_1: x = 2
Leaving Handle Function.
Entering Handle Function.
Hello, this is Callback_2: x = 4
Leaving Handle Function.
Entering Handle Function.
Hello, this is Callback_3: x = 6
Leaving Handle Function.
Leaving Main Function.
*/