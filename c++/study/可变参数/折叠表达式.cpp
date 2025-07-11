/*******************************************************************************
* 文 件 名: 折叠表达式.cpp
* 文件描述: 在 C++17 及以后的版本中，折叠表达式（Folding Expressions） 是一种用于简化可变参数模板展开的语法糖。它允许你直接对参数包中的所有参数执行二元运算，无需编写递归模板。
* 备    注: 一元折叠：对参数包 args 中的所有参数应用二元运算符 op
*			二元折叠：在参数包展开的基础上，增加一个初始值 init
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstring>

// 一元折叠有问题，std::string和const char*无法直接进行加法计算
template<typename... Args>
auto sum_right(Args... args) {
    return (args + ... + std::string{});  // 二元右折叠，等价于：(a1 + (a2 + (... + an)))
}

template<typename... Args>
auto sum_left(Args... args) {
    return (std::string{} + ... + args);  // 二元左折叠，等价于：(((a1 + a2) + ...) + an)
}

int main()
{
	// 右折叠：std::string("a") + "b" + "c"
    // 等价于：("a" + "b") + "c"
    std::cout << sum_right(std::string("a"), "b", "c") << std::endl; // 输出 "abc"
    
    // 左折叠：std::string("a") + "b" + "c"
    // 等价于："a" + ("b" + "c")
    std::cout << sum_left(std::string("a"), "b", "c") << std::endl; // 输出 "abc"
	return 0;
}