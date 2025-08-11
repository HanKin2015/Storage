/*******************************************************************************
* 文 件 名: struct_default_value.cpp
* 文件描述: 添加编译选项 -Werror=uninitialized ，对于未初始化的结构体成员变量进行报错
* 备    注: 可以使用valgrind的memcheck工具或者asan，在运行时对内存进行检查
* 作    者: HanKin
* 创建日期: 2025.08.11
* 修改日期：2025.08.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <string>

// 定义一个用户信息结构体
struct User {
    int age;         // 年龄，未初始化
    std::string name;// 姓名，默认调用string的构造函数进行初始化
    bool is_active;  // 是否活跃，未初始化
};

// 打印用户信息的函数
void printUser(User u) {
    std::cout << "姓名：" << u.name 
              << "，年龄：" << u.age 
              << "，状态：" << (u.is_active ? "活跃" : "禁用") << std::endl;
}

int main()
{
    User user1;  // 未初始化的结构体
    printUser(user1);
    User* v = new User;     // 不带括号可能不初始化（视编译器而定，亲测初始化了）
    printUser(*v);

    User user2{}; // 初始化的结构体
    printUser(user2);

    User* u = new User();   // 带括号会触发零初始化
    printUser(*u);
    return 0;
}