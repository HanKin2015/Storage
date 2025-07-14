/*******************************************************************************
* 文 件 名: packaged_task_example2.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.14
* 修改日期：2025.07.14
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <functional>
#include <future>

template<class F, class... Args>
auto enqueue(F&& f, Args&&... args) 
	-> std::future<typename std::result_of<F(Args...)>::type> {
	using return_type = typename std::result_of<F(Args...)>::type;
	
	// 包装任务为可调用对象
	std::shared_ptr<std::packaged_task<return_type()>> task;
	task = std::make_shared<std::packaged_task<return_type()>>(
		std::bind(std::forward<F>(f), std::forward<Args>(args)...)
	);
	
	// 获取任务的future
	std::future<return_type> res = task->get_future();
	
	(*task)();
	
	return res;
}

int main()
{
	auto ret = enqueue([]() {
		std::cout << "task task task" << std::endl;
		return 12345;
	});
	std::cout << ret.get() << std::endl;
	return 0;
}