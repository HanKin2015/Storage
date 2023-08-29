/**
* 文 件 名: unique_ptr_example.cpp
* 文件描述: unique_ptr指针
* 作    者: HanKin
* 创建日期: 2023.08.21
* 修改日期：2023.08.21
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include <iostream>
#include <string>
#include <cstdio>
#include <memory>
using namespace std;

int main()
{
    unique_ptr<string> ps(new string ("I reigned lonely as a cloud."));
    //unique_ptr<string> vocation(ps);    //编译出错，已禁止拷贝
    //unique_ptr<string> vocation = ps;   //编译出错，已禁止拷贝
    unique_ptr<string> vocation = std::move(ps);  //控制权限转移
    
    if (ps.get() != nullptr) {  // 判空操作更安全
        //printf("%p %p\n", ps, vocation);
        /*
        尝试复制一个被声明为 unique_ptr 的对象，但是 unique_ptr 是独占所有权的智能指针，不能被复制。这是为了确保资源的独占性，避免多个指针同时管理同一个资源，导致资源的重复释放等问题。

        如果你需要在多个地方使用同一个资源，可以考虑使用 shared_ptr，它允许多个指针共享同一个资源，并在最后一个指针被销毁时释放资源。

        如果你需要在不同的地方使用同一个 unique_ptr，可以考虑使用 std::move 将所有权转移给另一个 unique_ptr，或者使用 std::unique_ptr::release 方法释放所有权，然后手动管理资源的生命周期。
        */
        printf("%p\n", ps.release());
    }
    
    if (vocation.get() != nullptr) {  // 判空操作更安全
        //printf("%p %p\n", ps, vocation);
        printf("%p\n", vocation.release());
    }
    
    // reset函数的重要性
    unique_ptr<int> null_up1;   // 创建空智能指针
    null_up1.reset(new int(3)); // 绑定动态对象
    printf("null_up1 = %d\n", *null_up1);
    unique_ptr<int> null_up2;
    //null_up2 = new int(3);      // 编译不通过，不支持这种赋值
    null_up2 = std::make_unique<int>(3);    // std::make_unique 是 C++14 引入的函数
    printf("null_up2 = %d\n", *null_up2);
    unique_ptr<int> null_up3(new int(3));
    printf("null_up3 = %d\n", *null_up3);
    
    // 段错误
    cout << *vocation << endl;
    cout << *ps << endl;
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
0x216dc20
null_up1 = 3
null_up2 = 3
null_up3 = 3
段错误
*/
