/**
* 文 件 名: for_each_example.cpp
* 文件描述: 
* 作    者: HanKin
* 创建日期: 2023.07.24
* 修改日期：2023.07.24
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <string.h>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char *argv[])
{
    vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    
    for_each(v.cbegin(), v.cend(), [](int elem) {
        cout << elem << " ";
    });
    cout << endl;
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #g++ k.cpp --std=c++11
[root@ubuntu0006:~/cmake] #./a.out
1 2 3 4 5
*/