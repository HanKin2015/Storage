/*******************************************************************************
* 文 件 名: deque_example.cpp
* 文件描述: std::deque（双端队列，Double-ended Queue）是一种动态数组容器，支持在队列的两端高效地插入和删除元素。它结合了vector和list的部分优点
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <deque>
#include <iostream>

int main()
{
    // 初始化
    std::deque<int> dq = {1, 2, 3};
    
    // 尾部插入
    dq.push_back(4);  // dq = {1, 2, 3, 4}
    
    // 头部插入
    dq.push_front(0); // dq = {0, 1, 2, 3, 4}
    
    // 随机访问
    std::cout << dq[2] << std::endl; // 输出: 2
    
    // 遍历
    for (int num : dq) {
        std::cout << num << " ";
    }
    
    // 删除头部元素
    dq.pop_front(); // dq = {1, 2, 3, 4}
    
    // 删除尾部元素
    dq.pop_back();  // dq = {1, 2, 3}
    
    // 大小和容量
    std::cout << "\nSize: " << dq.size() << std::endl; // 输出: 3
    
    return 0;
}