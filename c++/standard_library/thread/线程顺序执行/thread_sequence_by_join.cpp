/*******************************************************************************
* 文 件 名: thread_sequence_by_join.cpp
* 文件描述: 控制线程执行顺序（如线程 1 → 线程 2 → 线程 3）需要通过同步机制实现
* 备    注: 使用 join () 串行化执行
* 作    者: HanKin
* 创建日期: 2025.08.11
* 修改日期：2025.08.11
*
* Copyright (c) 2025 HanKin. All rights reserved.

*******************************************************************************/
#include <iostream>
#include <thread>

void thread1() {
    std::cout << "Thread 1 running\n";
}

void thread2() {
    std::cout << "Thread 2 running\n";
}

void thread3() {
    std::cout << "Thread 3 running\n";
}

int main() {
    // 启动线程1并等待其完成
    std::thread t1(thread1);
    t1.join();  // 主线程阻塞，直到t1执行完毕
    
    // 启动线程2并等待其完成
    std::thread t2(thread2);
    t2.join();  // 确保t2在t1之后执行
    
    // 启动线程3并等待其完成
    std::thread t3(thread3);
    //t1.join();    // 写在这里的话顺序就不固定了
    //t2.join();
    t3.join();  // 确保t3在t2之后执行
    
    return 0;
}
