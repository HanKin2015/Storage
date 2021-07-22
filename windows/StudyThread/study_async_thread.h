#pragma once

#include <iostream>
#include <thread>
#include <mutex>
#include <future>
#include <Windows.h>
using namespace std;

/*
* std::async是一个函数模板，用来启动一个异步任务，它返回一个std::future类模板对象，future对象起到了占位的作用（记住这点就可以了）。
* 开始实例化的future是没有储存值的，但在调用std::future对象的get()成员函数时，主线程会被阻塞直到异步线程执行结束，
* 并把返回结果传递给std::future，即通过FutureObject.get()获取函数返回值。
* 
* 即隐藏调用了一个join函数
* 
* std::future与std::shard_future的用途都是为了占位，但是两者有些许差别。std::future的get()成员函数是转移数据所有权;
* std::shared_future的get()成员函数是复制数据。 因此： future对象的get()只能调用一次；无法实现多个线程等待同一个异步线程，
* 一旦其中一个线程获取了异步线程的返回值，其他线程就无法再次获取。 std::shared_future对象的get()可以调用多次；
* 可以实现多个线程等待同一个异步线程，每个线程都可以获取异步线程的返回值。
*/
double t1(const double a, const double b)
{
    double c = a + b;
    Sleep(3000);//假设t1函数是个复杂的计算过程，需要消耗3秒
    return c;
}
void study_async()
{
    double a = 2.3;
    double b = 6.7;
    future<double> fu = async(t1, a, b);//创建异步线程线程，并将线程的执行结果用fu占位；
    cout << "正在进行计算" << endl;
    cout << "计算结果马上就准备好，请您耐心等待" << endl;
    cout << "计算结果：" << fu.get() << endl;//阻塞主线程，直至异步线程return
    //cout << "计算结果：" << fu.get() << endl;//取消该语句注释后运行会报错，因为future对象的get()方法只能调用一次。
    return;
}

int study_async_thread()
{
    study_async();
    return 0;
}