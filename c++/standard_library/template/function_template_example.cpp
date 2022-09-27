/**
* 文 件 名: function_template_example.cpp
* 文件描述: 针对不同的数据类型 比较两个数据的大小
* 作    者: HanKin
* 创建日期: 2022.09.26
* 修改日期：2022.09.26
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <iostream>

template <typename T> //模板参数由关键字typename（也可以使用class定义）定义一个函数模板 返回两个数中数值大的那一个 
inline T max(const T &a, const T &b)//函数有两个参数 ，类型为定义 
{
    std::cout << "********* " << __FUNCTION__ << '[' << __LINE__ << "] *********" << std::endl;
    return a > b ? a : b;
}

static void test1()
{
    int a = 1;
    int b = 2;
    auto ret1 = max<int>(a, b);
    std::cout << "int ret1 = " << ret1 << std::endl;
    double da = 1;
    double db = 2;
    auto ret2 = max(da, db);
    std::cout << "double ret2 = " << ret2 << std::endl;
    return;
}

// 参数推导
static void test2()
{
    int a = 1;
    double b = 2.0;
    //auto ret = max(a,b); // error 模板只有一种参数 但是这里传入了两种类型的参数
    // 解决办法
    // 用static_cast 强制转换参数类型使得 参数匹配
    auto ret1 = max(static_cast<double>(a),b);
    std::cout << "ret1 = " << ret1 << std::endl;
    
    // 显示指定T的类型
    auto ret2 = max<double>(a,b);
    std::cout << "ret2 = " << ret2 << std::endl;
    return;
}

// 函数模板重载
template <typename T> 
inline T max(const T &a, const T &b, const T &c)
{
    T temp;
    if (a < b) {
        temp = b;
    } else {
        temp = a;
    }
    std::cout << "********* " << __FUNCTION__ << '[' << __LINE__ << "] *********" << std::endl;
    return temp > c ? temp : c;
}
 
inline int max(const int &a, const int &b)
{
    std::cout << "********* " << __FUNCTION__ << '[' << __LINE__ << "] *********" << std::endl;
    return a > b ? a : b;
}
 
template <typename T, typename T1=double>
inline T max(const T &a, const T1 &b)
{
    std::cout << "template <typename T, typename T1=double> " << std::endl;
    return a >b ? a : b;
}

static void test3()
{
    max(1, 2, 3);   // max(const T &a, const T &b,const T &c) max<int>
    max(1.0, 2.3);  // max(const T &a, const T &b) max<double>
    max('a', 'b');  // max(const T &a, const T &b) max<char>
    max(1, 2);      // inline int max(const int &a, const int &b)
    max<>(1, 2);    // max(const T &a, const T &b) max<int>
    max<int>(1, 2); // max(const T &a, const T &b) max<int>
    max('a', 2);    // inline int max(const int &a, const int &b)
    return;
}

int main()
{
    test1();
    test2();
    test3();
    return 0;
}
















