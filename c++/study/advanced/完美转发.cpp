/*******************************************************************************
* 文 件 名: 完美转发.cpp
* 文件描述: 完美转发（Perfect Forwarding）是 C++11 引入的一项重要特性，用于在函数模板中精确地将参数传递给其他函数，同时保留参数的原始值类别（左值或右值）和const属性。这在实现通用库（如容器、工厂函数、异步调用）时特别有用。
* 备    注: 当模板参数T通过&&推导时，T&&称为万能引用（又称转发引用）
* 作    者: HanKin
* 创建日期: 2025.07.09
* 修改日期：2025.07.09
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <utility>

// 目标函数（重载版本）
void target(int& x) {
    std::cout << "左值引用版本: " << x << std::endl;
}

void target(const int& x) {
    std::cout << "const 左值引用版本: " << x << std::endl;
}

void target(int&& x) {
    std::cout << "右值引用版本: " << x << std::endl;
}

// 完美转发包装器
template<typename T>
void wrapper(T&& arg) {
    target(std::forward<T>(arg));
}

int main() {
    int a = 42;
    const int b = 99;
    
    wrapper(a);        // 转发左值 -> 调用 target(int&)
    wrapper(b);        // 转发 const 左值 -> 调用 target(const int&)
    wrapper(123);      // 转发右值 -> 调用 target(int&&)
    wrapper(std::move(a));  // 强制转发为右值 -> 调用 target(int&&)
}