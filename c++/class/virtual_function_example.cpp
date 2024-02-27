/*******************************************************************************
* 文 件 名: virtual_function_example.cpp
* 文件描述: this指针作用
* 备    注: https://blog.csdn.net/weixin_43329614/article/details/89103574
* 作    者: HanKin
* 创建日期: 2024.02.26
* 修改日期：2024.02.26
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

/*
虚函数的声明与定义要求非常严格，只有在子函数中的虚函数与父函数一模一样的时候（包括限定符）才会被认为是真正的虚函数，不然的话就只能是重载。这被称为虚函数定义的同名覆盖原则，意思是只有名称完全一样时才能完成虚函数的定义。

因此在上述的例子中，将Derived类型的子类传入show函数时，实际上类型转化为了Base，由于此时虚函数并未完成定义，Derived的func()此时仅仅是属于Derived自己的虚函数，所以在show中b并不能调用，而调用的是Base内的func。而当没有发生类型转换的时候，Base类型与Derived类型就会各自调用自己的func函数。
*/
int main()
{
    show(base);     // Base
    show(derived);  // Base
    base.func();    // Base
    derived.func(); // Derived
    return 0;
}
