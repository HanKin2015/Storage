/**
* 文 件 名: 0_pointer_useable.c
* 文件描述: 0 指针的使用
* 作    者: HanKin
* 创建日期: 2023.06.20
* 修改日期：2023.06.20
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include<stdio.h>
#include <stddef.h>
 
struct test
{
    char i;
    int  j;
    char k;
};

#define max(a, b) \
    ({ typeof (a) _a = (a); \
       typeof (b) _b = (b); \
       _a > _b ? _a : _b; })
 
int main()
{
    struct test temp;
    printf("sizeof(struct test) = %lu\n", sizeof(struct test));
    printf("&temp = %p\n", &temp);   
    printf("&temp.k = %p\n", &temp.k);
    printf("&((struct test *)0)->k = %d\n", ((int)&((struct test *)0)->k));
    
    // #define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)
    printf("offsetof(struct test, k) = %lu\n", offsetof(struct test, k));
    
    //printf("typeof(((struct test *)0)->k) = %d\n", typeof(((struct test *)0)->k));
    int m = max(4, 6);
    printf("m = %d\n", m);
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
sizeof(struct test) = 12
&temp = 0x7ffe4b347de0
&temp.k = 0x7ffe4b347de8
&((struct test *)0)->k = 8
offsetof(struct test, k) = 8
m = 6
*/