/*******************************************************************************
* 文 件 名: thread_pool_by_myself.cpp
* 文件描述: 手写线程池
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.13
* 修改日期：2025.07.13
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <thread>
#include <functional>
#include <queue>
#include <atomic>
#include <condition_variable>
#include <future>

class ThreadPool
{
public:
	explicit ThreadPool(int thread_pool_size): m_stop(false)
	{
		for (int i = 0; i < thread_pool_size; ++i) {
			m_workers.emplace_back([this] {
				while (true) {
					std::function<void()> task;
					{
						std::unique_lock<std::mutex> lock(this->m_mutex);
						m_cv.wait(lock, [this] {	// 等待直到线程停止或者任务队列不为空
							return this->m_stop || !this->m_tasks.empty();
						});
						
						if (this->m_stop && this->m_tasks.empty()) {	// 线程停止并且完成所有任务
							std::cout << "end thread pool" << std::endl;
							return;
						}
						
						task = std::move(this->m_tasks.front());
						this->m_tasks.pop();
					}
				
					// 执行任务
					task();
				}
			});
		}
	}
	
	~ThreadPool()
	{
		{
			std::lock_guard<std::mutex> lock(m_mutex);
			m_stop = true;
		}
		m_cv.notify_all();
		
		for (auto& worker : m_workers) {
			worker.join();
		}
	}
	
	template<class F, class... Args>
	auto enqueue(F&& f, Args&&... args) ->std::future<typename std::result_of<F(Args...)>::type>
	{
		using return_type = typename std::result_of<F(Args...)>::type;
		
		// 包装任务可调用对象
		auto task = std::make_shared<std::packaged_task<return_type()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
		
		std::future<return_type> res = task->get_future();
		
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			if (m_stop) {
				throw std::runtime_error("thread cannot stop now");
			}
			
			m_tasks.emplace([task]() { (*task)(); });
		}
		
		// 通知新增一个任务
		m_cv.notify_one();
		return res;
	}
	
private:
	std::vector<std::thread> m_workers;		// 工作线程
	std::queue<std::function<void()>> m_tasks;// 任务队列
	
	std::mutex m_mutex;				// m_stop互斥
	std::condition_variable m_cv;	// 条件变量
	std::atomic<bool> m_stop;		// 线程是否停止
};

int main()
{
	ThreadPool pool(5);
	std::vector<std::future<int>> rets;
	
	for (int i = 0; i < 5; ++i) {
		rets.emplace_back(pool.enqueue([i]() {
			std::cout << "add task pid " << std::this_thread::get_id() << std::endl;
			return i*i;
		}));
	}
	
	for (auto& elem : rets) {
		std::cout << elem.get() << std::endl;
	}
	return 0;
}
/*
add task pid 140421644301888
add task pid 140421644301888
add task pid 140421644301888
add task pid 140421644301888
add task pid 140421644301888
0
1
4
9
16
end thread pool
end thread pool
end thread pool
end thread pool
end thread pool
*/