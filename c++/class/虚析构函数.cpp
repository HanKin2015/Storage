/*******************************************************************************
* 文 件 名: 虚析构函数.cpp
* 文件描述: 当通过父类指针删除子类对象时，如果父类的析构函数不是虚函数，则只会调用父类的析构函数，而不会调用子类的析构函数。这会导致子类的资源（如动态分配的内存、文件句柄、网络连接等）无法被正确释放，造成内存泄漏
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

class Base {
public:
    virtual ~Base() { std::cout << "Base destructor" << std::endl; }
};

class Derived : public Base {
private:
    int* data;
public:
    Derived() { data = new int[100]; }
    ~Derived() {
        delete[] data;  // 这行代码不会被执行！
        std::cout << "Derived destructor" << std::endl;
    }
};

int main()
{
    Base* ptr = new Derived();  // 父类指针指向子类对象
    delete ptr;  // 只调用Base::~Base()，导致Derived::~Derived()未被调用
    return 0;
}

// 输出结果：
// Base destructor
// 内存泄漏：data数组未被释放！