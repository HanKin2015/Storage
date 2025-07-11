/*******************************************************************************
* 文 件 名: queue_example.cpp
* 文件描述: 一种容器适配器（Container Adapter），它提供了队列（FIFO，先进先出）的抽象接口。它不直接存储元素，而是封装其他容器（如 deque、list 或 vector），并限制对元素的访问方式，确保元素只能从队列尾部插入、从头部删除
* 备    注: 默认使用 std::deque 作为底层容器，也可指定其他容器（如 list 或 vector）
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <queue>
#include <iostream>

int main()
{
    std::queue<int> q;
    
    // 入队操作
    q.push(10);  // 队列: [10]
    q.push(20);  // 队列: [10, 20]
    q.push(30);  // 队列: [10, 20, 30]
    
    // 访问队首元素
    std::cout << "Front: " << q.front() << std::endl;  // 输出: 10
    
    // 访问队尾元素
    std::cout << "Back: " << q.back() << std::endl;    // 输出: 30
    
    // 出队操作
    q.pop();  // 队列: [20, 30]
    std::cout << "Front after pop: " << q.front() << std::endl;  // 输出: 20
    
    // 检查队列是否为空
    std::cout << "Empty: " << (q.empty() ? "Yes" : "No") << std::endl;  // 输出: No
    
    // 获取队列大小
    std::cout << "Size: " << q.size() << std::endl;  // 输出: 2
    
    return 0;
}