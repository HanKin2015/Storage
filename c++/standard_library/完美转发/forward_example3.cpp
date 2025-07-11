/*******************************************************************************
* 文 件 名: forward_example3.cpp
* 文件描述: 实现通用包装器
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <utility>
#include <iostream>

// 通用包装器：将参数转发给目标函数
template<typename Func, typename... Args>
decltype(auto) wrapper(Func&& func, Args&&... args) {
    return std::forward<Func>(func)(std::forward<Args>(args)...);
}

// 测试函数
void print(int& x) { std::cout << "lvalue: " << x << std::endl; }
void print(int&& x) { std::cout << "rvalue: " << x << std::endl; }

int main() {
    int a = 42;
    
    // 方法1：使用函数指针显式指定重载版本
    using PrintLV = void(*)(int&);
    using PrintRV = void(*)(int&&);
    
    wrapper(static_cast<PrintLV>(print), a);      // 转发左值
    wrapper(static_cast<PrintRV>(print), 123);    // 转发右值
    
    // 方法2：使用lambda表达式（更简洁）
    wrapper([](auto&& arg) { print(std::forward<decltype(arg)>(arg)); }, a);
    wrapper([](auto&& arg) { print(std::forward<decltype(arg)>(arg)); }, 123);
    
    return 0;
}