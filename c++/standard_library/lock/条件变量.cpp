/*******************************************************************************
* 文 件 名: 条件变量.cpp
* 文件描述: mutex、lock_guard、adopt_lock
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <condition_variable>
#include <deque>
#include <mutex>
#include <thread>
#include <iostream>

std::deque<int> queue;
std::mutex mtx;
std::condition_variable cv;
bool finished = false;

// 生产者线程
void producer() 
{
    for (int i = 0; i < 5; ++i) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        
        {
            std::lock_guard<std::mutex> lock(mtx);
            queue.push_back(i);
            std::cout << "Produced: " << i << std::endl;
        }
        
        cv.notify_one();  // 通知消费者
    }
    
    // 生产结束标志
    {
        std::lock_guard<std::mutex> lock(mtx);
        finished = true;
    }
    cv.notify_all();  // 通知所有消费者结束
}

// 消费者线程
void consumer()
{
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        
        // 等待数据或结束标志
        cv.wait(lock, []{ return !queue.empty() || finished; });
        
		// 超时等待
		std::cv_status status = cv.wait_for(lock, std::chrono::seconds(1));
		if (status == std::cv_status::timeout) {
			// 超时处理
		} else {
			// 条件满足
		}		

        if (finished && queue.empty()) {
            break;  // 任务全部处理完毕
        }
        
        int value = queue.front();
        queue.pop_front();
        std::cout << "Consumed: " << value << std::endl;
        
        // 锁在作用域结束时自动释放
    }
}

int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    
    t1.join();
    t2.join();
    
    return 0;
}