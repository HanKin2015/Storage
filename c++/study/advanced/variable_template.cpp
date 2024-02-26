/*******************************************************************************
* 文 件 名: variable_template.cpp
* 文件描述: 变量模板
* 备    注: https://blog.csdn.net/u010168781/article/details/103399188
* 作    者: HanKin
* 创建日期: 2024.01.31
* 修改日期：2024.01.31
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstdio>

template<class T>
constexpr T pi = T(3.1415926535897932385L); // variable template

struct Limits
{
    template<typename T>
    static const T min; // 声明静态成员模板
};
 
template<typename T>
const T Limits::min = { }; // 定义静态成员模板，全部使用默认值

// 下面三个是模板变量的特化
template<>
const float Limits::min<float> = 4.5;

template<>
const double Limits::min<double> = 5.5;

template<>
const std::string Limits::min<std::string> = "hello";

int main()
{
    std::cout << pi<double> << std::endl;   // 3.14159
    std::cout << pi<float> << std::endl;    // 3.14159
    std::cout << pi<int> << std::endl;      // 3
    
    std::cout << Limits::min<int> << std::endl;         // 0
    std::cout << Limits::min<float> << std::endl;       // 4.5
    std::cout << Limits::min<double> << std::endl;      // 5.5
    std::cout << Limits::min<std::string> << std::endl; // hello
    return 0;
}