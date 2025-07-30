/*******************************************************************************
* 文 件 名: mutable_example.cpp
* 文件描述: 用于修饰类的成员变量，允许该变量在 const 成员函数中被修改。
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.29
* 修改日期：2025.07.29
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

class Example {
private:
    //mutable int counter;  // 声明为 mutable
    int counter;    // error: increment of member ‘Example::counter’ in read-only object

public:
    void doSomething() const {  // const 成员函数
        counter++;  // 合法：mutable 变量可在 const 函数中修改
    }
};

int main()
{
    return 0;
}