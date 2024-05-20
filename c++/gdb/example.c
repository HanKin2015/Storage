/*******************************************************************************
* 文 件 名: example.c
* 文件描述: gdb练习调试文件
* 备    注: 
* 作    者: HanKin
* 创建日期: 2024.05.18
* 修改日期：2024.05.18
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 很奇怪崩溃到了最后一行，这种情况居然无法进行调试
void test()
{
    int var[50] = { 0 };
    var[50] = 20;
    printf("%d\n", var[50]);
    return;
}

// 尽管 var 数组的大小只有 50 个整数，但是在 C 语言中，数组越界访问并不会引发运行时错误或崩溃。这是因为 C 语言中没有内置的边界检查机制，所以程序会继续执行，尽管这是一种未定义行为。
void func(void *p)
{
    int *var = (int *)p;
    var[55] = 20;
    printf("%d\n", var[55]);
    return;
}

void example1()
{
    char *p = (char *)malloc(40 * sizeof(char));
    // 对于指针变量 p，sizeof(p) 将返回指针本身的大小，而不是指向的内存块的大小。同样，strlen(p) 是用于计算以空字符结尾的字符串的长度，而不是用于计算动态分配的内存块的大小。
    printf("strlen = %ld, sizeof = %ld\n", strlen(p), sizeof(p));
    //memset(p, 0, sizeof(p));
    free(p);
    free(p);
    p = NULL;
    return;
}

// 也没有崩溃
void example2()
{
    int *ptr = (int *)malloc(sizeof(int));
    free(ptr);
    ptr[0] = 20;  // 使用已释放的内存
    return;
}

int main(int argc, char *argv[])
{
    //test();
    
    int *var = (int *)malloc(50 * sizeof(int));
    //func(var);
    free(var);
    var = NULL;
    
    example1();
    return 0;
}