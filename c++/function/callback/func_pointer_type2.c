/**
* 文 件 名: func_pointer_type2.c
* 文件描述: 函数指针类型的使用例子
* 作    者: HanKin
* 创建日期: 2023.06.25
* 修改日期：2023.06.25
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include <stdio.h>
#include <stdlib.h>

//void (*swap)(int *a, int *b); // 这一行毫无意义
typedef void (*swap_alias)(int *a, int *b);

void swap_func(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
    return;
}

void change_func(int *a, int *b)
{
    *a = 99;
    *b = 9999;
    return;
}

struct SWAP_STRUCT {
    swap_alias swap_alias_ptr;
    //swap swap_ptr;    // 因此如果不使用typedef修饰的话，则不能使用函数名来定义指针
    swap_alias change_func_ptr;
};

int main()
{
    int a = 1, b = 10;
    printf("a = %d, b = %d\n", a, b);
    
    struct SWAP_STRUCT st_test;
    st_test.swap_alias_ptr = swap_func;
    st_test.swap_alias_ptr(&a, &b);
    printf("a = %d, b = %d\n", a, b);
    st_test.change_func_ptr = change_func;
    st_test.change_func_ptr(&a, &b);
    
    printf("a = %d, b = %d\n", a, b);
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
a = 1, b = 10
a = 10, b = 1
a = 99, b = 9999
*/
