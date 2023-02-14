/**
* 文 件 名: bzero_example.cpp
* 文件描述: 学习bzero函数
* 作    者: HanKin
* 创建日期: 2023.02.14
* 修改日期：2023.02.14
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#include <cstdlib>
using namespace std;

/*
bzero() 能够将内存块（字符串）的前n个字节清零，在"string.h"头文件中，原型为：void bzero(void *s, int n);

【参数】s为内存（字符串）指针，n 为需要清零的字节数。
bzero()将参数s 所指的内存区域前n 个字节全部设为零。

bzero(void *s, int n) 与 memset((void*)s, 0,size_tn)是等价的，都是用来将内存块的前 n 个字节清零。

说明：bzero无返回值，并且使用string.h头文件，string.h曾经是posix标准的一部分，但是在POSIX.1-2001标准里面，这些函数被标记为了遗留函数而不推荐使用。在POSIX.1-2008标准里已经没有这些函数了。推荐使用memset替代bzero。
*/
int main(int argc, char *argv[])
{
    char str[BUFSIZ] = "123456789";
    printf("str[5]: %c\n", str[5]);
    bzero(str, BUFSIZ);
    printf("str[5]: %c\n", str[5]);
    
    memcpy(str, "123456789", BUFSIZ);
    printf("str[5]: %c\n", str[5]);
    memset(str, 0, BUFSIZ);
    printf("str[5]: %c\n", str[5]);
    return 0;
}
/*
[root@ubuntu0006:/media/vdb] #./a.out
str[5]: 6
str[5]:
str[5]: 6
str[5]:
*/