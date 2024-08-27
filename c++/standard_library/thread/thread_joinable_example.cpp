/*******************************************************************************
* 文 件 名: thread_joinable_example.cpp
* 文件描述: C++11中提供的线程类叫做std::thread(https://blog.csdn.net/weixin_48856218/article/details/137497800)
* 备    注: g++ thread_example.cpp -lpthread -std=c++11
* 作    者: HanKin
* 创建日期: 2024.08.27
* 修改日期：2024.08.27
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

void foo()
{
    this_thread::sleep_for(std::chrono::seconds(1));
}

int main()
{
    thread t;
    cout << "before starting, joinable: " << t.joinable() << endl;

    t = thread(foo);
    cout << "after starting, joinable: " << t.joinable() << endl;

    t.join();
    cout << "after joining, joinable: " << t.joinable() << endl;

    thread t1(foo);
    cout << "after starting, joinable: " << t1.joinable() << endl;
    t1.detach();
    cout << "after detaching, joinable: " << t1.joinable() << endl;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
before starting, joinable: 0
after starting, joinable: 1
after joining, joinable: 0
after starting, joinable: 1
after detaching, joinable: 0
*/