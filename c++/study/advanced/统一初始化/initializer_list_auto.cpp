/*******************************************************************************
* 文 件 名: initializer_list_auto.cpp
* 文件描述: 场景2: auto 与列表初始化的演进 (C++11 vs C++17)
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.11
* 修改日期：2025.08.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <vector>
#include <typeinfo>

int main()
{
    // C++11 和 C++14 中的行为
    auto x1 = {10}; // 推导为 std::initializer_list<int>
    auto x2{10};    // C++11/14中也推导为 std::initializer_list<int>

    // C++17 中的行为
    /**
     * @brief 使用等号的复制列表初始化。
     * @description 规则不变，auto推导为std::initializer_list<T>。
     */
    auto a = {42}; // a 的类型是 std::initializer_list<int>

    /**
     * @brief 使用花括号的直接列表初始化（单个元素）。
     * @description C++17规则修正：推导为花括号内元素的类型。
     */
    auto b{42};    // b 的类型是 int

    /**
     * @brief 使用花括号的直接列表初始化（多个元素）。
     * @description C++17规则修正：由于存在歧义（应该是什么类型？），这成为一个编译错误。
     */
    auto c{4, 2}; // 编译错误！

    std::cout << "In C++17 and later:" << std::endl;
    std::cout << "auto a = {42};  // type of a is: " << typeid(a).name() << std::endl;
    std::cout << "auto b{42};      // type of b is: " << typeid(b).name() << std::endl;
    std::cout << "// auto c{4, 2}; // This would be a compile error." << std::endl;
    
    return 0;
}