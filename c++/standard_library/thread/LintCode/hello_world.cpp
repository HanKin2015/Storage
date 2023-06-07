/**
* 文 件 名: hello_world.cpp
* 文件描述: 线程版的hello world
* 备    注：g++ hello_world.cpp -std=c++11 -lpthread
* 作    者: HanKin
* 创建日期: 2022.06.07
* 修改日期：2023.06.07
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <iostream>
#include <thread>

using namespace std;

void task()
{
    cout << "Hello World" << endl;
}

int main()
{
    thread t(task); // C++ 11 开始支持的线程标准库
    t.join();       // 通过 join() 函数即可启用该线程
    return 0;
}