/**
* 文 件 名: lambda_example.cpp
* 文件描述: 学习lambda函数
* 作    者: HanKin
* 创建日期: 2024.01.22
* 修改日期：2024.01.22
*
* Copyright (c) 2024 HanKin. All rights reserved.
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#include <cstdlib>
using namespace std;

void func1()
{
    printf("func1\n");
    return;
}

void func2(int y)
{
    printf("func2 y = %d\n", y);
    return;
}

int main(int argc, char *argv[])
{
    int x = 43;
    // 使用 lambda 表达式打印变量 x 的值
    auto print_x = [x]() {
        std::cout << "x = " << x << std::endl;
    };
    print_x();  // 调用 lambda 函数
    
    auto print_hello = [] {
        std::cout << "hello world" << std::endl;
    };
    print_hello();
    
    auto print_world = []() {
        std::cout << "hello world" << std::endl;
    };
    print_world();
    
    auto print_func = []() {
        func1();
        func2(123);
    };
    print_func();
    
    int a = 3, b = 5;
    // 正确，不推荐
    auto func = [a, b]() {
        printf("a + b = %d\n", a + b);
        return a + b;
    };
    int ret = func();
    printf("ret = %d\n", ret);
    
    // 'a' and 'b' is not captured
    auto func1 = []() {
        printf("a + b = %d\n", a + b);
        return a + b;
    };
    ret = func1();
    printf("ret = %d\n", ret);
    
    auto func4 = [=]() {
        a = 1000;   // error: assignment of read-only variable ‘a’
        printf("a + b = %d\n", a + b);
        return a + b;
    };
    ret = func4();
    printf("ret = %d\n", ret);
    
    // 正确，推荐
    auto func2 = [&]() {
        printf("a + b = %d\n", a + b);
        a = 100;
        return a + b;
    };
    ret = func2();
    printf("a = %d ret = %d\n", a, ret);
    
    // error: assignment of read-only variable ‘a’
    auto func3 = [a, b]() {
        printf("a + b = %d\n", a + b);
        a = 100;
        return a + b;
    };
    ret = func3();
    printf("a = %d ret = %d\n", a, ret);
    
    // 增加函数入参
    auto func5 = [=](int x) {
        printf("x = %d\n", x);
        return a + b + x;
    };
    ret = func5(123);
    printf("a = %d ret = %d\n", a, ret);    // 228
    
    // 指定返回类型
    auto func6 = [=](int x) -> double {
        printf("x = %d\n", x);
        return a + b + x;
    };
    double ret2 = func6(123);
    printf("a = %d ret = %f\n", a, ret2);    // 228.000000
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #g++ a.cpp -std=c++11
[root@ubuntu0006:~/cmake] #./a.out
x = 43
hello world
hello world
func1
func2 y = 123
*/