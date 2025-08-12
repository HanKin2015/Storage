/*******************************************************************************
* 文 件 名: thread_sequence_by_atomic.cpp
* 文件描述: 控制线程执行顺序（如线程 1 → 线程 2 → 线程 3）需要通过同步机制实现
* 备    注: 使用原子变量（Atomic Variable）
* 作    者: HanKin
* 创建日期: 2025.08.12
* 修改日期：2025.08.12
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> step(1);  // 原子变量，确保线程安全的读写

void thread1() {
    while (step != 1) {}  // 忙等，直到step为1
    std::cout << "Thread 1 running\n";
    step = 2;  // 推进步骤
}

void thread2() {
    while (step != 2) {}  // 等待线程1完成
    std::cout << "Thread 2 running\n";
    step = 3;  // 推进步骤
}

void thread3() {
    while (step != 3) {}  // 等待线程2完成
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
