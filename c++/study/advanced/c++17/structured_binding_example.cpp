/*******************************************************************************
* 文 件 名: structured_binding_example.cpp
* 文件描述: 结构化绑定
* 备    注: 标准库中的std::tuple基于可变参数模板实现
* 作    者: HanKin
* 创建日期: 2025.07.10
* 修改日期：2025.07.10
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <tuple>
#include <cstring>
#include <map>

struct Point { int x; int y; };

void example()
{
    // 1. 拆解结构体
    Point p = {10, 20};
    auto [x, y] = p; // x=10, y=20（自动推导类型为int）
    
    // 2. 拆解tuple
    auto t = std::make_tuple("C++17", 2017, 3.14);
    auto [lang, year, pi] = t; // lang=const char*, year=int, pi=double
    
    // 3. 遍历map（直接获取key和value，无需->first/->second）
    std::map<std::string, int> score = {{"Alice", 90}, {"Bob", 85}};
    for (const auto& [name, s] : score) {
        std::cout << name << ": " << s << "\n";
    }
}

int main()
{
    //std::tuple t = std::make_tuple(1, "hello", 3.14);
    std::tuple<int, std::string, int> t = std::make_tuple(1, "hello", 3.14);    // 1 hello 3
    auto [a, b, c] = t;
    std::cout << a << ' ' << b << ' ' << c << std::endl;    // 1 hello 3.14
    
    example();
    return 0;
}