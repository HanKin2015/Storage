/**
* 文 件 名: hash_example.cpp
* 文件描述: 学习functional库
* 备    注：g++ placeholders_example.cpp -std=c++11
* 作    者: HanKin
* 创建日期: 2024.09.27
* 修改日期：2025.09.02
*
* Copyright (c) 2025 HanKin. All rights reserved.
*/
#include <iostream>
#include <functional>
#include <string>
#include <limits.h>

int main()
{
    std::hash<std::string> hash_fn;
    std::string s = "Hello, World!";
    size_t hash = hash_fn(s);
    std::cout << "Hash of \"" << s << "\": " << hash << std::endl;

    std::string str = "hello, world";
    size_t hash_value1 = std::hash<std::string>{}(str);
    std::cout << "hash value1: " << hash_value1 << std::endl;
    size_t hash_value2 = std::hash<std::string>()(str);
    std::cout << "hash value2: " << hash_value2 << std::endl;
    std::cout << sizeof(int) << ' ' << sizeof(size_t) << std::endl;
    std::cout << sizeof(long) << ' ' << sizeof(long long) << std::endl;
    std::cout << LONG_MAX << ' ' << LONG_LONG_MAX << std::endl;
    return 0;
}
/*
root@hankin:~/opencv# ./a.out 
Hash of "Hello, World!": 18371290486108036847
hash value1: 4795077891475041234
hash value2: 4795077891475041234
4 8
8 8
9223372036854775807 9223372036854775807
root@hankin:~/opencv# ./a.out 
Hash of "Hello, World!": 18371290486108036847
hash value1: 4795077891475041234
hash value2: 4795077891475041234
4 8
8 8
9223372036854775807 9223372036854775807
*/

