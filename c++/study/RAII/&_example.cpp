/*******************************************************************************
* 文 件 名: &_example.cpp
* 文件描述: 探索lambda函数中的&
* 备    注：其实这个在D:\Github\GitBook\gitbook\C++\lambda.md有详细说明
* 作    者: HanKin
* 创建日期: 2024.01.26
* 修改日期：2024.01.26
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <functional>
#include <cstdio>
#include <malloc.h>
#include <cstdlib>
#include <string.h>

class ScopeGuard
{
public:
    ScopeGuard(std::function<void()> func) : func_(func) {}
    ~ScopeGuard() { func_(); }
private:
    std::function<void()> func_;
};

// 这里的作用其实就是取了一个类名，最终名字为onScopeExit38
#define SCOPEGUARD_LINENAME_CAT(name, line) onScopeExit##line
#define SCOPEGUARD_LINENAME(name, line) SCOPEGUARD_LINENAME_CAT(name, line)
#define ON_SCOPE_EXIT(callback) ScopeGuard SCOPEGUARD_LINENAME(EXIT, __LINE__)([&]callback) 

void test()
{
    printf("enter in test function\n");
    int *arr = NULL;
    
    // 利用类使用超出域后自动析构机制
    ON_SCOPE_EXIT({ if (arr) { printf("free arr\n"); free(arr); arr = NULL; } });
    
    /*
    在这段代码中，& 符号用于捕获外部变量 arr，这是因为在 Lambda 表达式 [&] 中，我们希望在 Lambda 函数中可以访问并修改 arr 变量。通过使用 [&]，我们实现了按引用捕获，这意味着在 Lambda 函数中对 arr 的修改会影响到外部的 arr 变量。

    在这个特定的例子中，& 的使用是为了确保在 ScopeGuard 对象的析构函数中能够正确释放 arr 变量所分配的内存。因为 arr 是在 test1 函数中分配的内存，我们希望在 ScopeGuard 对象被销毁时能够自动释放这块内存，因此需要在 Lambda 函数中捕获 arr  变量，以便在析构函数中执行相应的释放操作。

    总之，& 的使用确保了在 Lambda 函数中能够访问并修改外部变量 arr，并且在 ScopeGuard 对象的析构函数中能够正确释放 arr 所分配的内存。
    */
    // ScopeGuard guard([&]() { if (arr) { printf("free arr\n"); free(arr); arr = NULL; } });
    
    arr = (int *)malloc(100 * sizeof(int));
    memset(arr, 0, 100);
    arr[50] = 123;
    printf("%d\n", arr[50]);
    printf("enter out test function\n");
    return;
}

int main()
{
    printf("call test\n");
    test();
    printf("enter main\n");
    return 0;
}