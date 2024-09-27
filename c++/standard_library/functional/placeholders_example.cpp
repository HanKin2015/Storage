/**
* 文 件 名: placeholders_example.cpp
* 文件描述: 学习functional库
* 备    注：g++ placeholders_example.cpp -std=c++11
* 作    者: HanKin
* 创建日期: 2024.09.27
* 修改日期：2024.09.27
*
* Copyright (c) 2024 HanKin. All rights reserved.
*/
#include <iostream>
#include <functional>

void multiply(int a, int b)
{
    std::cout << "Product: " << a * b << std::endl;
    return;
}

int main()
{
    // 绑定第二个参数为 5
    auto boundFunc = std::bind(multiply, std::placeholders::_1, 5);
    boundFunc(4); // 输出: Product: 20

    return 0;
}


