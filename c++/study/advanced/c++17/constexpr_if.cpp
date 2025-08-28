/*******************************************************************************
* 文 件 名: constexpr_if.cpp
* 文件描述: 在编译期根据条件决定是否实例化代码分支，实现「编译时多态」，避免运行时分支开销，且不生成无用代码。
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.25
* 修改日期：2025.08.25
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <type_traits>
#include <iostream>

// 编译时判断类型，分别处理int和其他类型
template <typename T>
void printType(const T& val)
{
    if constexpr (std::is_integral_v<T>) { // 编译期判断：T是否为整数类型
        std::cout << "Integer: " << val << "\n";
    } else if constexpr (std::is_floating_point_v<T>) { // 编译期判断：是否为浮点型
        std::cout << "Float: " << val << "\n";
    } else {
        std::cout << "Other type\n";
    }
}

int main()
{
    printType(10);    // 编译后仅保留"Integer"分支
    printType(3.14);  // 编译后仅保留"Float"分支
    printType("str"); // 编译后仅保留"Other type"分支
    return 0;
}