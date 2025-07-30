/*******************************************************************************
* 文 件 名: 单例模式.cpp
* 文件描述: 确保一个类只有一个实例，并提供全局访问点。
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.18
* 修改日期：2025.07.18
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

class Singleton {
private:
    Singleton() = default;  // 私有构造函数
    Singleton(const Singleton&) = delete;  // 禁用拷贝构造
    Singleton& operator=(const Singleton&) = delete;  // 禁用赋值运算符

public:
    static Singleton* getInstance() {
        if (instance == nullptr) {
            instance = new Singleton();
        }
        return instance;
    }

    void print_info()
    {
        std::cout << "hello world" << std::endl;
        return;
    }

private:
    static Singleton* instance;
};

// 静态成员初始化
Singleton* Singleton::instance = nullptr;

int main(int argc, char **argv)
{
    Singleton *obj = Singleton::getInstance();
    obj->print_info();
    Singleton::getInstance()->print_info();
    return 0;
}
/*
root@hankin:~/opencv# g++ main.cpp 
root@hankin:~/opencv# ./a.out 
hello world
hello world
*/