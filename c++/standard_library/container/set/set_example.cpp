/*******************************************************************************
* 文 件 名: set_example.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.04.15
* 修改日期：2025.04.15
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <set>

int main()
{
    // 定义并初始化一个 set
    std::set<int> mySet = {5, 1, 3, 4, 2};

    // 插入元素
    mySet.insert(6);
    mySet.insert(3); // 重复元素，不会插入

    // 查找元素
    auto it = mySet.find(3);
    if (it != mySet.end()) {
        std::cout << "Found: " << *it << std::endl;
    } else {
        std::cout << "Not found." << std::endl;
    }

    // 删除元素
    mySet.erase(4);
    mySet.erase(14);

    // 遍历元素
    std::cout << "Elements in the set: ";
    for (const auto& element : mySet) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}
/*
[root@ubuntu0006:~] #g++ set_example -std=c++11
[root@ubuntu0006:~] #./a.out 
Found: 3
Elements in the set: 1 2 3 5 6
*/