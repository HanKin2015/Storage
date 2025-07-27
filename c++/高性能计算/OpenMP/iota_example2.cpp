/*******************************************************************************
* 文 件 名: iota_example2.cpp
* 文件描述: 源自希腊字母 ι（iota），在数学中常用于表示递增值
* 备    注: 自定义类型（需支持 operator++）
* 作    者: HanKin
* 创建日期: 2025.07.23
* 修改日期：2025.07.23
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <numeric>
#include <vector>
#include <iostream>

struct Counter {
    int value;
    Counter& operator++() { ++value; return *this; }
};

int main()
{
    std::vector<Counter> counters(3);
    std::iota(counters.begin(), counters.end(), Counter{10});
    
    for (const auto& c : counters) {
        std::cout << c.value << " ";  // 输出: 10 11 12
    }
    std::cout << std::endl;
    return 0;
}