/*******************************************************************************
* 文 件 名: friend_function_example2.cpp
* 文件描述: 友元函数是其他类的成员函数
* 备    注: 友元函数/友元类的声明位置没有要求，可以在private、protected、public权限区，效果都是一样的
* 作    者: HanKin
* 创建日期: 2024.03.01
* 修改日期：2024.03.01
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

using namespace std;

class Person;

class Man
{
public:
    void print(Person &pn);
};

class Person
{
private:
    int age;

public:
    Person(){};
    Person(int x);

    //声明print是友元函数
    friend void Man::print(Person &pn);
};

Person::Person(int x)
{
    this->age = x;
}

void Man::print(Person &pn)
{
    //因为print是Person类的友元函数，所以在内部可以访问Person类的私有成员age
    cout << "Man::print" << endl;
    cout << "age=" << pn.age << endl;
}

int main(void)
{
    Person p(22);
    Man M;

    M.print(p);
    return 0;
}
