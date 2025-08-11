/*******************************************************************************
* 文 件 名: is_standard_layout_example.cpp
* 文件描述: 判断一个类型是否为标准布局类型（Standard Layout Type），即其内存布局符合特定规范，确保跨编译器 / 平台的内存布局一致性
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.11
* 修改日期：2025.08.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <type_traits>
#include <iostream>

// 标准布局类型
struct A { int x; private: int y; };  // 错误：成员访问控制不同
struct B { public: int x; public: int y; };  // 正确：全public
struct C : B { int z; };  // 正确：基类B无成员，派生类C有成员

// 非标准布局类型
struct D { virtual void f(); };  // 有虚函数
struct E : B, C {};  // 多继承且基类有成员
struct F { int& ref; };  // 包含引用

int main() {
    std::cout << std::boolalpha;
    std::cout << "B is standard layout: " << std::is_standard_layout<B>::value << "\n";  // true
    std::cout << "D is standard layout: " << std::is_standard_layout<D>::value << "\n";  // false
    return 0;
}