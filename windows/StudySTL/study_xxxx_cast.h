#pragma once

#include "common.h"

/*
* 1��static_cast�ؼ���
*/
class Complex {
public:
    Complex(double real = 0.0, double imag = 0.0) : m_real(real), m_imag(imag) { }
public:
    operator double() const { return m_real; }  //����ת������
private:
    double m_real;
    double m_imag;
};
void sdudy_static_cast()
{
    //��������ȷ���÷�
    int m = 100;
    Complex c(12.5, 23.8);
    long n = static_cast<long>(m);          //��ת����û����Ϣ��ʧ
    char ch = static_cast<char>(m);         //խת�������ܻᶪʧ��Ϣ
    int* p1 = static_cast<int*>(malloc(10 * sizeof(int)));  //��voidָ��ת��Ϊ��������ָ��
    void* p2 = static_cast<void*>(p1);      //����������ָ�룬ת��Ϊvoidָ��
    double real = static_cast<double>(c);   //��������ת������

    //������÷��Ǵ����
    //��ָ��������޹أ�ǿ��ת��Ҫ�� reinterpret_cast��C ��ʽǿ��ת��������ʽǿ��ת��
    //float* p3 = static_cast<float*>(p1);    //�����������������͵�ָ��֮�����ת��
    //������ǿ��ת��Ϊָ������Ҫ�� reinterpret_cast��C ��ʽǿ��ת��������ʽǿ��ת��
    //p3 = static_cast<float*>(0X2DF9);       //���ܽ�����ת��Ϊָ������
	return;
}

/*
* 2��const_cast�ؼ���
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
* 3.reinterpret_cast�ؼ���
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
    //�� char* ת��Ϊ float*
    char str[] = "http://c.biancheng.net";
    float* p1 = reinterpret_cast<float*>(str);
    cout << *p1 << endl;
    //�� int ת��Ϊ int*
    int* p = reinterpret_cast<int*>(100);
    //�� A* ת��Ϊ int*
    p = reinterpret_cast<int*>(new A(25, 96));
    cout << *p << endl;
    return;
}

/*
* 4.dynamic_cast�ؼ���
*/
class Base {
public:
    Base(int a = 0) : m_a(a) { }
    int get_a() const { return m_a; }
    virtual void func() const { }
protected:
    int m_a;
};
class Derived : public Base {
public:
    Derived(int a = 0, int b = 0) : Base(a), m_b(b) { }
    int get_b() const { return m_b; }
private:
    int m_b;
};
void study_dynamic_cast()
{
    //�����
    Derived* pd1 = new Derived(35, 78);
    Base* pb1 = dynamic_cast<Derived*>(pd1);
    cout << "pd1 = " << pd1 << ", pb1 = " << pb1 << endl;
    cout << pb1->get_a() << endl;
    pb1->func();
    //�����
    int n = 100;
    Derived* pd2 = reinterpret_cast<Derived*>(&n);
    Base* pb2 = dynamic_cast<Base*>(pd2);
    cout << "pd2 = " << pd2 << ", pb2 = " << pb2 << endl;
    cout << pb2->get_a() << endl;   //���һ������ֵ
    //pb2->func();                    //�ڴ����
    return;
}
int test_study_xxxx_cast()
{
    sdudy_static_cast();
    study_const_cast();
    study_reinterpret_cast();
    study_dynamic_cast();
	return 0;
}