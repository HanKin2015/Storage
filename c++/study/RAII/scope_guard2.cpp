/*******************************************************************************
* 文 件 名: scope_guard2.cpp
* 文件描述: 从scope_guard.cpp文件得到灵感，其实已经很接近RAII技术的核心理念了
* 备    注：本文彻底理解到RAII技术的价值
* 作    者: HanKin
* 创建日期: 2024.01.22
* 修改日期：2024.01.22
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/

#include <iostream>
#include <functional>
#include <cstdio>
#include <malloc.h>
#include <cstdlib>
#include <string.h>

class ScopeGuard
{
public:
    ScopeGuard(std::function<void()> func) : func_(func) {}
    ~ScopeGuard() { func_(); }
private:
    std::function<void()> func_;
};

void test1()
{
    int *arr = NULL;
    
    // 利用类使用超出域后自动析构机制
    ScopeGuard guard([&]() { if (arr) { printf("free arr\n"); free(arr); arr = NULL; } });
    
    arr = (int *)malloc(100 * sizeof(int));
    memset(arr, 0, 100);
    arr[50] = 123;
    printf("%d\n", arr[50]);
    return;
}

void test2()
{
    int *arr = NULL;
    arr = (int *)malloc(100 * sizeof(int));
    memset(arr, 0, 100);
    arr[50] = 123;
    printf("%d\n", arr[50]);
    return;
}

int main()
{
    std::cout << "Enter main" << std::endl;

    /*
    Enter main
    123
    free arr
    Leave main
    */
    test1();
    
    // 存在内存泄露
    test2();

    std::cout << "Leave main" << std::endl;
    return 0;
}