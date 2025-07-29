/*******************************************************************************
* 文 件 名: greater_example.cpp
* 文件描述: 属于标准库提供的一个函数对象（也被叫做仿函数）。它的主要功能是对两个int类型的数值进行比较，判断第一个数是否大于第二个数，并且会返回比较结果的布尔值。这个函数对象常被用于需要定义降序排序规则或者构建最小堆的场景。
* 备    注: 相反的函数对象为std::less<int> comp
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <queue>

int main()
{
    // 1. 运用在std::sort中实现降序排列
    std::vector<int> numbers = {5, 2, 8, 1, 9};
    std::sort(numbers.begin(), numbers.end(), std::greater<int>());
    // 输出结果：9 8 5 2 1
    for (int num : numbers) std::cout << num << " ";
    std::cout << std::endl;

    // 2. 用于std::priority_queue构建最大堆
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;  // 注意这个greater特殊性
    minHeap.push(5);
    minHeap.push(2);
    minHeap.push(8);
    // 输出结果：2 5 8
    while (!minHeap.empty()) {
        std::cout << minHeap.top() << " ";
        minHeap.pop();
    }
    std::cout << std::endl;

    // 3. 直接调用函数对象
    std::greater<int> comp;
    bool result = comp(10, 5); // 等价于 10 > 5，结果为true
    std::cout << std::boolalpha << result << std::endl;

    return 0;
}