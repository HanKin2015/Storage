/*******************************************************************************
* 文 件 名: exception_bad_alloc.cpp
* 文件描述: std::bad_alloc: 表示内存分配失败
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.03.10
* 修改日期：2025.03.10
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <new> // 引入std::bad_alloc异常头文件

int main()
{
    try {
        // 尝试分配大量内存
        int* largeArray = new int[1000000000000]; // 模拟内存分配失败
    } catch (const std::bad_alloc& e) {
        // 捕获 std::bad_alloc 异常，输出错误信息
        std::cerr << "Memory allocation failed: " << e.what() << std::endl; // Memory allocation failed: std::bad_alloc
    }

    return 0;
}