/*******************************************************************************
* 文 件 名: packaged_task_example.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.13
* 修改日期：2025.07.13
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <future>
#include <thread>

int add(int a, int b)
{
    return a + b;
}

void use_lambda()
{
	std::packaged_task<double(double, double)> task([](double a, double b) {
		return a * b;
	});

	std::future<double> future = task.get_future();

	// 立即执行任务
	task(2.5, 3.0);

	// 获取结果（此时任务已完成，不会阻塞）
	std::cout << "Result: " << future.get() << std::endl;  // 输出: 7.5
}

int main()
{
    // 创建packaged_task，包装add函数
    std::packaged_task<int(int, int)> task(add);
    
    // 获取与任务关联的future
    std::future<int> future = task.get_future();
    
    // 在新线程中执行任务
    std::thread([&task]() {
        task(3, 4);  // 执行任务，传递参数
    }).detach();
    
    // 获取任务结果（阻塞直到任务完成）
    std::cout << "Result: " << future.get() << std::endl;  // 输出: 7
    return 0;
}