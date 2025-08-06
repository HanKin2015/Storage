/*******************************************************************************
* 文 件 名: shared_mutex_compare.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.06
* 修改日期：2025.08.06
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <mutex>
#include <vector>
#include <shared_mutex>

// 线程安全的vector封装
template <typename T>
class ConcurrentVector {
private:
    std::vector<T> data;
    mutable std::shared_mutex mtx;  // 读写锁（C++17）

public:
    // 读操作（共享锁）
    T get(size_t index) const {
        std::shared_lock<std::shared_mutex> lock(mtx);  // 多个读线程可同时进入
        return data[index];
    }

    // 写操作（独占锁）
    void push_back(const T& value) {
        std::unique_lock<std::shared_mutex> lock(mtx);  // 仅一个写线程可进入
        data.push_back(value);
    }
};