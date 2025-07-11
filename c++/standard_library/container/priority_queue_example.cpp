/*******************************************************************************
* 文 件 名: priority_queue_example.cpp
* 文件描述: priority_queue 是 C++ 标准库中的一个容器适配器，它提供了一种特殊的队列，其中元素按照优先级排序，优先级最高的元素总是位于队列的前端
* 备    注: 默认降序（大顶堆），即最大元素优先出队。使用 greater<int> 实现最小堆
* 作    者: HanKin
* 创建日期: 2025.07.09
* 修改日期：2025.07.09
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <queue>

int main()
{
    // 创建一个存储整数的最大堆
    std::priority_queue<int> pq;

    // 插入元素（O(log n)）
    pq.push(30);
    pq.push(10);
    pq.push(20);

    // 访问队首元素（最大值）
    std::cout << "Top: " << pq.top() << std::endl; // 输出: 30

    // 删除队首元素（O(log n)）
    pq.pop();
    std::cout << "Top after pop: " << pq.top() << std::endl; // 输出: 20

    // 检查队列是否为空
    std::cout << "Empty: " << (pq.empty() ? "Yes" : "No") << std::endl; // 输出: No

    // 获取队列大小
    std::cout << "Size: " << pq.size() << std::endl; // 输出: 2

	// 使用 greater<int> 实现最小堆
	std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
	minHeap.push(30);
	minHeap.push(10);
	minHeap.push(20);
	std::cout << "MinHeap Top: " << minHeap.top() << std::endl; // 输出: 10
    return 0;
}