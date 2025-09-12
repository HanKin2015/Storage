/*******************************************************************************
* 文 件 名: 类的大小.cpp
* 文件描述: 遵循 “只计算实际存储的数据，忽略成员函数” 的基本原则
* 备    注: 内存对齐
* 作    者: HanKin
* 创建日期: 2025.09.12
* 修改日期：2025.09.12
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

// 静态成员变量不计算在内
// 内存对齐
// 虚函数表指针
class A
{
    //char c;        // 1字节
    int a;         // 4字节
    double b;      // 8字节
    char c;        // 1字节
    static int d;  // 静态成员，不计算在对象大小中

    virtual void f(); // 引入虚函数表指针
    virtual void ff();
};

// 派生类的大小 = 基类成员变量的大小 + 派生类新增成员变量的大小（同样受对齐和虚函数影响）
class Base { char a; virtual void f(); };          // 1字节
class Base2 { char aa; virtual void ff(); };
class Derived : public Base, public Base2 { int b; };  // 4（基类a） + 4 + 8（派生类b） = 16字节
/*
8字节变量
8字节虚函数表指针

8字节变量
8字节虚函数表指针


*/

int main()
{
    std::cout << sizeof(A) << std::endl;

    int *p = nullptr;
    std::cout << sizeof(p) << std::endl;

    std::cout << sizeof(Derived) << std::endl;  // 16
    return 0;
}