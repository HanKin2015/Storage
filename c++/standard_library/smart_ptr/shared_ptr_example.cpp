/**
* 文 件 名: shared_ptr_example.cpp
* 文件描述: shared_ptr指针
* 备    注: 智能指针不能使用new和delete函数
* 作    者: HanKin
* 创建日期: 2023.08.21
* 修改日期：2024.01.12
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
    shared_ptr<string> ps(new string("I reigned lonely as a cloud."));
    shared_ptr<string> vocation;
    vocation = ps;
    
    printf("%p %p\n", ps, vocation);
    
    cout << *vocation << endl;
    cout << *ps << endl;
    
    shared_ptr<int> null_up2;
    null_up2 = new int(3);  // error: no match for ‘operator=’ (operand types are ‘std::shared_ptr<int>’ and ‘int*’)
    printf("null_up2 = %d\n", *null_up2);
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #g++ k.cpp -std=c++11
[root@ubuntu0006:~/cmake] #./a.out
0x7ffc5576fb90 0x7ffc5576fba0
I reigned lonely as a cloud.
I reigned lonely as a cloud.
*/
