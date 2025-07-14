/*******************************************************************************
* 文 件 名: thread_pool.cpp
* 文件描述: 线程池
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.12
* 修改日期：2025.07.12
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>
#include <atomic>

class ThreadPool
{
public:
    // 构造函数：初始化线程池
    explicit ThreadPool(size_t threadCount) : stop(false)
	{
        for (size_t i = 0; i < threadCount; ++i) {
            workers.emplace_back([this] {
                while (true) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(this->queueMutex);
                        // 等待任务或停止信号
                        this->condition.wait(lock, [this] {
                            return this->stop || !this->tasks.empty();
                        });
                        
                        // 如果线程池停止且没有任务，退出
                        if (this->stop && this->tasks.empty())
                            return;
                        
                        // 从队列中取出任务
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }
                    
                    // 执行任务
                    task();
                }
            });
        }
    }
    
    // 析构函数：停止并等待所有线程完成
    ~ThreadPool()
	{
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            stop = true;
        }
        condition.notify_all();  // 唤醒所有线程
        
        // 等待所有线程完成
        for (std::thread& worker : workers) {
            worker.join();
        }
    }
    
    // 添加任务到线程池
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) 
        -> std::future<typename std::result_of<F(Args...)>::type> {
        using return_type = typename std::result_of<F(Args...)>::type;
        
        // 包装任务为可调用对象
        auto task = std::make_shared<std::packaged_task<return_type()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...)
        );
        
        // 获取任务的future
        std::future<return_type> res = task->get_future();
        
        {
            std::unique_lock<std::mutex> lock(queueMutex);
            // 禁止在线程池停止后添加新任务
            if (stop) {
                throw std::runtime_error("enqueue on stopped ThreadPool");
            }
            // 将任务添加到队列
            tasks.emplace([task]() { (*task)(); });
        }
        
        // 通知一个等待的线程有新任务
        condition.notify_one();
        return res;
    }
    
private:
    std::vector<std::thread> workers;        // 工作线程集合
    std::queue<std::function<void()>> tasks; // 任务队列
    
    // 同步原语
    std::mutex queueMutex;                   // 保护任务队列的互斥锁
    std::condition_variable condition;       // 条件变量用于线程通信
    std::atomic<bool> stop;                  // 线程池停止标志
};

int main()
{
    // 创建包含4个线程的线程池
    ThreadPool pool(4);
    
    // 存储任务结果的future集合
    std::vector<std::future<int>> results;
    
    // 添加10个任务到线程池
    for (int i = 0; i < 10; ++i) {
        results.emplace_back(
            pool.enqueue([i] {
                std::cout << "Task " << i << " executed by thread " 
                          << std::this_thread::get_id() << std::endl;
                return i * i;
            })
        );
    }
    
    // 获取并打印任务结果
    for (auto&& result : results) {
        std::cout << "Result: " << result.get() << std::endl;
    }
    return 0;
}