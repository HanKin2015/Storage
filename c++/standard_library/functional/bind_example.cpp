/*******************************************************************************
* 文 件 名: bind_example.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2024.02.02
* 修改日期：2024.02.02
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <functional>
#include <cstdio>
#include <cstdint>

void Func(int x, int k)
{
    int ret = x * k;
    printf("ret = %d\n", ret);
    return;
}

void Func1(int32_t x)
{
    std::cout << x << std::endl;
    return;
}

void Func2(int32_t x, int64_t y)
{
    std::cout << x << ' ' << y << std::endl;
    return;
}

void Func3(int32_t& x)
{
    std::cout << x << std::endl;
    return;
}

void Func4(int32_t& x, int64_t& y)
{
    std::cout << x << ' ' << y << std::endl << std::endl;
    return;
}

// 按值捕获
void test1()
{
    int32_t x;
    int64_t y;
    auto f1 = std::bind(Func1, x);
    auto f2 = std::bind(Func2, x, y);

    auto ff1 = [x]() { std::cout << x; };
    auto ff2 = [x, y]() { std::cout << x << y; };

    std::cout << sizeof(f1) << " " << sizeof(f2) << std::endl;  // 16 24
    std::cout << sizeof(ff1) << " " << sizeof(ff2) << std::endl;// 4 16
    return;
}

// 按引用捕获
void test2()
{
    int32_t x;
    int64_t y;
    // bind中引用捕获需要使用std::ref
    auto f1 = std::bind(Func3, std::ref(x));
    auto f2 = std::bind(Func4, std::ref(x), std::ref(y));

    // lambda表达式引用捕获需要使用&
    auto ff1 = [&x]() { std::cout << x; };
    auto ff2 = [&x, &y]() { std::cout << x << y; };

    std::cout << sizeof(f1) << " " << sizeof(f2) << std::endl;  // 16 24
    std::cout << sizeof(ff1) << " " << sizeof(ff2) << std::endl;// 8 16
    return;
}

int main()
{
    int k = 10;
    std::function<void(int)> func = std::bind(Func, std::placeholders::_1, k);

    // 执行的时刻，我知道了x的值
    int m = 456;
    //直接调用func执行
    func(m);    // ret = 4560
    
    test2();
    return 0;
}
