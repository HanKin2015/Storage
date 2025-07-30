/*******************************************************************************
* 文 件 名: reserve_example.cpp
* 文件描述: swap和初始化赋值区别
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.29
* 修改日期：2025.07.29
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> vec1;
    vec1.reserve(10);
    std::cout << vec1.size() << ' ' << vec1.capacity() << std::endl;    // 0 10
    
    std::vector<int> vec2(100);
    std::cout << vec2.size() << ' ' << vec2.capacity() << std::endl;    // 100 100

    vec2.resize(10);
    std::cout << vec2.size() << ' ' << vec2.capacity() << std::endl;    // 10 100

    std::vector<int> v({1, 2, 5, 6});
    vec2.swap(v);
    std::cout << v.size() << ' ' << v.capacity() << std::endl;          // 10 100
    std::cout << vec2.size() << ' ' << vec2.capacity() << std::endl;    // 4 4
    std::vector<int> vv(vec2.begin(), vec2.end());
    for (const auto& elem : vv) {
        std::cout << elem << std::endl;
    }
    return 0;
}