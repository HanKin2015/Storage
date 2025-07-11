/*******************************************************************************
* 文 件 名: 参数包.cpp
* 文件描述: sizeof... 是专门用于参数包的运算符
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

// 递归终止函数
void printAll() {
    std::cout << std::endl;
}

// 递归函数模板
template<typename T, typename... Args>
void printAll(T first, Args... args) {
    std::cout << first;
    if constexpr (sizeof...(args) > 0) {
        std::cout << ", ";
    }
    printAll(args...); // 递归展开参数包
}

int main()
{
    printAll(1, 2.5, "hello"); // 输出：1, 2.5, hello
    return 0;
}