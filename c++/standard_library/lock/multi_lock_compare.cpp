/*******************************************************************************
* 文 件 名: multi_lock_compare.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.06
* 修改日期：2025.08.06
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <mutex>
#include <chrono>
#include <shared_mutex>

std::mutex m1, m2, m3;

// std::lock 用于同时锁定多个互斥量，它的特点是要么全部锁定成功，要么全部失败（不会部分锁定）。
void lock_example()
{
    // error: no matching function for call to ‘lock(std::mutex&)’
    // 不支持单个互斥锁锁定，至少2个。单个和m2.lock()一样
    //std::lock(m2);
    m2.lock();
    std::cout << "单个互斥量锁定成功" << std::endl;
    try {
        std::cout << "再次尝试互斥量锁定..." << std::endl;
        std::lock(m1, m2);  // 尝试同时锁定m1和m2
        // 若执行到这里，说明全部锁定成功
        std::cout << "所有互斥量锁定成功" << std::endl;
        
        // 手动解锁（因为std::lock不管理生命周期）
        m1.unlock();
        m2.unlock();
    } catch (...) { // 只会阻塞啊，不会抛出异常
        // 锁定失败（可能是某个互斥量无法锁定）
        std::cout << "锁定失败" << std::endl;
    }
    return;
}

// shared_lock和unique_lock通过try_lock/try_lock_for/try_lock_until返回值判断
// lock通过阻塞判断
// lock_guard 无法直接判断锁定成功
void judge_lock_result()
{
    std::shared_mutex sm;

    // 尝试获取读锁（共享）
    std::shared_lock<std::shared_mutex> read_lock(sm, std::defer_lock);
    if (read_lock.try_lock()) {
        std::cout << "读锁获取成功" << std::endl;
    }

    // 尝试获取写锁（独占）
    std::unique_lock<std::shared_mutex> write_lock(sm, std::defer_lock);
    if (write_lock.try_lock()) {
        std::cout << "写锁获取成功" << std::endl;
    }

    // 只有timed_mutex有这个超时锁定
    std::timed_mutex m;
    std::unique_lock<std::timed_mutex> lock(m, std::defer_lock);
    // 尝试锁定，最多等待100毫秒
    if (lock.try_lock_for(std::chrono::milliseconds(100))) {
        std::cout << "100ms内锁定成功" << std::endl;
    } else {
        std::cout << "100ms内锁定失败" << std::endl;
    }
}

int main()
{
    //lock_example();
    judge_lock_result();
    return 0;
}