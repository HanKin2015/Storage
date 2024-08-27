/*******************************************************************************
* 文 件 名: mutex_example.cpp
* 文件描述: 在编程中，mutex（互斥锁）是一种同步原语，用于保护共享资源，以防止多个线程同时访问或修改该资源
* 备    注: g++ mutex_example.cpp -lpthread -std=c++11
* 作    者: HanKin
* 创建日期: 2024.08.27
* 修改日期：2024.08.27
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <mutex>
#include <thread>

std::mutex mtx;  // 全局变量

//可以尝试将关于锁的操作去掉，有什么效果
void *function(void *arg)
{
    char *m;
    m = (char *)arg;
    mtx.lock();
    while (*m != '\0') {
        printf("%c", *m);
        fflush(stdout);
        m++;
        usleep(3e5);
    }
    printf("\n");
    mtx.unlock();
    //return;   // 加上会有警告：
}

int main(int argc, char *argv[])
{
    char *str1 = (char *)"hello";
    char *str2 = (char *)"wolrd";

    std::thread thread1(function, str1);
    std::thread thread2(function, str2);

    thread1.join();
    thread2.join();
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
hello
wolrd
[root@ubuntu0006:~/cmake] #vi a.pp
[root@ubuntu0006:~/cmake] #g++ a.cpp -lpthread -std=c++11
[root@ubuntu0006:~/cmake] #./a.out
hwoellrldo

[root@ubuntu0006:~/cmake] #./a.out
whoellrldo

*/
