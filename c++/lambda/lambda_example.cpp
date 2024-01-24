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