/**
* 文 件 名: function_class_example.cpp
* 文件描述: 
* 备    注：g++ function_class_example.cpp -std=c++11 -lpthread
* 作    者: HanKin
* 创建日期: 2022.06.08
* 修改日期：2023.06.08
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <iostream>
#include <thread>

using namespace std;

class Task {
public:
    void task1() const {
        cout << "task1\n";
    }

    void task2() const {
        cout << "task2\n";
    }

    void operator()() const {
        task1();
        task2();
    }
};

int main()
{
    Task task;
    thread t(task);
    t.join();
    return 0;
}
/*
[root@ubuntu0006:~/cmake/build] #./a.out
task1
task2
*/