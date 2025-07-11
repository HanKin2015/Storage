/*******************************************************************************
* 文 件 名: CAS_example.cpp
* 文件描述: 核心思想：“先比较内存中的值是否等于期望值，如果相等则更新为新值，否则返回失败”
* 备    注: CAS（Compare-And-Swap）是一种硬件级别的原子操作，用于实现无锁（lock-free）算法
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <atomic>
#include <iostream>

int main()
{
    std::atomic<int> data(10);
    int expected = 10;
    int new_value = 20;

    // 原子 CAS 操作
    bool success = data.compare_exchange_weak(expected, new_value);

    if (success) {
        std::cout << "CAS succeeded! data is now " << data << std::endl;
    } else {
        std::cout << "CAS failed! data is " << data 
                  << ", expected was " << expected << std::endl;
    }
    return 0;
}