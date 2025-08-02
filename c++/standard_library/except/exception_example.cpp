/*******************************************************************************
* 文 件 名: exception_example.cpp
* 文件描述: <exception>中定义了exception类
            <new>中定义了bad_alloc类
            <type_info>中定义了bad_cast类
            <stdexcept>中定义了runtime_error、logic_error类
            所有的异常类都是exception类的子类。
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.03.10
* 修改日期：2025.03.10
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <exception>

class MyException : public std::exception
{
public:
    const char* what() const throw()
    {
        return "My custom exception";
    }
};

int main()
{
    try {
        // 模拟一个错误情况
        bool error_condition = true;
        if (error_condition) {
            throw MyException();
        }
    } catch (const MyException& e) {  // 自定义的异常必须要在标准异常的前面，否则会有警告
        std::cout << "Caught an MyException: " << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Caught an exception: " << e.what() << std::endl;  // Caught an exception: My custom exception
    }

    return 0;
}