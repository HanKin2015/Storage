/**
* 文 件 名: vector_at_[].cpp
* 文件描述: at是一个成员函数，如果索引超出范围，会抛出 std::out_of_range 异常，operator[]不进行边界检查，如果索引超出范围，行为是未定义的（可能导致程序崩溃或访问非法内存）
* 备    注: g++ vector_at_[].cpp --std=c++11
* 作    者: HanKin
* 创建日期: 2025.03.10
* 修改日期：2025.03.10
*
* Copyright (c) 2025 HanKin. All rights reserved.
*/

#include <cstdio>
#include <iostream>
#include <vector>

int main()
{
    std::vector<int> vec = {10, 20, 30};

    // 使用 at() 进行安全访问
    try {
        std::cout << vec.at(1) << std::endl; // 输出 20
        std::cout << vec.at(3) << std::endl; // 会抛出异常
    } catch (const std::out_of_range& e) {
        std::cout << "Out of range: " << e.what() << std::endl; // vector::_M_range_check: __n (which is 3) >= this->size() (which is 3)
    }

    // 使用 [] 进行直接访问
    std::cout << vec[1] << std::endl; // 输出 20
    // std::cout << vec[3] << std::endl; // 未定义行为，可能导致崩溃（输出0，上面会抛出异常一定会崩溃）

    return 0;
}