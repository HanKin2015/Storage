/*******************************************************************************
* 文 件 名: vector_empty.cpp
* 文件描述: 空的vector返回
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.05.20
* 修改日期：2025.05.20
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <vector>

template <typename T>
std::vector<T> get_bind_info(T value)
{
    if (value == 1) return std::vector<T>();
    else if (value == 2) return std::vector<T>{};
    return {};
}

int main()
{
    std::vector<int> vec = get_bind_info(1);
    vec = get_bind_info(2);
    vec = get_bind_info(3);
    return 0;
}