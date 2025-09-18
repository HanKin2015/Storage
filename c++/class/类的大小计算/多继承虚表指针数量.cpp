/*******************************************************************************
* 文 件 名: 多继承虚表指针数量.cpp
* 文件描述: 普通函数不占用内存，并且无虚函数则无虚指针
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.09.17
* 修改日期：2025.09.17
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

class Base1 { char a; void f(); };
class Base2 { char aa, bb; virtual void f(); virtual void ff(); };

class Derived1 { virtual void fff(); };
class Derived2 : public Base1 { virtual void fff(); };
// 这里如何理解？自身的虚函数表指针和后面一个继承类合并，如Base2
class Derived3 : public Base1, public Base2 { virtual void fff(); };
// 这里如何理解？自身的虚函数表指针和后面一个继承类合并，如Base1
class Derived4 : public Base2, public Base1 { virtual void fff(); };
// 这里可以看出，字节就是16，变量+虚函数表指针
class Derived5 : public Base2 { virtual void fff(); };

int main()
{
    std::cout << sizeof(Base1) << std::endl;    // 1
    std::cout << sizeof(Base2) << std::endl;    // 16
    std::cout << sizeof(Derived1) << std::endl; // 8
    std::cout << sizeof(Derived2) << std::endl; // 16
    std::cout << sizeof(Derived3) << std::endl; // 16
    std::cout << sizeof(Derived4) << std::endl; // 16
    std::cout << sizeof(Derived5) << std::endl; // 16
    return 0;
}