/*******************************************************************************
* 文 件 名: friend_function_example.cpp
* 文件描述: 友元函数是普通全局函数
* 备    注: 友元函数/友元类的声明位置没有要求，可以在private、protected、public权限区，效果都是一样的
* 作    者: HanKin
* 创建日期: 2024.03.01
* 修改日期：2024.03.01
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

using namespace std;

class Person
{
private:
    int age;

protected:
    int sex;

public:
    int height;

public:
    Person(){};
    Person(int x, int y, int z);

    //声明print是友元函数
    friend void print(Person &pn);
    void test(Person &pn);
    void func(Person &pn);
};

Person::Person(int x, int y, int z)
{
    this->age = x;
    this->sex = y;
    this->height = z;
}

void print(Person &pn)
{
    //因为print是Person类的友元函数，所以在内部可以访问Person类的私有成员age
    cout << "age=" << pn.age << endl;
}

void test(Person &pn)
{
    //cout << pn.age << endl; // error: ‘int Person::age’ is private
    //cout << pn.sex << endl; // error: ‘int Person::sex’ is protected
    cout << pn.height << endl;
}

void Person::func(Person &pn)
{
    cout << "hello" << endl;
}

int main(void)
{
    Person p(22, 23, 24);
    print(p);   // age=22
    
    test(p);    // 24
    
    //func(p);    // error: ‘func’ was not declared in this scope
    p.func(p);  // hello
    return 0;
}
