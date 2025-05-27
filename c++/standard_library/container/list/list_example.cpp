/*******************************************************************************
* 文 件 名: list_example.cpp
* 文件描述: 提供了双向链表的实现。它允许在任意位置高效地插入和删除元素，但在随机访问方面的性能较差（通过索引直接访问元素）
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.05.22
* 修改日期：2025.05.22
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <list>
#include <algorithm> // for std::find

int main()
{
    std::list<int> myList = {1, 2, 3, 4, 5};

    // 添加元素
    myList.push_back(10); // 在末尾添加 10
    myList.push_front(5); // 在开头添加 5
    myList.insert(myList.begin(), 1); // 在开头插入 1

    // 遍历并打印元素
    std::cout << "List elements: ";
    for (const auto& value : myList) {
        std::cout << value << " ";
    }
    std::cout << std::endl; // List elements: 1 5 1 2 3 4 5 10

    // 删除元素
    myList.pop_back(); // 删除末尾元素
    myList.pop_front(); // 删除开头元素
    myList.remove(3); // 删除所有值为 3 的元素
    myList.erase(myList.begin()); // 删除第一个元素

    // 打印删除后的元素
    std::cout << "After removing 3: ";
    for (auto it = myList.begin(); it != myList.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl; // After removing 3: 1 2 4 5

    // 使用 std::find 查找元素
    auto it = std::find(myList.begin(), myList.end(), 4);
    if (it != myList.end()) {
        std::cout << "Found: " << *it << std::endl; // Found: 4
    } else {
        std::cout << "Not found." << std::endl;
    }

    // 其他常用函数
    std::cout << "Size: " << myList.size() << std::endl;    // Size: 4
    if (myList.empty()) {
        std::cout << "List is empty." << std::endl;
    }
    myList.clear(); // 清空列表

    return 0;
}