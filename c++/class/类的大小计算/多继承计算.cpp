/*******************************************************************************
* 文 件 名: 多继承计算.cpp
* 文件描述: 遵循 “只计算实际存储的数据，忽略成员函数” 的基本原则
* 备    注: 内存对齐
* 作    者: HanKin
* 创建日期: 2025.09.15
* 修改日期：2025.09.15
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

class Base1 { char a; virtual void f(); };          // 8+8
class Base2 { char aa, bb; virtual void ff(); };    // 8+8
class Derived1 : public Base1, public Base2 { };    // 16+16
class Derived2 : public Base1, public Base2 { char l, m, n; int b; };   // 16+9字节变量+7补充+8字节虚表指针
class Derived3 : public Base2, public Base1 { char l, m, n; int b; };   // 16+8字节变量+8字节虚表指针
class Derived4 : public Base1 { };          // 16
class Derived5 : public Base1 { int b; };   // 5字节变量+3字节补充+8字节虚表指针
class Derived6 : public Base1 { int b; char l, m, n; };   // 1字节变量+3字节补充+4字节变量+3字节变量+5字节补充+8字节虚表指针
class Derived7 : public Base1 { char l, m, n; int b; };   // 8字节变量+8字节虚表指针
class Derived8 : public Base1 { char l, m, n, o; int b; };// 5字节变量+3字节补充+4字节变量+4字节补充+8字节虚表指针

int main()
{
    std::cout << sizeof(Base1) << std::endl;
    std::cout << sizeof(Base2) << std::endl;
    std::cout << sizeof(Derived1) << std::endl;
    std::cout << sizeof(Derived2) << std::endl;
    std::cout << sizeof(Derived3) << std::endl;
    std::cout << sizeof(Derived4) << std::endl;
    std::cout << sizeof(Derived5) << std::endl;
    std::cout << sizeof(Derived6) << std::endl; // 这个是最好说明的派生类和父类会把变量放在一起，然后变量顺序不变
    std::cout << sizeof(Derived7) << std::endl;
    std::cout << sizeof(Derived8) << std::endl;
    return 0;
}
/*
root@hankin:~/opencv# ./a.out 
16
16
32
40
32
16
16
24
16
24
*/