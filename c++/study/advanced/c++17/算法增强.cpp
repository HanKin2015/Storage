/*******************************************************************************
* 文 件 名: 算法增强.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.25
* 修改日期：2025.08.25
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <algorithm>
#include <vector>
// #include <execution>

int main()
{
    // std::min(max, std::max(val, min))的简洁版
    int x = std::clamp(100, 0, 50); // x=50（后面2个参数是范围）
    std::cout << x << std::endl;

    // 可指定并行执行（std::execution::par），利用多核 CPU 提升性能
    // 该特性依赖 Intel TBB（Threading Building Blocks）库实现并行计算，但编译时没有正确链接 TBB 库，导致链接器无法找到相关实现
    std::vector<int> vec{3, 2, 1, 5, 6};
    //std::sort(std::execution::par, vec.begin(), vec.end());
    for_each(vec.begin(), vec.end(), [](int elem) {
        std::cout << elem << std::endl;
    });
    return 0;
}