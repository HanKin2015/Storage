/*******************************************************************************
* 文 件 名: emplace_back_example.cpp
* 文件描述: 直接在容器的内存空间中构造对象，只需要一次构造，无需临时对象。
* 备    注: push_back先构造一个临时对象，再将其移动（或拷贝）到容器中。可能触发两次构造（临时对象 + 移动构造）。
* 作    者: HanKin
* 创建日期: 2025.07.09
* 修改日期：2025.07.09
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <vector>

class Person {
public:
    Person(const std::string& name, int age) : name(name), age(age) { std::cout << __func__ << std::endl; }
private:
    std::string name;
    int age;
};

int main()
{
	std::vector<Person> people;

	// push_back：必须先构造 Person 对象（去掉Person后会编译不过，但是std::string类型可以默认构造）
	people.push_back(Person("Alice", 20));  // 显式构造 + 移动

	// emplace_back：直接传递构造参数
	people.emplace_back("Bob", 25);  // 直接构造，无需显式创建 Person

	return 0;
}