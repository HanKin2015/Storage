/*******************************************************************************
* 文 件 名: set_custom_sort.cpp
* 文件描述: 如果需要自定义排序，可以在定义 std::set 时提供一个比较函数
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.05.20
* 修改日期：2025.05.20
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <set>

struct CustomCompare
{
    bool operator()(int a, int b) const {
        return a > b; // 降序排列
    }
};

int main()
{
    std::set<int, CustomCompare> mySet1 = {5, 1, 3, 4, 2};
    // 遍历元素
    std::cout << "Elements in the set (descending order): ";
    for (const auto& element : mySet1) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    std::set<int> mySet2 = {5, 1, 3, 4, 2};
    // 遍历元素
    std::cout << "Elements in the set (order): ";
    for (const auto& element : mySet2) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
Elements in the set (descending order): 5 4 3 2 1
Elements in the set (order): 1 2 3 4 5
*/