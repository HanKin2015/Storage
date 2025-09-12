/*******************************************************************************
* 文 件 名: stringstream_example.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.28
* 修改日期：2025.07.28
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <sstream>
#include <string>
#include <iomanip>
#include <iostream>

// 数值转字符串
void number2string()
{
    int num = 42;
    std::stringstream ss1;
    ss1 << num;           // 向流中写入整数
    std::string str = ss1.str();  // 获取流中的字符串 "42"
    std::cout << str << std::endl;
    
    std::stringstream ss2;
    ss2.precision(2);  // 设置精度
    ss2 << std::fixed << 3.14159;
    std::string s = ss2.str();  // "3.14"
    std::cout << s << std::endl;
    
    double price = 9.99;
    int quantity = 3;
    std::stringstream ss3;
    ss3 << "Total: $" << std::fixed 
       << std::setprecision(2) << (price * quantity);
    std::string result = ss3.str();  // "Total: $29.97"
    std::cout << result << std::endl;
}

// 字符串转数值
void string2number()
{
    std::string str = "3.14";
    std::stringstream ss(str);  // 用字符串初始化流
    double value;
    ss >> value;  // 从流中读取浮点数，value = 3.14
    std::cout << value << std::endl;

    // 如果转失败会怎么样
    str = "a1234";
    //错误做法ss << str;
    ss.clear();       // 重置流状态
    ss.str(str);
    ss >> value;
    if (ss.fail()) {
        std::cout << "转换失败！" << std::endl;
    } else {
        std::cout << "转换成功：" << value << std::endl;
    }
    std::cout << value << std::endl;
}

// 多类型拼接
void join()
{
    int age = 25;
    std::string name = "Alice";
    std::stringstream ss;
    ss << "Name: " << name << ", Age: " << age;
    std::string result = ss.str();  // "Name: Alice, Age: 25"
    std::cout << result << std::endl;
}

// 字符串分割
void split()
{
    std::string input = "apple banana cherry";
    std::stringstream ss(input);
    std::string word;
    while (ss >> word) {
        // 依次输出 "apple", "banana", "cherry"
        std::cout << word << std::endl;
    }
}

// 仅支持数值类型转字符串，简单直接，但功能单一
void to_string_example()
{
    std::string s = std::to_string(3.14);  // "3.140000"
    std::cout << s << std::endl;
}

template<typename T>
bool safeConvert(const std::string& str, T& value) {
    std::stringstream ss(str);
    return (ss >> value) && ss.eof();
}

void example()
{
    std::string name = "Bob";
    int age = 25;
    
    std::stringstream ss;
    ss << "Name: " << name << ", Age: " << age;
    std::string message = ss.str();
    std::cout << message << std::endl;  // 输出: Name: Bob, Age: 25
    
    // 数字格式化示例
    double pi = 3.1415926535;
    std::stringstream pi_ss;
    pi_ss << "Pi: " << std::fixed << std::setprecision(2) << pi;
    std::string formatted_pi = pi_ss.str();
    std::cout << formatted_pi << std::endl;  // 输出: Pi: 3.14
}

int main()
{
    number2string();
    string2number();
    join();
    split();
    to_string_example();

    std::string str = "123";
    int value;
    if (safeConvert(str, value)) {
        std::cout << "转换成功：" << value << std::endl;
    } else {
        std::cout << "转换失败" << std::endl;
    }
    example();
    return 0;
}