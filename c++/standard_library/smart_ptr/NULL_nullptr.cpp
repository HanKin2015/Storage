/*******************************************************************************
* 文 件 名: NULL_nullptr.cpp
* 文件描述: 在c++中如果表示空指针语义时建议使用nullptr而不要使用NULL，因为NULL本质上是个int型的0，其实不是个指针
* 备    注: nullptr是c++11用来表示空指针新引入的常量值
* 作    者: HanKin
* 创建日期: 2024.01.22
* 修改日期：2024.01.22
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
using namespace std;

void func(void *ptr)
{
    cout << "func ptr" << endl;
}

void func(int i)
{
    cout << "func i" << endl;
}

int main()
{
    func(NULL);     // 编译失败，会产生二义性(error: call of overloaded ‘func(NULL)’ is ambiguous)
    func(nullptr);  // 输出func ptr
    return 0;
}