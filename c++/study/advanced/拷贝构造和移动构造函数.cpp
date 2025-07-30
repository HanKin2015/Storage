/*******************************************************************************
* 文 件 名: 拷贝构造和移动构造函数.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.14
* 修改日期：2025.07.14
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <vector>

class NonCopyable
{
public:
    NonCopyable(int value) : data(value) {}
    
    // 添加移动构造函数
    NonCopyable(NonCopyable&& other) noexcept : data(other.data) {}
    
    NonCopyable(const NonCopyable&) = delete;  // 禁用拷贝构造

private:
    int data;
};

int main()
{
    std::vector<NonCopyable> vec;
    vec.emplace_back(42);  // 直接构造
    vec.push_back(42);  // 非法，无法拷贝
    return 0;
}