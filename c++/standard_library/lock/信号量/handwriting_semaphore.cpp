/*******************************************************************************
* 文 件 名: handwriting_semaphore.cpp
* 文件描述: 基于互斥锁和条件变量手动实现信号量
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.12
* 修改日期：2025.08.12
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <mutex>
#include <condition_variable>

// 手动实现计数信号量
template <int MaxCount>
class CountingSemaphore {
private:
    std::mutex mtx;
    std::condition_variable cv;
    int count;  // 当前计数（0 ≤ count ≤ MaxCount）

public:
    // 构造函数，初始计数为initial_count
    CountingSemaphore(int initial_count = 0) : count(initial_count) {}

    // 获取信号量（count--，若为0则等待）
    void acquire() {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [this] { return count > 0; });  // 等待count > 0
        count--;
    }

    // 释放信号量（count++，唤醒等待线程）
    void release() {
        std::lock_guard<std::mutex> lock(mtx);
        if (count < MaxCount) {
            count++;
            cv.notify_one();  // 唤醒一个等待线程
        }
    }

    // 非阻塞获取
    bool try_acquire() {
        std::lock_guard<std::mutex> lock(mtx);
        if (count > 0) {
            count--;
            return true;
        }
        return false;
    }
};

// 二进制信号量（简化版）
using BinarySemaphore = CountingSemaphore<1>;
