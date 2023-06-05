/**
* 文 件 名: functional_example2.cpp
* 文件描述: 学习functional库
* 备    注：g++ functional_example2.cpp -std=c++11
* 作    者: HanKin
* 创建日期: 2022.06.01
* 修改日期：2023.06.01
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <iostream>
#include <functional>

using namespace std;

int add(int a, int b)
{
    return a + b;
}

int main()
{
    // 使用function封装函数指针
    function<int(int, int)> func1 = add;
    cout << func1(1, 2) << endl; // 输出3

    // 使用bind绑定函数和参数
    auto func2 = bind(add, 1, 2);
    cout << func2() << endl; // 输出3

    // 使用mem_fn封装成员函数
    class A {
    public:
        int add(int a, int b) {
            return a + b;
        }
    };
    A a;
    auto func3 = mem_fn(&A::add);
    cout << func3(&a, 1, 2) << endl; // 输出3

    // 使用plus函数对象实现加法
    plus<int> p;
    cout << p(1, 2) << endl; // 输出3

    // 使用greater函数对象实现比较
    greater<int> g;
    cout << g(1, 2) << endl; // 输出false

    return 0;
}
/*
3
3
3
3
0
*/