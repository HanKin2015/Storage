/**
* 文 件 名: move_example.cpp
* 文件描述: C++ 标准库使用比如vector::push_back 等这类函数时,会对参数的对象进行复制,连数据也会复制.这就会造成对象内存的额外创建, 本来原意是想把参数push_back进去就行了,通过std::move，可以避免不必要的拷贝操作。
            std::move是为性能而生。
            std::move是将对象的状态或者所有权从一个对象转移到另一个对象，只是转移，没有内存的搬迁或者内存拷贝。
* 作    者: HanKin
* 创建日期: 2023.07.24
* 修改日期：2023.07.24
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <iostream>
#include <vector>
#include <string>

int main()
{
    std::string str = "Hello";
    std::vector<std::string> v;
    //调用常规的拷贝构造函数，新建字符数组，拷贝数据
    v.push_back(str);
    std::cout << "After copy, str is \"" << str << "\"\n";
    //调用移动构造函数，掏空str，掏空后，最好不要使用str
    v.push_back(std::move(str));
    std::cout << "After move, str is \"" << str << "\"\n";
    std::cout << "The contents of the vector are \"" << v[0]
                                         << "\", \"" << v[1] << "\"\n";
}
/*
[root@ubuntu0006:~/cmake] #g++ k.cpp -g --std=c++11
[root@ubuntu0006:~/cmake] #./a.out
After copy, str is "Hello"
After move, str is ""
The contents of the vector are "Hello", "Hello"
*/