/**
* 文 件 名: weak_ptr_example.cpp
* 文件描述: weak_ptr指针
* 作    者: HanKin
* 创建日期: 2023.09.01
* 修改日期：2023.09.01
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include <assert.h>
#include <iostream>
#include <memory>
#include <string>

using namespace std;

int main()
{
    shared_ptr<int> sp(new int(10));
    assert(sp.use_count() == 1);
    weak_ptr<int> wp(sp); 	// 从 shared_ptr 创建 weak_ptr
    assert(wp.use_count() == 1);
    if (!wp.expired()) {	// 判断 weak_ptr 观察的对象是否失效
        shared_ptr<int> sp2 = wp.lock();	// 获得一个 shared_ptr
        *sp2 = 100;
        assert(wp.use_count() == 2);
    }
    assert(wp.use_count() == 1);
    cout << "int:" << *sp << endl;
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
int:100
*/