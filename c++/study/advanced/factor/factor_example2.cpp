/*******************************************************************************
* 文 件 名: factor_example2.cpp
* 文件描述: 仿函数
* 备    注: https://baike.baidu.com/item/%E4%BB%BF%E5%87%BD%E6%95%B0?fromModule=lemma_search-box
* 作    者: HanKin
* 创建日期: 2024.01.31
* 修改日期：2024.01.31
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <ctime>
#include <cstring>
#include <string>
#include <set>

typedef long long LL;

// 打印不同类型的变量
class Prt
{
    char c[53];
    int top;
public:
    template <class T>
    Prt &operator()(T x);
    Prt &operator()(LL x);
    Prt &operator()(int x);
    Prt &operator()(char x);
    Prt &operator()(const char *x);
    Prt &operator()(double x);
    Prt &operator()(const std::string x);
    Prt &operator()(double x, int k)
    {
        sprintf(c, "%%.%dlf", k);
        printf(c, x);
        return *this;
    }
};

template <typename T>
Prt &Prt::operator()(T x)
{
    std::cout << x;
    return *this;
}
Prt &Prt::operator()(LL x)
{
    if(x == 0) {
        putchar('0');
        return *this;
    }
    if(x < 0) {
        putchar('-');
        x = -x;
    }
    top = 0;
    while(x > 0) {
        c[top++] = '0' + x % 10;
        x /= 10;
    }
    while(top--) {
        putchar(c[top]);
    }
    return *this;
}
Prt &Prt::operator()(int x)
{
    return operator()((LL)(x));
}
Prt &Prt::operator()(char x)
{
    putchar(x);
    return *this;
}
Prt &Prt::operator()(const char *x)
{
    printf("%s", x);
    return *this;
}
Prt &Prt::operator()(double x)
{
    printf("%lf", x);
    return *this;
}
Prt &Prt::operator()(const std::string x)
{
    return operator()(x.data());
}

Prt prt;

struct st {
    int x, y;
    st()
    {
        x = y = 0;
    } st(int a, int b)
    {
        x = a;
        y = b;
    }
};

std::ostream &operator<<(std::ostream &fout, const st &x)
{
    fout << "[" << x.x << "," << x.y << "]";
    return fout;
}

int main()
{
    prt(">>> prt(\"LL:\")(12341231234123ll)(\' \')(\"int:\")(15)(\'\\n\');\n");
    prt("LL:")(12341231234123ll)(' ')("int:")(15)('\n');
    prt('\n');
    prt(">>> prt(\"char:\")(\'a\')(\" char*(/string):\")(std::string(\"abc\"))(\" d \")\
((std::string(\"abc\")).data())(\'\\n\');\n");
    prt("char:")('a')(" char*(/string):")(std::string("abc"))(" d ")
    ((std::string("abc")).data())('\n');
    prt('\n');
    prt(">>> prt(\"double:\")(1.5)(\"  double[int]:\")(10.12349746192736,4)(\'\\n\');\n");
    prt("double:")(1.5)("  double[int]:")(10.12349746192736, 4)('\n');
    prt("\n>>> prt(st(12,31));\n");
    prt(st(12, 31));
    prt('\n');
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
>>> prt("LL:")(12341231234123ll)(' ')("int:")(15)('\n');
LL:12341231234123 int:15

>>> prt("char:")('a')(" char*(/string):")(std::string("abc"))(" d ")((std::string("abc")).data())('\n');
char:a char*(/string):abc d abc

>>> prt("double:")(1.5)("  double[int]:")(10.12349746192736,4)('\n');
double:1.500000  double[int]:10.1235

>>> prt(st(12,31));
[12,31]
*/