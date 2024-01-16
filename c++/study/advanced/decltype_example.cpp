/*******************************************************************************
* 文 件 名: decltype_example.cpp
* 文件描述: auto关键字是在编译时通过已经初始化的变量来确定auto所代表的类型。auto修饰的表达式必须是已经初始化的变量
* 备    注: decltype关键字也是用来在编译时推导出一个表达式的类型，但此表达式初始化与否，在编译器都没有多大的影响
* 作    者: HanKin
* 创建日期: 2024.01.12
* 修改日期：2024.01.12
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
using namespace std;

int main()
{
    int x = 0;
    decltype(x) y = 1;  //y -> int
    cout << y << endl;
    decltype(x + y) z = 2; //z -> int
    cout << z << endl;

    const int& i = x;
    decltype(i) j = y;  //j -> const int &

    cout << j << endl;

    const decltype(z) *p = &z;  //*p -> const int
    decltype(z) *pi = &z;       //*pi -> int, pi->int*
    decltype(pi) *pp = &pi;     //*pp -> int*, pp->int**

    cout << pp << endl;         //打印结果：0x61fe80
    cout << *pp << endl;        //打印结果：0x61fe84
    cout << **pp << endl;       //打印结果：2

    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
1
2
1
0x7ffe0d67cf70
0x7ffe0d67cf6c
2
*/