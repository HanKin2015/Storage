/*******************************************************************************
* 文 件 名: operator_example.cpp
* 文件描述: operator重载运算符
* 备    注: https://blog.csdn.net/hp_cpp/article/details/108350361
* 作    者: HanKin
* 创建日期: 2024.01.03
* 修改日期：2024.01.03
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
using namespace std;

// 将操作符重载实现为类的成员函数
class person
{
private:
    int age;
public:
    person(int nAge) {
        this->age = nAge;
    }
 
    bool operator==(const person& ps) {
        if (this->age == ps.age) {
            return true;
        }
        return false;
    }
};

// 操作符重载实现为非类的成员函数（即全局函数）
class Person
{
public:
    int age;
};
 
// 左操作数的类型必须被显式指定
// 此处指定的类型为person类
// 写成这样也正确bool operator==(Person const& p1, Person const& p2)
bool operator == (Person const& p1, Person const& p2)
{
    if (p1.age == p2.age) {
        return true;
    } else {
        return false;
    }
}
 
int main()
{
    person p1(10);
    person p2(10);
    if (p1 == p2) {
        cout << "p1 is equal with p2." << endl;
 
    } else {
        cout << "p1 is not equal with p2." << endl;
    }
    
    Person p3, p4;
    p3.age = 18;
    p4.age = 18;
    if (p3 == p4) {
        cout << "p3 is equal with p4." << endl;
 
    } else {
        cout << "p3 is not equal with p4." << endl;
    }
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #g++ operator_example.cpp
[root@ubuntu0006:~/cmake] #./a.out
p1 is equal with p2.
p3 is equal with p4.
*/