/*******************************************************************************
* 文 件 名: forward_example4.cpp
* 文件描述: 完美转发构造函数参数
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <utility>
#include <iostream>

// 目标类：接收任意参数的构造函数
class MyClass {
public:
    template<typename... Args>
    MyClass(Args&&... args) : data(std::forward<Args>(args)...) {}

    // 简化示例：存储一个 int
    int data;
};

// 工厂函数：完美转发参数创建对象
template<typename T, typename... Args>
T create(Args&&... args) {
    return T(std::forward<Args>(args)...);
}

int main()
{
    int x = 42;
    MyClass obj1(x);             // 左值参数
    MyClass obj2(create<int>(5)); // 右值参数

    std::cout << obj1.data << std::endl; // 输出: 42
    std::cout << obj2.data << std::endl; // 输出: 5
    return 0;
}