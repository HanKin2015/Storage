/*******************************************************************************
* 文 件 名: exception_what.cpp
* 文件描述: what()，用于返回异常信息的 C 风格字符串
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.03.10
* 修改日期：2025.03.10
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <stdexcept>

void mightGoWrong()
{
    bool errorOccurred = true; // 模拟错误发生
    if (errorOccurred) {
        throw std::runtime_error("Something went wrong!"); // 抛出异常
    }
}

int main()
{
    try {
        mightGoWrong(); // 尝试调用可能出错的函数
    } catch (const std::exception& e) { // 捕获所有标准异常
        std::cout << "Caught an exception: " << e.what() << std::endl; // Caught an exception: Something went wrong!
    }

    return 0;
}
