/**
* 文 件 名: hash_example.cpp
* 文件描述: 学习hash函数
* 备    注：g++ hash_example.cpp -std=c++11
* 作    者: HanKin
* 创建日期: 2022.06.05
* 修改日期：2023.06.05
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <iostream>
#include <string>
#include <functional>
#include <limits.h>

using namespace std;

int main() {
    string str = "hello, world";
    size_t hash_value = hash<string>{}(str);
    cout << "hash value: " << hash_value << endl;
    cout << sizeof(int) << ' ' << sizeof(size_t) << endl;
    cout << sizeof(long) << ' ' << sizeof(long long) << endl;
    cout << LONG_MAX << ' ' << LONG_LONG_MAX << endl;
    return 0;
}
/*
hash value: 4795077891475041234
4 8
8 8
9223372036854775807 9223372036854775807
*/
