/*******************************************************************************
* 文 件 名: friend_function_example3.cpp
* 文件描述: 友元类
* 备    注: 友元函数/友元类的声明位置没有要求，可以在private、protected、public权限区，效果都是一样的
* 作    者: HanKin
* 创建日期: 2024.03.01
* 修改日期：2024.03.01
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <string>

using namespace std;

class Person;

class Man
{
private:
	string name;

public:
	Man(){};
	Man(string myname)
	{
		this->name = myname;
	}
	
	void print_Man(Person &pn);

	//声明Person类是友元类
	friend class Person;
};

class Person
{
private:
	int age;

public:
	Person(){};
	Person(int x)
	{
		this->age = x;
	}
	
	void print_Person(Man &pn);

	//声明Man类是友元类
	friend class Man;
};

void Man::print_Man(Person &pn)
{
	//因为Man类是Person类的友元函数，Man的成员函数也可以访问Person类的私有成员
	cout << "Man::print" << endl;
	cout << "age=" << pn.age << endl;
}

void Person::print_Person(Man &pn)
{
	//因为Person类是Man类的友元函数，Person的成员函数也可以访问Man类的私有成员
	cout << "Person::print" << endl;
	cout << "name=" << pn.name << endl;
}

int main(void)
{
	Person p(22);
	Man M("linux");

	//Person和Man互为友元类
	p.print_Person(M);
	M.print_Man(p);
	return 0;
}
