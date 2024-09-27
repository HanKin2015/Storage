/**
* 文 件 名: function_example.cpp
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

void freeFunction(int x)
{
    std::cout << "Free function called with " << x << std::endl;
    return;
}

int main()
{
    // 使用 std::function 包装自由函数
    std::function<void(int)> func = freeFunction;
    func(10);

    // 使用 std::function 包装 lambda 表达式
    std::function<void(int)> lambda = [](int x) {
        std::cout << "Lambda called with " << x << std::endl;
    };
    lambda(20);

    return 0;
}
