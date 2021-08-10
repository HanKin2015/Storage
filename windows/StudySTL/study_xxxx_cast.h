#pragma once

#include "common.h"

/*
* 1、static_cast关键字
*/
class Complex {
public:
    Complex(double real = 0.0, double imag = 0.0) : m_real(real), m_imag(imag) { }
public:
    operator double() const { return m_real; }  //类型转换函数
private:
    double m_real;
    double m_imag;
};
void sdudy_static_cast()
{
    //下面是正确的用法
    int m = 100;
    Complex c(12.5, 23.8);
    long n = static_cast<long>(m);          //宽转换，没有信息丢失
    char ch = static_cast<char>(m);         //窄转换，可能会丢失信息
    int* p1 = static_cast<int*>(malloc(10 * sizeof(int)));  //将void指针转换为具体类型指针
    void* p2 = static_cast<void*>(p1);      //将具体类型指针，转换为void指针
    double real = static_cast<double>(c);   //调用类型转换函数

    //下面的用法是错误的
    //与指向的类型无关；强制转换要求 reinterpret_cast、C 样式强制转换或函数样式强制转换
    //float* p3 = static_cast<float*>(p1);    //不能在两个具体类型的指针之间进行转换
    //从整型强制转换为指针类型要求 reinterpret_cast、C 样式强制转换或函数样式强制转换
    //p3 = static_cast<float*>(0X2DF9);       //不能将整数转换为指针类型
	return;
}

/*
* 2、const_cast关键字
*/
void study_const_cast()
{
    const int n = 100;
    int* p = const_cast<int*>(&n);
    *p = 234;
    cout << "n = " << n << endl;
    cout << "*p = " << *p << endl;
    return;
}

/*
* 3.reinterpret_cast关键字
*/
class A {
public:
    A(int a = 0, int b = 0) : m_a(a), m_b(b) {}
private:
    int m_a;
    int m_b;
};
void study_reinterpret_cast()
{
    //将 char* 转换为 float*
    char str[] = "http://c.biancheng.net";
    float* p1 = reinterpret_cast<float*>(str);
    cout << *p1 << endl;
    //将 int 转换为 int*
    int* p = reinterpret_cast<int*>(100);
    //将 A* 转换为 int*
    p = reinterpret_cast<int*>(new A(25, 96));
    cout << *p << endl;

    return 0;
}

int test_study_xxxx_cast()
{
    sdudy_static_cast();
    study_const_cast();
	return 0;
}