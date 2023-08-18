/**
* 文 件 名: if_error_instruct_example.c
* 文件描述: #if和#error指令学习
* 备    注: #if只支持常量表达式，#error用来在程序中生成一个编译错误
* 作    者: HanKin
* 创建日期: 2023.05.12
* 修改日期：2023.05.12
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <string.h>

//#define DEBUG

#ifdef DEBUG
#error "define DEBUG"
#endif

// 我的编译系统是x86_64因此编译会报错
#ifdef __x86_64__
#error "This program requires a 32-bit platform."
#endif

const int x = sizeof(int);
#define y sizeof(int)
const int z = 4;

// 不报错
#if (5 == 4)
#error "5 This program requires a 32-bit platform."
#endif

// 报错
#if (4 == 4)
#error "4 This program requires a 32-bit platform."
#endif

// 不报错
#if (x == 4)
#error "x This program requires a 32-bit platform."
#endif

// error: missing binary operator before token "("
#if 0
#if (y == 4)
#error "y This program requires a 32-bit platform."
#endif
#endif

// 不报错
#if (z == 4)
#error "z This program requires a 32-bit platform."
#endif

int main()
{
    printf("sizeof(int) = %ld, x = %d\n", sizeof(int), x);
    printf("hello #error\n");
    if (sizeof(int) == 4) {
        printf("yes\n");
    } else {
        printf("no\n");
    }
    if (x == 4) {
        printf("x yes\n");
    } else {
        printf("x no\n");
    }
    return 0;
}
/*
[root@ubuntu0006:~] #gcc if_error_instruct_example.c
if_error_instruct_example.c:11:2: error: #error "This program requires a 32-bit platform."
 #error "This program requires a 32-bit platform."
  ^
if_error_instruct_example.c:22:2: error: #error "4 This program requires a 32-bit platform."
 #error "4 This program requires a 32-bit platform."
  ^

必须要把编译错误#error的地方删除后才能生成a.out文件
[root@ubuntu0006:~/cmake] #./a.out
sizeof(int) = 4, x = 4
hello #error
yes
x yes
*/

