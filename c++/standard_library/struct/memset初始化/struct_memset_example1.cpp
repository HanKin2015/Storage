/*******************************************************************************
* 文 件 名: struct_memset_example1.cpp
* 文件描述: 现代编译器（如 GCC、Clang）的std::string通常采用 SSO：当字符串长度较短时（如 "Alice"），数据直接存储在std::string对象内部的栈缓冲区中，不涉及堆内存
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.11
* 修改日期：2025.08.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <string>
#include <cstring>

struct Data {
    int id;
    double value;
    bool flag;
};

struct Student {
    int age;
    std::string name;   // 包含类类型成员
};

struct Base {
    virtual void print() {}  // 包含虚函数，存在vptr
    int data;
};

int main()
{
    Data d;
    memset(&d, 0, sizeof(Data));  // 使用memset初始化
    std::cout << "id: " << d.id 
              << ", value: " << d.value 
              << ", flag: " << std::boolalpha << d.flag << std::endl;
    
    Student s;
    memset(&s, 0, sizeof(Student)); // 同样使用memset
    s.name = "Alice";  // 运行时崩溃（姑且认为它是崩溃的，实际测试不会出现崩溃）
    std::cout << "name: " << s.name
              << ", age: " << s.age
              << std::endl;
    
    Base b;
    memset(&b, 0, sizeof(Base));  // 覆盖vptr
    b.print();  // 崩溃：无法找到虚函数表
    return 0;
}