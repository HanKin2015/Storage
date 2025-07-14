/*******************************************************************************
* 文 件 名: emplace_back_push_back_compare.cpp
* 文件描述: 对于没有拷贝或移动构造函数的对象，只能使用 emplace 系列方法插入
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.14
* 修改日期：2025.07.14
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <vector>
#include <string>
#include <iostream>

class Person
{
public:
    // 带参数的构造函数
    Person(std::string name, int age) 
        : name(std::move(name)), age(age) {
        std::cout << "Constructing Person: " << this->name << std::endl;
    }
    
    // 拷贝构造函数
    Person(const Person& other)
        : name(other.name), age(other.age) {
        std::cout << "Copy constructing Person: " << name << std::endl;
    }
    
    // 移动构造函数
    Person(Person&& other) noexcept
        : name(std::move(other.name)), age(other.age) {
        std::cout << "Moving Person: " << name << std::endl;
    }
    
private:
    std::string name;
    int age;
};

int main()
{
    std::vector<Person> people;
    
    std::cout << "\nUsing push_back with temporary object:\n";
    people.push_back(Person("Alice", 25));  // 必须显式构造对象
    
    std::cout << "\nUsing emplace_back with arguments:\n";
    people.emplace_back("Bob", 30);  // 直接传递构造参数
    
    std::cout << "\nUsing push_back with lvalue:\n";
    Person eve("Eve", 22);
    people.push_back(eve);  // 拷贝构造（左值）
    
    return 0;
}
/*
Using push_back with temporary object:
Constructing Person: Alice
Moving Person: Alice

Using emplace_back with arguments:
Constructing Person: Bob
Moving Person: Alice

Using push_back with lvalue:
Constructing Person: Eve
Copy constructing Person: Eve
Moving Person: Alice
Moving Person: Bob
*/