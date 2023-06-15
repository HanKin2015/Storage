/**
* 文 件 名: scope_guard.cpp
* 文件描述: 可以使用RAII（Resource Acquisition Is Initialization）技术来实现作用域退出。RAII是一种C++编程技术，它利用了C++对象的构造函数和析构函数的自动调用机制，来管理资源的获取和释放
* 备    注：感觉跟一般的类没有什么区别
* 作    者: HanKin
* 创建日期: 2023.06.14
* 修改日期：2023.06.14
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <iostream>
#include <functional>

class ScopeGuard
{
public:
    ScopeGuard(std::function<void()> func) : func_(func) {}
    ~ScopeGuard() { func_(); }
private:
    std::function<void()> func_;
};

int main()
{
    std::cout << "Enter main" << std::endl;

    {
        // lambda表达式
        ScopeGuard guard([]() { std::cout << "Exit scope" << std::endl; });
        std::cout << "Inside scope" << std::endl;
    }

    std::cout << "Leave main" << std::endl;
    return 0;
}
/*
[root@ubuntu0006:~/cmake/hj] #./a.out
Enter main
Inside scope
Exit scope
Leave main
[root@ubuntu0006:~/cmake/hj] #g++ scope_guard.cpp -std=c++11
*/