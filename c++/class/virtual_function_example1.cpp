/*******************************************************************************
* 文 件 名: virtual_function_example1.cpp
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

class Base
{
public:
    virtual void func() const
    {
        cout << "Base!" << endl;
    }
};
class Derived :public Base
{
public:
    virtual void func()
    {
        cout << "Derived!" << endl;
    }
};

void show(Base& b)
{
    b.func();
}
Base base;
Derived derived;

int main()
{
    show(base);     // Base
    show(derived);  // Derived
    base.func();    // Base
    derived.func(); // Derived
    
    Base tmp = Derived();
    tmp.func();     // Base
    
    Base temp = derived;
    temp.func();    // Base
    
    // 定义为虚函数是为了允许用基类的指针来调用子类的这个函数
    // 因此一定需要指针或者引用才能调用子类
    Base *tp = &derived;
    tp->func();     // Derived
    
    Base *tep = new Derived();
    tep->func();    // Derived
    delete tep;
    tep = NULL;
    return 0;
}
