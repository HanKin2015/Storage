/*******************************************************************************
* 文 件 名: c++11_example.cpp
* 文件描述: std::chrono 是 C++11 引入的一个库，用于处理时间和时钟
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.04.25
* 修改日期：2025.04.25
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <chrono>
#include <memory>

int main()
{
    // std::enable_shared_from_this
    // std::chrono
    std::shared_ptr<int> p = std::make_shared<int>();
    std::cout << *p << std::endl;
    return 0;
}