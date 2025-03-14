/*******************************************************************************
* 文 件 名: const_pointer.cpp
* 文件描述: 
* 作    者: HanKin
* 创建日期: 2025.03.11
* 修改日期：2025.03.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    //const*  o = NULL;     // error: expected unqualified-id before ‘char’
    char* const o = NULL;   // error: assignment of read-only variable ‘o’（一个指向字符的常量指针）
    const char *p = NULL;   // 一个指向常量字符的指针
    char const *q = NULL;   // 一个指向常量字符的指针
    const char *str1 = "hello world";
    const char *str2 = "hello c++";
    o = str1;
    p = str1;
    q = str1;
    printf("o: %s\n", o);
    printf("p: %s\n", p);
    printf("q: %s\n", q);

    o = str2;
    p = str2;
    q = str2;
    printf("o: %s\n", o);
    printf("p: %s\n", p);
    printf("q: %s\n", q);
    return 0;
}
