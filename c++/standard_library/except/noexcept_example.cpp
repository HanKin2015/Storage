/*******************************************************************************
* 文 件 名: noexcept_example.cpp
* 文件描述: noexcept 是 C++11 引入的一个关键字，用于指定一个函数是否会抛出异常。它的主要目的是提高程序的性能和安全性，特别是在异常处理方面
* 备    注: 用于指定一个函数是否会抛出异常，而不是跳过异常不处理
* 作    者: HanKin
* 创建日期: 2025.02.17
* 修改日期：2025.02.17
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cassert>
#include <cstdio>
using namespace std;

void test(int x) noexcept
{
    printf("hejian\n");
    assert(x);
    return;
}

void t(int x) noexcept
{
    if (x <= 0) {
        throw std::runtime_error("An error occurred!");
    }
    return;
}

int main()
{
    t(0);
    return 0;
}
