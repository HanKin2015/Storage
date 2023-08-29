/**
* 文 件 名: auto_ptr_example.cpp
* 文件描述: auto_ptr指针
* 作    者: HanKin
* 创建日期: 2023.08.21
* 修改日期：2023.08.21
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
using namespace std;

int main()
{
    auto_ptr<string> ps(new string ("I reigned lonely as a cloud."));
    auto_ptr<string> vocation;
    vocation = ps;
    
    printf("%p %p\n", ps, vocation);
    
    cout << *vocation << endl;
    cout << *ps << endl;    // 段错误
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
0x7ffd9018d550 0x7ffd9018d560
I reigned lonely as a cloud.
段错误
[root@ubuntu0006:~/cmake] #cppcheck k.cpp
Checking k.cpp...
*/
