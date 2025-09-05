
/*******************************************************************************
* 文 件 名: secondary_pointer.cpp
* 文件描述: 二级指针
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.09.04
* 修改日期：2025.09.04
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

// 基本语法
void test1()
{
    int a = 10;
    int *p = &a;       // 一级指针：p 指向 a
    int **pp = &p;     // 二级指针：pp 指向 p

    printf("a = %d\n", a);          // 直接访问 a → 10
    printf("*p = %d\n", *p);        // 通过一级指针访问 a → 10
    printf("**pp = %d\n", **pp);    // 通过二级指针访问 a → 10

    printf("&a = %p\n", &a);        // a 的地址 → 0x1000
    printf("p = %p\n", p);          // p 存储 a 的地址 → 0x1000
    printf("*pp = %p\n", *pp);      // pp 指向 p，*pp 即 p 的值 → 0x1000

    printf("&p = %p\n", &p);        // p 的地址 → 0x2000
    printf("pp = %p\n", pp);        // pp 存储 p 的地址 → 0x2000
}

// 指针内存在外部分配
void alloc_mem(int **pp)
{
    *pp = (int*)malloc(sizeof(int));  // *pp 即外部的 p，修改其指向新内存
    **pp = 20;  // 等价于 *p = 20
}
void test2()
{
    int *p = NULL;
    alloc_mem(&p);  // 传递 p 的地址（二级指针）
    printf("%d\n", *p);  // 正确输出 20
    free(p);
}

// 用二级指针 char**接收字符串数组
void print_strings(const char **strs, int n)
{
    for (int i = 0; i < n; i++) {
        printf("%s\n", strs[i]);  // strs[i] 是 char* 类型
    }
}
void test3()
{
    const char *names[] = {"Alice", "Bob", "Charlie"};  // 指针数组
    print_strings(names, 3);  // 数组名 decay 为 char**类型
}

// 实现多维动态数组
void test4()
{
    int rows = 3, cols = 2;
    int **arr = (int**)malloc(rows * sizeof(int*));  // 第一维：指向 int* 的指针
    
    for (int i = 0; i < rows; i++) {
        arr[i] = (int*)malloc(cols * sizeof(int));  // 第二维：指向 int 的指针
        arr[i][0] = i;
        arr[i][1] = i * 10;
    }
    
    // 访问数据
    printf("%d\n", arr[2][1]);  // 输出 20
    
    // 释放内存
    for (int i = 0; i < rows; i++) free(arr[i]);
    free(arr);
}

int main()
{
    test1();
    test2();
    test3();
    test4();
    return 0;
}