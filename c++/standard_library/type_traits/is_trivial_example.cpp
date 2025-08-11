/*******************************************************************************
* 文 件 名: is_trivial_example.cpp
* 文件描述: 判断一个类型是否为平凡类型（Trivial Type），即类型的初始化、复制、移动和销毁可以通过简单的内存操作（如 memcpy）完成，无需特殊逻辑
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.11
* 修改日期：2025.08.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <type_traits>
#include <iostream>

// 平凡类型
struct A { int x; double y; };  // 编译器生成所有默认函数

// 非平凡类型
struct B { B() {} };  // 用户定义了构造函数，非平凡
struct C { ~C() {} };  // 用户定义了析构函数，非平凡
struct D { D(const D&) {} };  // 用户定义了复制构造函数，非平凡

int main() {
    std::cout << std::boolalpha;
    std::cout << "A is trivial: " << std::is_trivial<A>::value << "\n";  // true
    std::cout << "B is trivial: " << std::is_trivial<B>::value << "\n";  // false
    return 0;
}