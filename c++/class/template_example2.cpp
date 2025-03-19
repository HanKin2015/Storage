/*******************************************************************************
* 文 件 名: template_example2.cpp
* 文件描述: template类
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.03.17
* 修改日期：2025.03.17
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstdio>
#include <memory>

template <typename T>
using sp = std::shared_ptr<T>;

template <typename T>
using up = std::unique_ptr<T>;

void test(up<int> &p)
{
    printf("%p\n", p.get()); // 使用 p.get() 获取原始指针
    return;
}

int main()
{
    up<int> p = std::make_unique<int>(42); // 初始化 unique_ptr
    test(p);
    return 0;
}
