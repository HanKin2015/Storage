/**
 * 文 件 名: watchpoint_example.cpp
 * 备    注: g++ watchpoint_example.cpp -g -lpthread -std=c++11
 * 文件描述: 在GDB中通过添加watchpoint来观察一段内存，这段内存被修改时程序将会停止
 * 作    者: HanKin
 * 创建日期: 2023.01.05
 * 修改日期：2023.01.05
 *
 * Copyright (c) 2023 HanKin. All rights reserved.
 */

#include <iostream>
#include <thread>
using namespace std;

// 线程修改变量值
void memory_write(int* value)
{
    *value = 1;
}

int main()
{
    int a = 10;
    // 获取局部变量a的地址
    int* c = &a;

    for (int i = 0; i < 100; i++) {
        a += i;
    }

    cout << a << endl;

    // 将变量a的地址传递到线程
    thread t(memory_write, c);
    t.join();

    cout << a << endl;
    return 0;
}
