/*******************************************************************************
* 文 件 名: semaphore_concurrency.cpp
* 文件描述: 限制并发访问（如最多 3 个线程同时访问资源）
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.12
* 修改日期：2025.08.12
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <thread>
#include <semaphore>
#include <vector>

const int MAX_CONCURRENT = 3;  // 最大并发线程数
std::counting_semaphore<MAX_CONCURRENT> sem(MAX_CONCURRENT);  // 初始值为3

void access_resource(int id) {
    sem.acquire();  // 获取信号量（计数器-1），若满则等待
    
    // 模拟资源访问
    std::cout << "线程 " << id << " 访问资源" << "\n";
    std::this_thread::sleep_for(std::chrono::seconds(1));  // 模拟耗时操作
    
    sem.release();  // 释放信号量（计数器+1）
    std::cout << "线程 " << id << " 释放资源\n";
}

int main()
{
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i) {  // 启动5个线程
        threads.emplace_back(access_resource, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
