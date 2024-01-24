/**
* 文 件 名: tuple_example.cpp
* 文件描述: 在 C++11 中引入了 std::tuple 类模板，它是一个通用的元组（Tuple）类，用于存储多个不同类型的值。std::tuple 可以看作是一个固定大小的、类型安全的、不可修改的集合。
* 备    注: 编译器版本过旧：确保你的编译器版本足够新，以支持 C++17 中的结构化绑定。例如，GCC 需要至少是 7.1 版本，Clang 需要至少是 4.0 版本。
* 作    者: HanKin
* 创建日期: 2024.01.22
* 修改日期：2024.01.22
*
* Copyright (c) 2024 HanKin. All rights reserved.
*/
#include <iostream>
#include <tuple>

int main() {
    // 创建一个包含 int、double 和字符串的 tuple
    std::tuple<int, double, std::string> myTuple(42, 3.14, "Hello");

    // 使用 std::get 访问 tuple 中的元素（通过索引）
    int intValue = std::get<0>(myTuple);
    double doubleValue = std::get<1>(myTuple);
    std::string stringValue = std::get<2>(myTuple);
    std::cout << "int value: " << intValue << std::endl;
    std::cout << "double value: " << doubleValue << std::endl;
    std::cout << "string value: " << stringValue << std::endl;

    // 结构化绑定解包 tuple 中的值(结构化绑定是 C++17 新引入的特性，它允许你方便地解包 tuple、pair 或结构体中的元素)
    auto [intValue1, doubleValue1, stringValue1] = myTuple;
    std::cout << "int value: " << intValue1 << std::endl;
    std::cout << "double value: " << doubleValue1 << std::endl;
    std::cout << "string value: " << stringValue1 << std::endl;
    
    // 使用 std::tie 解包 tuple 中的值
    int intValue2;
    double doubleValue2;
    std::string stringValue2;
    std::tie(intValue2, doubleValue2, stringValue2) = myTuple;
    std::cout << "int value: " << intValue2 << std::endl;
    std::cout << "double value: " << doubleValue2 << std::endl;
    std::cout << "string value: " << stringValue2 << std::endl;
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #g++ a.cpp -std=c++11
[root@ubuntu0006:~/cmake] #./a.out
int value: 42
double value: 3.14
string value: Hello
int value: 42
double value: 3.14
string value: Hello
*/