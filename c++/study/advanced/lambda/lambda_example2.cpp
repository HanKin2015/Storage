/**
* 文 件 名: lambda_example.cpp
* 文件描述: 
* 备    注：g++ lambda_example.cpp -std=c++11 -lpthread
* 作    者: HanKin
* 创建日期: 2022.06.08
* 修改日期：2023.06.08
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <thread>
#include <iostream>

using namespace std;

void task1() {
	cout << "task1\n";
}

void task2() {
	cout << "task2\n";
}

int main()
{
    thread t([] {
        task1();
        task2();
    });
    t.join();
}
/*
[root@ubuntu0006:~/cmake/build] #./a.out
task1
task2
*/