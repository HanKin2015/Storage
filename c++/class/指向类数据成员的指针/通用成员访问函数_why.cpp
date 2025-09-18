/*******************************************************************************
* 文 件 名: 通用成员访问函数_why.cpp
* 文件描述: 如果需要为类的多个成员编写“读取/修改”函数，直接编码会出现大量重复代码。而用成员指针则可以实现一个“通用函数”，动态处理不同成员
* 备    注: 如果Person类后续新增成员（如weight），无需修改set_person_member和get_person_member，直接传入&Person::weight就能够使用，代码复用性较高
* 作    者: HanKin
* 创建日期: 2025.09.17
* 修改日期：2025.09.17
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <string>

class Person {
public:
    int age;
    std::string name;
    double height;
};

// 通用设置函数：动态设置Person的某个成员
template <typename T>
void set_person_member(Person& p, T Person::*member_ptr, const T& value) {
    p.*member_ptr = value; // 用成员指针动态访问成员
}

// 通用读取函数：动态读取Person的某个成员
template <typename T>
T get_person_member(const Person& p, T Person::*member_ptr) {
    return p.*member_ptr;
}

// 传统的写法就是在类中写多个get和set函数
int main()
{
    Person p;

    // 动态设置age
    set_person_member(p, &Person::age, 28);
    // 动态设置name
    set_person_member(p, &Person::name, "Charlie");
    // 动态设置height
    set_person_member(p, &Person::height, 1.82);

    // 动态读取成员
    std::cout << "Age: " << get_person_member(p, &Person::age) << std::endl;
    std::cout << "Name: " << get_person_member(p, &Person::name) << std::endl;
    std::cout << "Height: " << get_person_member(p, &Person::height) << std::endl;

    return 0;
}