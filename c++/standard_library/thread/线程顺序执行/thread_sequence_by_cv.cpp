/*******************************************************************************
* 文 件 名: thread_sequence_by_cv.cpp
* 文件描述: 控制线程执行顺序（如线程 1 → 线程 2 → 线程 3）需要通过同步机制实现
* 备    注: 使用条件变量（Condition Variable）
* 作    者: HanKin
* 创建日期: 2025.08.11
* 修改日期：2025.08.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex mtx;
std::condition_variable cv;
int step = 1;  // 控制步骤：1→2→3

// 线程1：打印后通知线程2
void thread1() {
    std::unique_lock<std::mutex> lock(mtx);
    // 确保线程1先执行（step为1时）
    cv.wait(lock, []{ return step == 1; });
    
    std::cout << "Thread 1 running\n";
    
    // 步骤推进，通知线程2
    step = 2;
    cv.notify_all();
}

// 线程2：等待线程1完成后执行，再通知线程3
void thread2() {
    std::unique_lock<std::mutex> lock(mtx);
    // 等待step变为2（线程1执行完毕）
    cv.wait(lock, []{ return step == 2; });
    
    std::cout << "Thread 2 running\n";
    
    // 步骤推进，通知线程3
    step = 3;
    cv.notify_all();
}

// 线程3：等待线程2完成后执行
void thread3() {
    std::unique_lock<std::mutex> lock(mtx);
    // 等待step变为3（线程2执行完毕）
    cv.wait(lock, []{ return step == 3; });
    
    std::cout << "Thread 3 running\n";
}

int main() {
    // 启动线程（启动顺序不影响执行顺序）
    std::thread t3(thread3);
    std::thread t2(thread2);
    std::thread t1(thread1);
    
    // 等待所有线程结束
    t1.join();
    t2.join();
    t3.join();
    
    return 0;
}
