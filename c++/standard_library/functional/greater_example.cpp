/**
* 文 件 名: greater_example.cpp
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

    // 使用 std::greater 进行降序排序
    std::sort(vec.begin(), vec.end(), std::greater<int>());
    for (int n : vec) {
        std::cout << n << " "; // 输出: 5 4 3 2 1
    }
    std::cout << std::endl;

    // 使用 std::equal_to 查找等于 3 的元素
    auto it = std::find_if(vec.begin(), vec.end(), std::bind(std::equal_to<int>(), std::placeholders::_1, 3));
    if (it != vec.end()) {
        std::cout << "Found: " << *it << std::endl; // 输出: Found: 3
    }

    return 0;
}
