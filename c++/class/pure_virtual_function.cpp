/*******************************************************************************
* 文 件 名: pure_virtual_function.cpp
* 文件描述: 纯虚函数，抽象类是指在一个类中包含纯虚函数，这样的类不能被直接实例化
* 备    注: 定义纯虚函数是为了实现一个接口，起到一个规范的作用，规范继承这个类的程序员必须实现这个函数
* 作    者: HanKin
* 创建日期: 2024.03.01
* 修改日期：2024.03.01
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
    // 纯虚方法一般只有一个声明而没有定义（实现）
    virtual void func() = 0;
};
class Derived :public Base
{
public:
    virtual void func()
    {
        cout << "Derived" << endl;
    }
};

void show(Base& b)
{
    b.func();
}

int main()
{
    // error: cannot declare variable ‘base’ to be of abstract type ‘Base’
    // note:   because the following virtual functions are pure within ‘Base’:
    //Base base;
    //show(base);
    
    Derived derived;
    show(derived);
    return 0;
}
