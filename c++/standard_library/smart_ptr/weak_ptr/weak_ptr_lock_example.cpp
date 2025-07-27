/*******************************************************************************
* 文 件 名: weak_ptr_lock_example.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.27
* 修改日期：2025.07.27
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <memory>

int main()
{
    auto parent = std::make_shared<int>();
    
    std::cout << parent.use_count() << std::endl;   // 1

    std::weak_ptr<int> child = parent;

    std::cout << parent.use_count() << std::endl;   // 1

    auto ptr1 = parent;
    std::cout << parent.use_count() << std::endl;   // 2

    auto ptr2 = child;
    std::cout << parent.use_count() << std::endl;   // 2
    
    auto ptr3 = child.lock();
    std::cout << parent.use_count() << std::endl;   // 3
    return 0;
}