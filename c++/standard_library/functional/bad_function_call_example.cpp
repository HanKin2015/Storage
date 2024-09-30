/**
* 文 件 名: bad_function_call_example.cpp
* 文件描述: 学习functional库
* 备    注：g++ placeholders_example.cpp -std=c++11
* 作    者: HanKin
* 创建日期: 2024.09.29
* 修改日期：2024.09.29
*
* Copyright (c) 2024 HanKin. All rights reserved.
*/
#include <iostream>
#include <functional>

int main()
{
    std::function<void()> func;

    try {
        func(); // 调用空的 std::function 对象
    } catch (const std::bad_function_call& e) {
        std::cerr << "Caught std::bad_function_call: " << e.what() << std::endl;
    }

    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
Caught std::bad_function_call: bad_function_call
*/