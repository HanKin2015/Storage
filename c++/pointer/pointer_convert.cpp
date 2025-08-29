/*******************************************************************************
* 文 件 名: pointer_convert.cpp
* 文件描述: 输出不是5，用到了空类型指针void*，类型不安全
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.28
* 修改日期：2025.08.28
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
using namespace std;

int main()
{
    int i = 5;
    void* pInt = &i;
    double d = (*(double*)pInt);
    cout << d << endl;  // 奇奇怪怪的值
    return 0;
}