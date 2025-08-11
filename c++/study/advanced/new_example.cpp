/*******************************************************************************
* 文 件 名: new_example.cpp
* 文件描述: new(this) D; 是 placement new 的用法，在已有内存地址上构造 D 对象。这种操作非常底层，绕过了 C++ 常规的对象生命周期管理，必须确保内存大小兼容且手动处理析构，否则极易引发未定义行为，实际开发中应谨慎使用
* 备    注: new(this) D; 是 C++ 中的 “placement new”（定位 new） 语法，用于在已分配的内存地址上构造对象，而不重新分配新内存
* 作    者: HanKin
* 创建日期: 2025.08.11
* 修改日期：2025.08.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstdio>
#include <new>  // 引入placement new所需的头文件

class B {
public:
    virtual void foo();
    virtual ~B() { puts("B::~B"); }
};

class D : public B {
public:
    void foo() override { puts("D::foo"); }
    ~D() { puts("D::~D"); }
};

// 在D定义后实现B::foo()，此时D已完整可见
void B::foo() { 
    puts("B::foo");
    this->~B();
    new(this) D;  // 现在可以正确识别placement new
}

int main() {
    B* b = new B();
    b->foo();   // B::foo B::~B
    b->foo();   // D::foo
    puts("\n");
    delete b;   // D::~D B::~B
    return 0;
}