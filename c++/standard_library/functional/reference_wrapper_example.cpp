/**
* 文 件 名: reference_wrapper_example.cpp
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
#include <vector>

void print(int& x)
{
    std::cout << x << std::endl;
    return;
}

int main()
{
    int n = 10;
    std::reference_wrapper<int> ref = std::ref(n);
    print(ref); // 输出: 10

    // 在容器中存储引用
    std::vector<std::reference_wrapper<int>> vec;
    vec.push_back(ref);
    vec[0].get() = 20;
    std::cout << n << std::endl; // 输出: 20

    return 0;
}
