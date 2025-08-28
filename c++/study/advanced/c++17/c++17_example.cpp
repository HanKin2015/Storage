/*******************************************************************************
* 文 件 名: c++17_example.cpp
* 文件描述: 高级用法杂烩
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.04.24
* 修改日期：2025.04.24
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <any>

int main()
{
    std::any anyVal = 123.45; // 这里存储的是 double 类型
    try {
        std::cout << "Any: " << std::any_cast<double>(anyVal) << std::endl; // 正确地转换为 double
    } catch (const std::bad_any_cast& e) {
        std::cerr << "Bad any cast: " << e.what() << std::endl; // 捕获类型转换错误
    }
    return 0;
}