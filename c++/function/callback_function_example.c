/**
* 文 件 名: callback_function_example.c
* 文件描述: 回调函数
* 作    者: HanKin
* 创建日期: 2023.05.18
* 修改日期：2023.05.18
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>

int Callback_1() // Callback Function 1
{
    printf("Hello, this is Callback_1\n");
    return 0;
}

int Callback_2() // Callback Function 2
{
    printf("Hello, this is Callback_2\n");
    return 0;
}

int Callback_3() // Callback Function 3
{
    printf("Hello, this is Callback_3\n");
    return 0;
}

// 这个相当于是一个第三方库，无法对其进行修改
int Handle(int (*Callback)())
{
    printf("Entering Handle Function.\n");
    Callback();
    printf("Leaving Handle Function.\n");
    return 0;
}

int main()
{
    printf("Entering Main Function.\n");
    Handle(Callback_1);
    Handle(Callback_2);
    Handle(Callback_3);
    printf("Leaving Main Function.\n");
    return 0;
}
/*
[root@ubuntu0006:~] #./a.out
Entering Main Function.
Entering Handle Function.
Hello, this is Callback_1
Leaving Handle Function.
Entering Handle Function.
Hello, this is Callback_2
Leaving Handle Function.
Entering Handle Function.
Hello, this is Callback_3
Leaving Handle Function.
Leaving Main Function.
*/