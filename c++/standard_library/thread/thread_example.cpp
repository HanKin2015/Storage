/*******************************************************************************
* 文 件 名: thread_example.cpp
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

using namespace std;

void func(int num, string str)
{
    for (int i = 0; i < 10; i++) {
        cout << "子线程: i = " << i << ", num: " 
             << num << ", str: " << str << endl;
    }
}

void func1()
{
    for (int i = 0; i < 10; ++i) {
        cout << "子线程: i = " << i << endl;
    }
}

int main()
{
    cout << "主线程的线程ID: " << this_thread::get_id() << endl;
    thread t(func, 520, "i love you");
    thread t1(func1);
    cout << "线程t 的线程ID: " << t.get_id() << endl;
    cout << "线程t1的线程ID: " << t1.get_id() << endl;
    t.join();
    t1.join();
}
/*
[root@ubuntu0006:~/cmake] #./a.out
主线程的线程ID: 139827614619456
线程t 的线程ID: 139827597256448
线程t1的线程ID: 139827588863744
子线程: i = 0
子线程: i = 1
子线程: i = 2
子线程: i = 3
子线程: i = 4
子线程: i = 5
子线程: i = 6
子线程: i = 7
子线程: i = 8
子线程: i = 9
子线程: i = 0, num: 520, str: i love you
子线程: i = 1, num: 520, str: i love you
子线程: i = 2, num: 520, str: i love you
子线程: i = 3, num: 520, str: i love you
子线程: i = 4, num: 520, str: i love you
子线程: i = 5, num: 520, str: i love you
子线程: i = 6, num: 520, str: i love you
子线程: i = 7, num: 520, str: i love you
子线程: i = 8, num: 520, str: i love you
子线程: i = 9, num: 520, str: i love you
*/
