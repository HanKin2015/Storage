/**
* 文 件 名: bind_example.cpp
* 文件描述: 学习functional库
* 备    注：g++ function_example.cpp -std=c++11
* 作    者: HanKin
* 创建日期: 2024.09.27
* 修改日期：2024.09.27
*
* Copyright (c) 2024 HanKin. All rights reserved.
*/
#include <iostream>
#include <functional>

void add(int a, int b)
{
    std::cout << "Sum: " << a + b << std::endl;
    return;
}

int main()
{
    // 绑定第一个参数为 10
    auto boundFunc = std::bind(add, 10, std::placeholders::_1);
    boundFunc(20); // 输出: Sum: 30

    return 0;
}

