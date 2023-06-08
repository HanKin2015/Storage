/**
* 文 件 名: join_detach_difference.cpp
* 文件描述: 在 C++ 的 API 中，提供了两种线程的运行方式，一种是 join（等待式），一种是 detach（分离式）
* 备    注：g++ join_detach_difference.cpp -std=c++11 -lpthread
* 作    者: HanKin
* 创建日期: 2022.06.08
* 修改日期：2023.06.08
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <thread>
#include <string>
#include <iostream>
#include <chrono>

using namespace std;

// 当线程以 join 方式运行时，那么线程依托的主线程将不会结束，直至线程执行完全部的任务
static void join_method()
{
    thread t([] {
        for (int i = 0; i < 3; ++i) {
            // 休眠 1 s
            this_thread::sleep_for(std::chrono::seconds(1));
            cout << ("second: " + to_string(i + 1)) << endl;
        };
    });
    t.join();
    cout << "main thread ending\n";
}

// 分离模式下的线程将从主线程进行分离，在调用 detach 模式运行线程后，主线程将不会阻塞
// 当使用 detach 模式时，你需要确保线程中没有访问可能被销毁的临时变量，否则可能出现意料之外的错误
// 可能看不出来是否打印了这段文字，可以通过创建文件方式来判断
static void detach_method()
{
    thread t([] {
        this_thread::sleep_for(std::chrono::milliseconds(3000));
        cout << "t thread ending\n";
    });
    t.detach();
    cout << "main thread ending\n";
}

int main()
{
    join_method();
    //detach_method();
    return 0;
}