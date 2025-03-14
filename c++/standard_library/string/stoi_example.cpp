/*******************************************************************************
* 文 件 名: stoi_example.cpp
* 文件描述: std::stoi 函数用于将字符串转换为整数
* 备    注: 如果传入的字符串为空，std::stoi 会抛出一个 std::invalid_argument 异常
* 作    者: HanKin
* 创建日期: 2025.03.11
* 修改日期：2025.03.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <string>
#include <stdexcept>

int main()
{
    std::string input;
    int defaultValue = 0;

    // 假设 input 是从某个地方获取的字符串
    // 例如：input = ""; // 空字符串
    std::cout << "请输入一个整数（空字符串将使用默认值0）: ";
    std::getline(std::cin, input); // 从标准输入读取字符串

    int value = defaultValue; // 设置默认值

    try {
        if (!input.empty()) { // 检查字符串是否为空
            value = std::stoi(input); // 尝试转换
        }
    } catch (const std::invalid_argument& e) {
        std::cout << "无效的输入，使用默认值0。" << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << "输入的数字超出范围，使用默认值0。" << std::endl;
    }

    std::cout << "转换后的值: " << value << std::endl;

    return 0;
}
