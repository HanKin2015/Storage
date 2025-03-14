/*******************************************************************************
* 文 件 名: const_example.cpp
* 文件描述: const修饰符的作用
* 作    者: HanKin
* 创建日期: 2024.02.26
* 修改日期：2024.02.26
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstdio>

// 2、函数参数：const 可以用来声明函数参数为常量，防止函数修改参数的数值。
void printValue(const int value);

class MyClass {
public:
    // 3、成员函数：const 可以用来修饰成员函数，表示该函数不会修改对象的状态。
    void doSomething() const
    {
        printf("hello\n");
        age = 100;  // error: assignment of member ‘MyClass::age’ in read-only object
    }
    
    void change_value()
    {
        value = 100;    // error: assignment of read-only member ‘MyClass::value’
    }
    
public:
    int age;

    // 5、常量成员：const 可以用来声明类的成员变量为常量成员，表示该成员变量在对象创建后不能被修改。
    const int value;
};


int main()
{
    // 1、常量声明：const 可以用来声明常量，一旦被赋值就不能再被修改。
    const int MAX_VALUE = 100;
    //MAX_VALUE = 100;    // error: assignment of read-only variable ‘MAX_VALUE’

    // 4、指针：const 可以用来声明指向常量的指针，防止通过指针修改所指向的值。
    int TEMP = 1000;
    const int* ptr = &TEMP;
    //*ptr = 123; // error: assignment of read-only location ‘* ptr’
    ptr = &MAX_VALUE;
    printf("%d %d\n", TEMP, *ptr);  // 1000 100
    
    int* const p = &TEMP;
    *p = 123;
    //p = &MAX_VALUE; // error: assignment of read-only variable ‘p’ error: invalid conversion from ‘const int*’ to ‘int*’ [-fpermissive]
    int VALUE = 100;
    //p = &VALUE; // error: assignment of read-only variable ‘p’
    printf("%d %d\n", TEMP, *p);    // 123 123
    
    int const *pp = &TEMP;  // 都是正确的写法
    //*pp = 123;  // error: assignment of read-only location ‘* pp’
    pp = &VALUE;
    return 0;
}
