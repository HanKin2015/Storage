/*******************************************************************************
* 文 件 名: template_example.cpp
* 文件描述: 函数参数可以隐式类型，但是返回值必须要显示，否则无法编译
* 备    注: g++ template_example.cpp -std=c++14
* 作    者: HanKin
* 创建日期: 2025.05.12
* 修改日期：2025.05.12
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <list>
#include <cstring>
#include <cstdio>
#include <memory>

template <typename T>
void template_function_argument(T x)
{
    std::cout << x << std::endl;
}

template <typename T>
T template_function_return_value()
{
    const char *ptr = "hejian";
    T x = T(ptr);
    return x;
}

int main()
{
    template_function_argument(1);
    template_function_argument<int>(11);
    template_function_argument(std::string("str"));
    template_function_argument("str");    // 传递字符串字面量 "s" 时，C++ 会将其视为 const char* 类型，而 template_function_argument 函数模板会接受任何类型的参数，因此这部分没有问题，但可能会导致不明确的类型推导

    // error: no matching function for call to ‘template_function_return_value()
    // 必现要指定返回值类型，否则编译报错
    std::string ret = template_function_return_value<std::string>();
    std::cout << ret << std::endl;
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #g++ template_example.cpp -std=c++14
[root@ubuntu0006:~/cmake] #./a.out
1
11
str
str
hejian
*/