/*******************************************************************************
* 文 件 名: friend_function_example4.cpp
* 文件描述: "=, ->, [], ()"不能用友元函数重载的原因
* 备    注: https://blog.csdn.net/weixin_42031299/article/details/127699652
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

public:
	Person(){};
	Person(int a);

	friend Person operator=(int x);
};

Person::Person(int a)
{
	cout << "Person(int a)" << endl;
	this->age = a;
}

Person operator=(int x)
{
	cout << "operator=" << endl;
	this->age = x;
	return *this;
}

int main()
{
	Person p;
	p = 2;
	return 0;
}

