/*******************************************************************************
* 文 件 名: forward_example.cpp
* 文件描述: std::forward 是一个用于实现完美转发的关键工具，通常与可变参数模板结合使用
* 备    注: 它能够保持参数的左值 / 右值属性，避免不必要的拷贝或移动操作
* 作    者: HanKin
* 创建日期: 2025.07.10
* 修改日期：2025.07.10
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <utility>
#include <iostream>

// 完美转发函数包装器
template<typename F, typename... Args>
decltype(auto) forward_wrapper(F&& f, Args&&... args) {
    return std::forward<F>(f)(std::forward<Args>(args)...);
}

// 使用示例
void print(int& x) { std::cout << "lvalue: " << x << '\n'; }
void print(int&& x) { std::cout << "rvalue: " << x << '\n'; }

int main()
{
    int a = 42;
    // 使用函数指针明确指定要使用的重载版本
    void (*print_lvalue)(int&) = print;
    void (*print_rvalue)(int&&) = print;
    
    forward_wrapper(print_lvalue, a);      // 转发左值
    forward_wrapper(print_rvalue, 123);    // 转发右值
	return 0;
}