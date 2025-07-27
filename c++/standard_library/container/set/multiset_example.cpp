/*******************************************************************************
* 文 件 名: multiset_example.cpp
* 文件描述: 处理有序重复元素集合的理想容器，通过红黑树结构提供高效的插入、删除和查找操作
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.23
* 修改日期：2025.07.23
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <multiset>
#include <iostream>

#define 

int main()
{
    int arr[] = {1, 2, 2, 3};
    std::multiset<int> ms = {1, 2, 2, 2, 3};
    
    // 自定义比较器（降序）
    std::multiset<int, std::greater<int>> ms2;

    // 1. 查找第一个等于 2 的元素
    auto lower = ms.lower_bound(2);  // 返回第一个 >=2 的迭代器

    // 2. 查找最后一个等于 2 的元素的下一个位置
    auto upper = ms.upper_bound(2);  // 返回第一个 >2 的迭代器

    // 3. 遍历所有 2
    for (auto it = lower; it != upper; ++it) {
        std::cout << *it << " ";  // 输出: 2 2 2
    }

    // 4. 统计 2 的数量
    size_t cnt = std::distance(lower, upper);  // 等价于 ms.count(2)

    // 5. 删除所有 2
    ms.erase(lower, upper);  // 或 ms.erase(2);
    return 0;
}