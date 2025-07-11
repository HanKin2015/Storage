/*******************************************************************************
* 文 件 名: SpinLock_example.cpp
* 文件描述: C++11 引入的标准库组件，用于实现原子操作。原子操作是不可中断的操作，在多线程环境中无需锁即可保证数据一致性，常用于实现无锁（lock-free）算法
* 备    注: 底层实现：依赖硬件原子指令（如 CPU 的 CAS 操作），性能通常优于互斥锁
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>

class SpinLock {
private:
    std::atomic<bool> locked_{false};  // 原子标志，表示锁的状态

public:
    void lock() {
        bool expected = false;
        // 持续尝试原子地将 locked_ 从 false 设为 true
        while (!locked_.compare_exchange_weak(expected, true, 
                                              std::memory_order_acquire,
                                              std::memory_order_relaxed)) {
            expected = false;  // 重置期望值
            // 可选：添加短暂延迟以减少 CPU 使用率
            // std::this_thread::yield();
        }
    }

    void unlock() {
        locked_.store(false, std::memory_order_release);
    }
};

int main()
{
	SpinLock spin;
	spin.lock();  // 获取锁
	// 临界区
	// ...
	spin.unlock();  // 释放锁
	return 0;
}