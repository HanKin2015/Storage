/**
* 文 件 名: hash_example.cpp
* 文件描述: 学习functional库
* 备    注：g++ placeholders_example.cpp -std=c++11
* 作    者: HanKin
* 创建日期: 2024.09.27
* 修改日期：2024.09.27
*
* Copyright (c) 2024 HanKin. All rights reserved.
*/
#include <iostream>
#include <functional>
#include <string>

int main() {
    std::hash<std::string> hash_fn;
    std::string s = "Hello, World!";
    size_t hash = hash_fn(s);
    std::cout << "Hash of \"" << s << "\": " << hash << std::endl;

    return 0;
}
