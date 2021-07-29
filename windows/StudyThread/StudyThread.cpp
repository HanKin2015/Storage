// StudyThread.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <thread>
#include <ctime>
#include <cstdio>
#include <windows.h>
#include "study_lock.h"
#include "study_async_thread.h"

using namespace std;

// 获取主线程id
thread::id main_thread_id = this_thread::get_id();

// 输出YYDS
void hello()
{
    cout << "Hello World!\n";
    if (main_thread_id == this_thread::get_id()) {
        cout << "This is the main thread.\n";
    }
    else {
        cout << "This is not the main thread.\n";
    }
    return;
}

// 暂停线程n秒
void pause_thread(int idx, int n) {
    this_thread::sleep_for(chrono::seconds(n));
    cout << "thread id<" << idx << "> pause of " << n << " seconds ended\n";
    return;
}

// 简单示例
void demo()
{
    thread t(hello);
    cout << "hardware_concurrency: " << t.hardware_concurrency() << endl;//可以并发执行多少个(不准确)
    cout << "native_handle: " << t.native_handle() << endl;              //可以并发执行多少个(不准确)
    t.join();
    thread a(hello);
    a.detach();
    thread threads[5];                         // 默认构造线程

    cout << "Spawning 5 threads...\n";
    for (int i = 0; i < 5; ++i) {
        threads[i] = thread(pause_thread, i + 1, 5 - i);   // move-assign threads
    }
    cout << "Done spawning threads. Now waiting for them to join:\n";
    // 要注意内存泄露问题。如果设置为 PTHREAD_CREATE_JOINABLE，就继续用 pthread_join() 来等待和释放资源，否则会内存泄露。
    // 当线程启动后，一定要在和线程相关联的std::thread对象销毁前，对线程运用join()或者detach()方法。
    // join()与detach()都是std::thread类的成员函数，是两种线程阻塞方法，两者的区别是是否等待子线程执行结束。
    for (auto& thread : threads) {
        thread.join();
    }
    cout << "All threads joined!\n";
    return;
}

void func(int idx)
{
    int n = 2000;
    Sleep(n);
    printf("idx<%d> sleep %d seconds done.\n", idx, n / 1000);
    return;
}

void hello_thread()
{
    // 1、普通使用方式
    clock_t start_time = clock();
    for (int i = 0; i < 2; i++) {
        func(i + 1);
    }
    clock_t spent_time = clock() - start_time;
    printf("exec time is %lf s.\n", (double)spent_time / CLOCKS_PER_SEC);

    // 2、多线程节省时间
    start_time = clock();
    thread threads[2];
    for (int i = 0; i < 2; i++) {
        threads[i] = thread(func, i + 1);
    }
    spent_time = clock() - start_time;
    printf("here do not need to wait thread done. %lf s.\n", (double)spent_time / CLOCKS_PER_SEC);
    for (auto& thread : threads) {
        thread.join();
    }
    printf("here need to wait thread done.\n");
    spent_time = clock() - start_time;
    printf("exec time is %lf s.\n", (double)spent_time / CLOCKS_PER_SEC);

    // 3、最大线程数量
    start_time = clock();
    const int THREAD_NUM = 166;
    thread tds[THREAD_NUM];
    for (int i = 0; i < THREAD_NUM; i++) {
        tds[i] = thread(func, i + 1);
    }

    // 很奇怪,166个线程也是同时完成,难道没有限制?可能是操作太简单.
    cout << tds[0].hardware_concurrency() << endl;              // 4
    cout << "native_handle: " << tds[0].native_handle() << endl;// 166

    for (auto& thread : tds) {
        thread.join();
    }
    spent_time = clock() - start_time;
    printf("exec time is %lf s.\n", (double)spent_time / CLOCKS_PER_SEC);
    return;
}

int main()
{
    //hello_thread();
    //test_study_lock();
    test_study_async_thread();
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
