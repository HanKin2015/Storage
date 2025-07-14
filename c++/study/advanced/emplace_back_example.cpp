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

public:
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

	// 注意emplace函数并不是表示在头部插入
	people.emplace_back("hj", 31);
	
	for (const auto& elem : people) {
		std::cout << elem.age << std::endl;
	}
	return 0;
}
/*
场景						推荐方法					原因
向 vector 尾部添加元素	emplace_back			避免临时对象，直接构造。
向 map 插入键值对		emplace					直接构造键值对，无需创建 std::pair。
插入不可拷贝 / 移动的对象	emplace/emplace_back	只能通过直接构造插入。
需要检查插入是否成功		emplace					返回包含成功标志的 std::pair。
*/