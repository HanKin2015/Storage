/*******************************************************************************
* 文 件 名: optional_example.cpp
* 文件描述: 表示「可能存在的值」，避免用nullptr或特殊值（如-1）表示「无值」，增强类型安全
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.25
* 修改日期：2025.08.25
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <optional>
#include <string>
#include <iostream>

// 查找字符串中第一个数字，找到返回数字，否则返回"无值"
std::optional<char> findFirstDigit(const std::string& s) {
    for (char c : s) {
        if (isdigit(c)) {
            return c; // 返回有值的optional
        }
    }
    return std::nullopt; // 返回无值（替代返回'\0'等模糊值）
}

int main()
{
    auto res1 = findFirstDigit("C++17");
    if (res1.has_value()) { // 判断是否有值
        std::cout << "Found: " << res1.value() << "\n"; // 输出'1'
    }

    auto res2 = findFirstDigit("Hello");
    if (!res2) { // 简写判断
        std::cout << "No digit found\n";
    }
    return 0;
}