/*******************************************************************************
* 文 件 名: string2number.cpp
* 文件描述: std::stoi 函数用于将字符串转换为整数
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.03.11
* 修改日期：2025.03.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <cstdio>

// 如果传入的字符串为空，std::stoi 会抛出一个 std::invalid_argument 异常
// C++11 引入了 std::stoi、std::stol、std::stoll、std::stof、std::stod 和 std::stold 等函数，可以将字符串转换为整数或浮点数
void stoi_example()
{
    printf("----- %s[%d] -----\n", __FUNCTION__, __LINE__);
    std::string input;
    std::cout << "请输入一个整数（空字符串将使用默认值0）: ";
    std::getline(std::cin, input); // 从标准输入读取字符串

    int value = 0; // 设置默认值

    try {
        if (!input.empty()) { // 检查字符串是否为空
            value = std::stoi(input); // 尝试转换
        }
    } catch (const std::invalid_argument& e) {
        std::cout << "无效的输入，使用默认值0。" << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "输入的数字超出范围，使用默认值0。" << std::endl;
    }

    std::cout << "转换后的值: " << value << std::endl;   // 11

    std::string str = "11";
    value = std::stoi(str, nullptr, 16);
    std::cout << "转换后的值: " << value << std::endl;   // 17
}

void stringstream_example()
{
    printf("----- %s[%d] -----\n", __FUNCTION__, __LINE__);
    std::string strInt = "123";
    std::string strFloat = "123.45";

    // 使用 stringstream 转换为整数
    std::stringstream ssInt(strInt);
    int numInt;
    ssInt >> numInt;
    std::cout << "Integer: " << numInt << std::endl;

    // 使用 stringstream 转换为浮点数
    std::stringstream ssFloat(strFloat);
    float numFloat;
    ssFloat >> numFloat;
    std::cout << "Float: " << numFloat << std::endl;
}

// atoi 和 atof 是 C 风格的函数，可以将字符串转换为整数和浮点数，但它们不提供错误处理
// atol 不提供任何溢出或下溢的检测。如果输入字符串表示的数字超出了 long 的范围，atol 仍然会返回 0，这可能导致误解，因为 0 也可能是有效的转换结果
void atoi_example()
{
    printf("----- %s[%d] -----\n", __FUNCTION__, __LINE__);
    const char* strInt = "123";
    const char* strFloat = "123.45";

    // 转换为整数
    int numInt = std::atoi(strInt);
    std::cout << "Integer: " << numInt << std::endl;

    // 转换为浮点数
    double numFloat = std::atof(strFloat);
    std::cout << "Float: " << numFloat << std::endl;
}

// 当转换的结果超出了 long 类型的表示范围时，strtol 会返回 LONG_MAX 或 LONG_MIN，并将 errno 设置为 ERANGE
void strtol_example()
{
    printf("----- %s[%d] -----\n", __FUNCTION__, __LINE__);
    const char* strInt = "123";
    const char* strFloat = "123.45";

    char* end;

    // 转换为整数
    long numInt = std::strtol(strInt, &end, 16);
    std::cout << "Integer: " << numInt << " end: " << end << std::endl; // Integer: 291 end:

    double numFloat = std::strtol(strFloat, &end, 10);
    std::cout << "Float: " << numFloat << " end: " << end << std::endl; // Float: 123 end: .45
}

int main()
{
    stoi_example();
    stringstream_example();
    atoi_example();
    strtol_example();
    return 0;
}
