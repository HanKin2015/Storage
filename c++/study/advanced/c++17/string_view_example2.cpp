/*******************************************************************************
* 文 件 名: string_view_example2.cpp
* 文件描述:  C++17 引入的一个轻量级字符串视图类，主要用于高效地访问字符串数据而不拥有其所有权，旨在解决传统 const std::string& 传递时可能产生的性能开销问题
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.18
* 修改日期：2025.08.18
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <string_view>
#include <string>
#include <cstdio>
#include <cstring>
#include <iostream>

// 与 std::string 的转换
void string_view_to_string()
{
    std::string_view sv = "hello";

    // string_view → string（会触发拷贝）
    std::string str = std::string(sv);  // 或 sv.data()（需确保以\0结尾）

    // string → string_view（无拷贝，直接指向原始数据）
    std::string_view sv2 = str;
    std::cout << sv << std::endl;
    std::cout << str << std::endl;
    std::cout << sv2 << std::endl;
}

// 生命周期管理
std::string_view get_view()
{
    std::string s = "temporary";  // s 在函数结束后销毁
    return std::string_view(s);   // 返回悬垂视图，危险！
}

// 不一定以 \0 结尾
void data_example()
{
    std::string str = "abcdef";
    std::string_view sv = str.substr(1, 3);  // 指向 "bcd"，但 data() 后无 \0
    printf("%s\n", sv.data());  // 危险！可能输出乱码（直到遇到 \0）
}

int main()
{
    // 从 std::string 构造
    std::string str = "hello";
    std::string_view sv1 = str;  // 指向 str 的数据，长度 5

    // 从 C 风格字符串构造（自动计算长度）
    const char* cstr = "world";
    std::string_view sv2 = cstr;  // 指向 cstr，长度 5

    // 从字符串字面量直接构造
    std::string_view sv3 = "string_view";  // 长度 11

    // 构造子字符串（起始位置，长度）
    std::string_view sv4 = sv3.substr(0, 6);  // "string"
    std::string_view sv5(sv3.data() + 7, 4);  // "view"（指针 + 长度）

    string_view_to_string();
    data_example();
    return 0;
}