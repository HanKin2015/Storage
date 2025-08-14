/*******************************************************************************
* 文 件 名: friend_class_example.cpp
* 文件描述: 友元类
* 备    注: 友元函数/友元类的声明位置没有要求，可以在private、protected、public权限区，效果都是一样的
* 作    者: HanKin
* 创建日期: 2025.08.13
* 修改日期：2025.08.13
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

/*******************************************************************************
* 文 件 名: 运算符重载_友元函数_by_myself.cpp
* 文件描述: 运算符重载
* 备    注: 当需要重载的运算符不满足作为成员函数的条件（如没有左侧操作数或需要访问类的私有或保护成员但又不希望将其设为公开）时，可以使用友元函数来实现
* 作    者: HanKin
* 创建日期: 2025.08.13
* 修改日期：2025.08.13
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

class A;
class B
{
public:
    B(int x): m_x(x) {};
    ~B() = default;

private:
    friend class A;
    int m_x;
};

class A
{
public:
    A() = default;
    ~A() = default;

    // 友元类的好处是可以直接访问B中的私有成员
    void print_member()
    {
        std::cout << m_b->m_x << std::endl;
    }
    
    void set_b(B& b)
    {
        m_b = &b;
    }

private:
    B *m_b;
};

int main()
{
    B b{100};
    A a;
    a.set_b(b);
    a.print_member();
    return 0;
}