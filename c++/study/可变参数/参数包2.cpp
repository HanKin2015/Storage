/*******************************************************************************
* 文 件 名: 参数包2.cpp
* 文件描述: Args... 是参数包类型，args... 是参数包对象
* 备    注: typename... Args：声明一个名为 Args 的模板参数包，它可以包含零个或多个类型。
*			Args... args：声明一个名为 args 的函数参数包，它的每个参数类型对应 Args 中的一个类型。
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

// 计算所有参数的和（支持不同类型，但要求可相加）
template<typename... Args>
auto sum_all(Args... args) {
    return (args + ...); // 折叠表达式（C++17）
}

int main()
{
    std::cout << sum_all(1, 2, 3) << std::endl; // 输出6
    std::cout << sum_all(1.5, 2.5, 3.5) << std::endl; // 输出7.5
    return 0;
}