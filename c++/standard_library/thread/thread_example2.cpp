/*******************************************************************************
* 文 件 名: thread_example2.cpp
* 文件描述: 调用类里面的函数需要给类指针
* 备    注: g++ thread_example2.cpp -lpthread -std=c++11
* 作    者: HanKin
* 创建日期: 2025.03.19
* 修改日期：2025.03.19
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <thread>

using namespace std;

class MyClass {
public:
    void myFunction(int a) {
        std::cout << "Value: " << a << std::endl;
    }
};

int main()
{
    MyClass obj;
    cout << "主线程的线程ID: " << this_thread::get_id() << endl;
    thread t1(&MyClass::myFunction, &obj, 42);  // 没有地址符error: invalid use of non-static member function ‘void MyClass::myFunction(int)’
    cout << "线程t1 的线程ID: " << t1.get_id() << endl;
    t1.join();   // 等待线程完成

    // 使用 std::bind
    auto boundFunction = std::bind(&MyClass::myFunction, &obj, 42);
    std::thread t2(boundFunction);
    t2.join();

    // 或者使用 Lambda 表达式
    std::thread t3([&obj]() { obj.myFunction(42); });
    t3.join();

    return 0;
}
/*
[root@ubuntu0006:/media] #g++ thread_example2.cpp --std=c++11 -lpthread
[root@ubuntu0006:/media] #./a.out
主线程的线程ID: 140558182065984
线程t1 的线程ID: 140558164702976
Value: 42
Value: 42
Value: 42
*/
