/**
* 文 件 名: parameter_usable.cpp
* 文件描述: 函数参数是否需要使用到引用
* 作    者: HanKin
* 创建日期: 2023.07.10
* 修改日期：2023.07.10
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#include <cstdlib>
#include <vector>
#include <algorithm>    // 使用remove函数一定需要这个头文件
using namespace std;

static void func1(vector<int> vec)
{
    printf("func1 vec size = %lu\n", vec.size());
    vec.push_back(7);
    vec.push_back(8);
    return;
}

static void func2(vector<int> &vec)
{
    printf("func2 vec size = %lu\n", vec.size());
    vec.push_back(9);
    vec.push_back(10);
    return;
}

int main(int argc, char *argv[])
{
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    v.push_back(6);
    
    int count = v.size();
    printf("count = %d\n", count);
    for (int i = 0; i < count; i++) {
        printf("%d%c", v[i], i == count - 1 ? '\n' : ' ');
    }

    func1(v);
    printf("v size = %lu\n", v.size());
    func2(v);
    printf("v size = %lu\n", v.size());
    return 0;
}