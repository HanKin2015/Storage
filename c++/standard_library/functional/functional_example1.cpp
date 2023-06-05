/**
* 文 件 名: functional_example1.cpp
* 文件描述: 学习functional库
* 备    注：g++ functional_example1.cpp -std=c++11
* 作    者: HanKin
* 创建日期: 2022.05.13
* 修改日期：2023.06.01
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <functional>
#include <iostream>

struct S {
    void operator ()()
    {
        std::cout << "S::()" << std::endl;
    }
};

void f()
{
    std::cout << "f()" << std::endl;
}

void ff()
{
    std::cout << "ff()" << std::endl;
}

int main(int argc, char *argv[])
{
    std::function<void()> f1(f);
    std::function<void()> f2(f1);
    f1(); // 输出f()
    f2(); // 输出f()
    f2 = ff;
    f2(); // 输出ff()
    f1.swap(f2);
    f1(); // 输出ff()
    f2(); // 输出f()
    std::cout << f1.target_type().name() << ", " << f2.target_type().name() << std::endl; // 可能输出PFvvE, PFvvE
    std::function<void()> f3 = S();
    f3(); // 输出S::()
    std::function<void()> f4;
    std::cout << (f4 ? "valid" : "invalid") << std::endl;  // 输出invalid
    try { f4(); } catch(std::bad_function_call e) { std::cout << e.what(); /*std::exceptionvalid*/ }
    f4 = f2;
    std::cout << (f4 ? "valid" : "invalid") << std::endl; // 输出valid
    auto f5 = [](){std::cout << "lambda" << std::endl;};
    auto f6 = [](int i){std::cout << "lambda with parameter " << i << std::endl;};
    f5(); // 输出lambda
    f6(100); // 输出lambda with parameter 100
    return 0;
}
/*
f()
f()
ff()
ff()
f()
PFvvE, PFvvE
S::()
invalid
bad_function_callvalid
lambda
lambda with parameter 100
*/