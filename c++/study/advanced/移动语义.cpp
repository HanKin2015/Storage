/*******************************************************************************
* 文 件 名: 移动语义.cpp
* 文件描述: 用于高效地转移资源所有权（如内存、文件句柄等），避免不必要的深拷贝，从而提升性能。它主要通过 右值引用（Rvalue Reference） 和 移动构造函数 / 移动赋值运算符 实现。
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.29
* 修改日期：2025.07.29
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

class MyClass {
public:
    // 移动构造函数
    MyClass(MyClass&& other) noexcept {
        // 转移资源所有权，避免拷贝
        data = other.data;
        other.data = nullptr;  // 确保原对象不再拥有资源
    }

    // 移动赋值运算符
    MyClass& operator=(MyClass&& other) noexcept {
        if (this != &other) {
            delete data;       // 释放当前资源
            data = other.data; // 转移资源
            other.data = nullptr;
        }
        return *this;
    }

private:
    int* data;
};

int main()
{
    int x = 10;
    int& lref = x;       // 左值引用绑定到左值
    int&& rref = 20;     // 右值引用绑定到右值（临时对象）
    std::cout << x << ' ' << lref << ' ' << rref << std::endl;
    return 0;
}