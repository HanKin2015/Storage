/*******************************************************************************
* 文 件 名: functional_example3.cpp
* 文件描述: std::function 其实就是一个可调用对象包装器（可以理解为auto接受）
* 备    注: 函数指针、仿函数、bind表达式、lambda表达式都是可调用对象，因此都可以使用std::function来接收
* 作    者: HanKin
* 创建日期: 2024.02.02
* 修改日期：2024.02.02
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <functional>

// 接收lambda表达式
std::function<void(int)> f1 = [](int val) { std::cout << val << std::endl; };

// 接收仿函数
class Functor
{
public:
    void operator() (int val)
    {
        std::cout << val << std::endl;
    }
};
Functor obj;
std::function<void(int)> f2 = obj;

// 接收正常函数
void Func1(int val)
{
    std::cout << val << std::endl;
}
std::function<void(int)> f3 = Func1;


// 接收std::bind绑定的函数
void Func2(int val1, int val2)
{
    std::cout << val1 << ' ' << val2 << std::endl;
}
std::function<void(int)> f4 = std::bind(Func2, std::placeholders::_1, 10);

// 接收std::bind绑定成员函数
class MyClass
{
public:
    void Func(int val)
    {
        std::cout << val << std::endl;
    }
};
MyClass myObj;
std::function<void(int)> f5 = std::bind(&MyClass::Func, &myObj, std::placeholders::_1);

int main()
{
    f1(1);  // 1
    f2(2);  // 2
    f3(3);  // 3
    f4(4);  // 4 10
    f5(5);  // 5
    return 0;
}