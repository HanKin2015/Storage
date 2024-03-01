/*******************************************************************************
* 文 件 名: virtual_inherit_example.cpp
* 文件描述: 虚继承
* 备    注: https://zhuanlan.zhihu.com/p/506896264
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

class A
{
public:
    int a;
};

class B : public A
{
public:
    int b;
};

class C : public A
{
public:
    int c;
};

class D : public B, public C
{
public:
    int d;
};

// 虚继承
class BB : virtual public A
{
public:
    int b;
};
class CC : virtual public A
{
public:
    int c;
};
class DD : public BB, public CC
{
public:
    int d;
};

int main()
{
    D d;
    
    // error: request for member ‘a’ is ambiguous
    // 事实上，在d中存在两份基类A的副本
    //d.a = 5;
    //cout << d.a << endl;
    
    cout << &d.B::a << endl; // 0x7ffefbb51390（该值随机）
    cout << &d.C::a << endl; // 0x7ffefbb51398（该值随机）
    
    d.B::a = 5;
    cout << d.B::a<< endl;   // 5
    
    
    // 在每个实例中只存在一个副本
    DD dd;
    cout << &dd.a << endl;      // 0x7ffc436af120（该值随机）
    cout << &dd.BB::a << endl;  // 0x7ffc436af120（该值随机）
    cout << &dd.CC::a << endl;  // 0x7ffc436af120（该值随机）
    return 0;
}
