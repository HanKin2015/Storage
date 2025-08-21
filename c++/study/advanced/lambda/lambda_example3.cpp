/*******************************************************************************
* 文 件 名: lambda_example3.cpp
* 文件描述: 在 C++ 中，lambda 表达式前加 + 是一种强制将 lambda 转换为函数指针的技巧
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.21
* 修改日期：2025.08.21
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

int main()
{
    // 无捕获的 lambda
    auto lambda = []() { std::cout << "Hello\n"; };
    
    // lambda 本身是函数对象
    lambda();  // 调用函数对象
    
    // +lambda 强制转换为函数指针
    auto func_ptr = +[]() { std::cout << "Hello\n"; };
    func_ptr();  // 调用函数指针
    
    return 0;
}