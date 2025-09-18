/*******************************************************************************
* 文 件 名: 指向类数据成员的指针.cpp
* 文件描述: 其语法标志为::*
* 备    注: 
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

class Person1 {
public:
    const std::string id; // const成员：身份证号不可修改
};

int main()
{
    // 1. 声明指向Person类中int成员的指针
    int Person::*p_int_member;

    // 2. 声明指向Person类中std::string成员的指针
    std::string Person::*p_str_member;

    // 3. 声明指向Person类中double成员的指针
    double Person::*p_double_member;
    
    // 初始化：指向Person::age
    p_int_member = &Person::age;

    // 初始化：指向Person::name
    p_str_member = &Person::name;

    // 初始化：指向Person::height
    p_double_member = &Person::height;
    
    // 创建具体对象
    Person p;
    Person* pp = &p;

    // 1. 通过对象和.*访问成员
    p.*p_int_member = 25;       // 等价于 p.age = 25
    p.*p_str_member = "Alice";  // 等价于 p.name = "Alice"
    p.*p_double_member = 1.65;  // 等价于 p.height = 1.65

    // 2. 通过对象指针和->*访问成员
    pp->*p_int_member = 26;     // 等价于 pp->age = 26
    pp->*p_str_member = "Bob";  // 等价于 pp->name = "Bob"
    pp->*p_double_member = 1.78;// 等价于 pp->height = 1.78

    // 输出结果
    std::cout << p.age << " " << p.name << " " << p.height << std::endl;
    // 输出：26 Bob 1.78

    // 声明指向const成员的指针
    const std::string Person1::*p_const_str_member = &Person1::id;

    Person1 p1{"123456"};
    // 正确：读取const成员
    std::cout << p1.*p_const_str_member << std::endl; // 输出123456
    // 错误：不能通过成员指针修改const成员
    // p1.*p_const_str_member = "654321"; // 编译报错：assignment of read-only member
    return 0;
}