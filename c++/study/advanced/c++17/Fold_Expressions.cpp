/*******************************************************************************
* 文 件 名: Fold_Expressions.cpp
* 文件描述: 简化「可变参数模板」的遍历逻辑，无需递归即可对参数包进行「累加、拼接、逻辑判断」等操作，是模板元编程的重要优化。
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.25
* 修改日期：2025.08.25
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <string>

// 1. 数值求和（折叠方向不影响结果，左折叠/右折叠均可）
template <typename... Args>
auto sum(Args&&... args) {
    return (args + ...); // 右折叠：(1 + (2 + (3 + 4)))
}

// 2. 字符串拼接（确保至少第一个参数是std::string，右折叠更直观）
template <typename... Args>
std::string concat(const std::string& first, Args&&... rest) {
    return (first + ... + rest); // 左折叠：((first + rest1) + rest2) + ...
}

int main()
{
    // 数值求和：正确
    std::cout << sum(1, 2, 3, 4) << "\n"; // 输出10

    // 字符串拼接：将第一个参数显式转为std::string，后续可接字符串字面值
    std::cout << concat(std::string("C++"), "17", " is ", "great!") << "\n"; // 输出"C++17 is great!"
    
    // 也可以直接传std::string字面量（C++14起支持）
    using namespace std::string_literals;       // 必须包含此命名空间才能使用`s`
    std::cout << concat("C++"s, "17", " is ", "great!") << "\n"; // 注意"s"后缀，需包含<string>
    return 0;
}
    