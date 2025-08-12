/*******************************************************************************
* 文 件 名: thread_sequence_by_sem.cpp
* 文件描述: 控制线程执行顺序（如线程 1 → 线程 2 → 线程 3）需要通过同步机制实现
* 备    注: 使用信号量（Semaphore）
* 作    者: HanKin
* 创建日期: 2025.08.12
* 修改日期：2025.08.12
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <thread>
#include <semaphore>  // C++20 标准信号量

// 信号量初始值为0，表示“不可用”
std::counting_semaphore<1> sem2(0);  // 线程2的启动信号（由线程1释放）
std::counting_semaphore<1> sem3(0);  // 线程3的启动信号（由线程2释放）

void thread1() {
    std::cout << "Thread 1 running\n";
    sem2.release();  // 释放信号量，允许线程2执行
}

void thread2() {
    sem2.acquire();  // 等待线程1释放信号
    std::cout << "Thread 2 running\n";
    sem3.release();  // 释放信号量，允许线程3执行
}

void thread3() {
    sem3.acquire();  // 等待线程2释放信号
    std::cout << "Thread 3 running\n";
}

int main()
{
    std::thread t1(thread1);
    std::thread t2(thread2);
    std::thread t3(thread3);
    
    t1.join();
    t2.join();
    t3.join();
    
    return 0;
}
