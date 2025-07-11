/*******************************************************************************
* 文 件 名: 引用计数.cpp
* 文件描述: 引用计数（Reference Counting）是一种实现内存管理的技术，主要用于智能指针和共享资源的场景
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <memory>
#include <iostream>

int main()
{
    // 创建shared_ptr
    std::shared_ptr<int> ptr1 = std::make_shared<int>(42);
    std::cout << "引用计数: " << ptr1.use_count() << std::endl; // 输出: 1

    {
        std::shared_ptr<int> ptr2 = ptr1; // 引用计数+1
        std::cout << "引用计数: " << ptr1.use_count() << std::endl; // 输出: 2
    } // ptr2离开作用域，引用计数-1

    std::cout << "引用计数: " << ptr1.use_count() << std::endl; // 输出: 1
    // ptr1离开作用域，引用计数归零，对象被销毁

	// 特点：弱引用，不增加引用计数，用于解决shared_ptr的循环引用问题。
	// 使用场景：需要访问对象但不拥有所有权，或避免循环引用
	std::weak_ptr<int> ptr3 = ptr1;
	std::cout << "引用计数: " << ptr1.use_count() << std::endl; // 输出: 1
	
	ptr1 = ptr1;
	std::cout << "引用计数: " << ptr1.use_count() << std::endl; // 输出: 1
	return 0;
}
/*
引用计数: 1
引用计数: 2
引用计数: 1
引用计数: 1
引用计数: 1
*/