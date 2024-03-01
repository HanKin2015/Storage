/*******************************************************************************
* 文 件 名: virtual_function_example2.cpp
* 文件描述: 定义虚函数是为了允许用基类的指针来调用子类的这个函数
* 备    注: https://blog.csdn.net/weixin_43329614/article/details/89103574
* 作    者: HanKin
* 创建日期: 2024.02.29
* 修改日期：2024.02.29
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#include <cstdlib>
using namespace std;

class Base1
{
public:
    virtual void func() const
    {
        cout << "Base1!" << endl;
    }
};
class Base2
{
public:
    virtual void func()
    {
        cout << "Base2!" << endl;
    }
};
class Derived :public Base1, public Base2
{
public:
    virtual void func()
    {
        cout << "Derived!" << endl;
    }
};
class Pure1 :public Base2
{
public:
    virtual void func()
    {
        cout << "Pure1!" << endl;
    }
};

// 继承但不重写基类虚函数
class Pure2 :public Base2
{
public:
    virtual void func2()
    {
        cout << "Pure2!" << endl;
    }
};

// 继承但不重写基类虚函数
class Pure3 :public Base1, public Base2
{
public:
    virtual void func2()
    {
        cout << "Pure2!" << endl;
    }
};

/*
切片问题是指当通过基类的引用或指针来操作派生类对象时，如果派生类对象被切割成了基类对象，就会导致部分派生类特有的信息丢失。这种情况通常发生在使用复制构造函数、赋值操作符或者传递参数的过程中。为了避免切片问题，应该尽量使用指针或引用来操作派生类对象，而不是直接使用对象本身。
*/
void show(Base1& b)
{
    b.func();
}
Base1 base;
Derived derived;

int main()
{
    show(base);     // Base1
    show(derived);  // Base1
    base.func();    // Base1
    derived.func(); // Derived
    
    Base2 tmp = Derived();
    tmp.func();     // Base2
    
    // *** Error in `./a.out': free(): invalid pointer: 0x00000000016bc038 ***
    // 原因就是由于继承了两个基类，会被释放两次
    Base2 *t = new Derived();
    t->func();      // Derived
    //delete t;
    //t = NULL;
    
    Base2 *te = new Pure1();
    te->func();     // Pure1
    delete te;
    te = NULL;
    
    Base2 *tem = new Pure2();
    tem->func();    // Base2
    delete tem;
    tem = NULL;
    
    Base2 *temp = new Pure3();
    temp->func();   // Base2
    //delete temp;
    //temp = NULL;
    
    Base1 *tp = new Pure3();
    tp->func();     // Base1
    //delete tp;
    //tp = NULL;
    return 0;
}
