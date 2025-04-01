/**
* 文 件 名: wunused-variable.cpp
* 文件描述: 在 C++ 中，除以零并不会抛出一个标准异常（如 std::exception）。相反，除以零会导致未定义行为，通常会导致程序崩溃或产生运行时错误。
* 备    注: 使用VS2019编译会有警告warning C4101: “e”: 未引用的局部变量，但是GCC没有
* 作    者: HanKin
* 创建日期: 2025.03.11
* 修改日期：2025.03.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*/
#include <iostream>
#include <string>
#include <exception>
#include <cstdio>

int main()
{
    int x = 5;
    int y = 0;
    try {
        if (y == 0) {
            throw std::runtime_error("除数不能为零"); // 手动抛出异常
        }
        double ret = static_cast<double>(x) / y; // 确保进行浮点除法


        double ret = x / y;
        printf("ret = %f\n", ret);
    } catch (const std::runtime_error&) {   // 如果你不需要异常信息，可以完全省略参数名，但这在 C++ 中并不总是被允许，具体取决于编译器
        std::cout << "代码段抛出了异常。" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "代码段抛出了异常。" << std::endl;
    }
    return 0;
}
/*
[root@ubuntu0006:/media/vdb/TransferStation] #g++ wunused-variable.cpp -Wall -Werror -Wextra
[root@ubuntu0006:/media/vdb/TransferStation] #./a.out
Floating point exception (core dumped)
*/