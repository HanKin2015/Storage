/**
* 文 件 名: plus_example.cpp
* 文件描述: 学习functional库
* 备    注：g++ placeholders_example.cpp -std=c++11
* 作    者: HanKin
* 创建日期: 2024.09.29
* 修改日期：2024.09.29
*
* Copyright (c) 2024 HanKin. All rights reserved.
*/
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>

int main()
{
    std::vector<int> vec = {1, 2, 3, 4, 5};

    // 使用 std::plus 进行加法运算
    std::transform(vec.begin(), vec.end(), vec.begin(), std::plus<int>());
    for (int n : vec) {
        std::cout << n << " "; // 输出: 2 4 6 8 10
    }
    std::cout << std::endl;

    // 使用 std::multiplies 进行乘法运算
    std::transform(vec.begin(), vec.end(), vec.begin(), std::multiplies<int>());
    for (int n : vec) {
        std::cout << n << " "; // 输出: 4 16 36 64 100
    }
    std::cout << std::endl;

    return 0;
}
