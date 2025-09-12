/*******************************************************************************
* 文 件 名: format_example.cpp
* 文件描述: C++20 标准引入了 <format> 头文件，其中的 std::format 函数提供了类型安全、功能丰富的字符串格式化能力
* 备    注: g++ format_example.cpp -std=c++20
* 作    者: HanKin
* 创建日期: 2025.09.12
* 修改日期：2025.09.12
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <format>
#include <string>
#include <iostream>

int main()
{
    std::string name = "Alice";
    int age = 30;
    
    // 基本格式化
    std::string message = std::format("Name: {}, Age: {}", name, age);
    std::cout << message << std::endl;  // 输出: Name: Alice, Age: 30
    
    // 数字格式化
    double pi = 3.1415926535;
    std::string formatted_pi = std::format("Pi: {:.2f}", pi);
    std::cout << formatted_pi << std::endl;  // 输出: Pi: 3.14
    
    // 位置参数
    int a = 10, b = 20;
    std::string result = std::format("{} + {} = {}", a, b, a + b);
    std::cout << result << std::endl;  // 输出: 10 + 20 = 30
    
    return 0;
}