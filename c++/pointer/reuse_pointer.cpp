/**
* 文 件 名: reuse_pointer.cpp
* 文件描述: 重复使用指针变量是否存在问题
* 作    者: HanKin
* 创建日期: 2023.07.11
* 修改日期：2023.07.11
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#include <cstdlib>
#include <vector>
using namespace std;

static void test1()
{
    printf("%d: %s\n", __LINE__, __FUNCTION__);
    //int *p = NULL;    // 因此p指针是可以提前写
    int n = 5;
    
    vector<int *> vec;
    for (int i = 0; i < 10; i++) {
        int *p = (int *)calloc(1, sizeof(int));
        n = i;
        //p = &n;   // 因为一直指向的是n的地址，n的地址最后是指向了9
        *p = i;
        printf("pointer p address %p\n", p);
        vec.push_back(p);
    }
    
    printf("vec size %lu\n", vec.size());
    for (int *iter : vec) {
        printf("%d\n", *iter);
    }
    
    /*
    在循环中，每次都会分配一个新的int类型的内存空间，并将指针p指向该空间，然后将p加入到vector中。
    但是，在每次循环中，都会将n的值赋值给p，这意味着每个指针都指向了同一个变量n的地址，而不是指向
    分配的新内存空间的地址。因此，vector中的所有指针都指向同一个变量n，而不是指向不同的内存空间。
    这会导致在释放内存时出现问题，因为多个指针指向同一个内存空间，释放一个指针的内存空间后，其他
    指针将指向已经释放的内存空间，这可能会导致程序崩溃或产生未定义的行为。
    */
    free(vec[5]);
    vec[5] = NULL;
    if (!vec[1]) {
        printf("说明是同一个地址，这种分配方式存在问题\n");
    } else {
        printf("说明不是同一个地址，这种分配方式不存在问题\n");
    }
    return;
}

static void test2()
{
    printf("%d: %s\n", __LINE__, __FUNCTION__);
    int *p = (int *)calloc(1, sizeof(int));
    
    vector<int *> vec;
    for (int i = 0; i < 10; i++) {
        *p = i;
        printf("pointer p address %p\n", p);
        vec.push_back(p);
    }
    
    printf("vec size %lu\n", vec.size());
    for (int *iter : vec) {
        printf("%d\n", *iter);
    }
    
    free(vec[5]);
    vec[5] = NULL;
    if (!vec[1]) {
        printf("说明是同一个地址，这种分配方式存在问题\n");
    } else {
        printf("说明不是同一个地址，这种分配方式不存在问题\n");
    }
    return;
}

static void test3()
{
    printf("%d: %s\n", __LINE__, __FUNCTION__);
    int *p = NULL;
    
    vector<int *> vec;
    for (int i = 0; i < 10; i++) {
        p = (int *)calloc(1, sizeof(int));
        *p = i;
        printf("pointer p address %p\n", p);
        vec.push_back(p);
    }
    
    printf("vec size %lu\n", vec.size());
    for (int *iter : vec) {
        printf("%d\n", *iter);
    }
    
    free(vec[5]);
    vec[5] = NULL;
    if (!vec[1]) {
        printf("说明是同一个地址，这种分配方式存在问题\n");
    } else {
        printf("说明不是同一个地址，这种分配方式不存在问题\n");
    }
    return;
}

static void test4()
{
    printf("%d: %s\n", __LINE__, __FUNCTION__);
    vector<int *> vec;
    for (int i = 0; i < 10; i++) {
        int *p = (int *)calloc(1, sizeof(int));
        *p = i;
        printf("pointer p address %p\n", p);
        vec.push_back(p);
    }
    
    printf("vec size %lu\n", vec.size());
    for (int *iter : vec) {
        printf("%d\n", *iter);
    }
    
    free(vec[5]);
    vec[5] = NULL;
    if (!vec[1]) {
        printf("说明是同一个地址，这种分配方式存在问题\n");
    } else {
        printf("说明不是同一个地址，这种分配方式不存在问题\n");
    }
    return;
}

// 崩溃的原因是变量n是在栈上分配的，而不是通过malloc或calloc函数分配的，因此不能使用free函数释放它
static void test5()
{
    printf("%d: %s\n", __LINE__, __FUNCTION__);
    int *p = NULL, *q = NULL;
    int n = 5;
    p = &n;
    q = &n;
    
    free(p);
    p = NULL;
    if (!q) {
        printf("说明是同一个地址，这种分配方式存在问题\n");
    } else {
        printf("说明不是同一个地址，这种分配方式不存在问题\n");
    }
    return;
}

static void test6()
{
    printf("%d: %s\n", __LINE__, __FUNCTION__);
    int *p = NULL, *q = NULL;
    int n = 5;
    
    p = (int *)calloc(1, sizeof(int));
    *p = n;
    q = p;
    printf("p[%p] = %d, q[%p] = %d\n", p, *p, q, *q);
    
    free(p);
    p = NULL;
    if (!q) {
        printf("说明是同一个地址，这种分配方式存在问题\n");
    } else {
        printf("q[%p] = %d\n", q, *q);
        free(q);
        q = NULL;
        printf("说明不是同一个地址，这种分配方式不存在问题\n");
    }
    return;
}

int main(int argc, char *argv[])
{
    test1();
    test2();
    test3();
    test4();
    //test5();
    test6();
    return 0;
}
/*
(gdb) bt
#0  0x00007ffff74aa438 in raise () from /lib/x86_64-linux-gnu/libc.so.6
#1  0x00007ffff74ac03a in abort () from /lib/x86_64-linux-gnu/libc.so.6
#2  0x00007ffff74ec7fa in ?? () from /lib/x86_64-linux-gnu/libc.so.6
#3  0x00007ffff74f538a in ?? () from /lib/x86_64-linux-gnu/libc.so.6
#4  0x00007ffff74f958c in free () from /lib/x86_64-linux-gnu/libc.so.6
#5  0x0000000000401348 in test5 () at k.cpp:146
#6  0x00000000004013ac in main (argc=1, argv=0x7fffffffe468) at k.cpp:162
(gdb) f 5
#5  0x0000000000401348 in test5 () at k.cpp:146
146         free(p);
(gdb) print *p
$1 = 5
(gdb) print *q
$2 = 5
(gdb) print p
$3 = (int *) 0x7fffffffe344
(gdb) print q
$4 = (int *) 0x7fffffffe344
(gdb)
*/