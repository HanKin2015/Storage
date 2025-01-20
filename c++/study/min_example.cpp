/*******************************************************************************
* 文 件 名: min_example.cpp
* 文件描述: min函数使用
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.01.03
* 修改日期：2025.01.03
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <iostream>
#include <cstdint>
#include <algorithm> // 包含 std::min 的定义

int main()
{
    unsigned int x = 1;
    long unsigned int y = 2;
    int z = std::min(x, static_cast<unsigned int>(y)); // 显式转换
    auto z = std::min<unsigned long>(x, y); // 显式指定类型为 unsigned long
    //int z = std::min(x, y);   // deduced conflicting types for parameter ‘const _Tp’ (‘long unsigned int’ and ‘uint32_t {aka unsigned int}’)
    printf("z = %d\n", z);
    return 0;
}


