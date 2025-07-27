/*******************************************************************************
* 文 件 名: unique_reference.cpp
* 文件描述: 
* 备    注: g++ unique_reference.cpp -std=c++14
* 作    者: HanKin
* 创建日期: 2025.04.19
* 修改日期：2025.04.19
*
* Copyright (c) 2025 HanKin. All rights reserved.
*/
#include <iostream>
#include <string>
#include <cstdio>
#include <memory>

template <typename T>
using up = std::unique_ptr<T>;

class Father {
public:
    Father(up<int> loop): m_loop(std::move(loop)) {}
    ~Father() {}

    void print_m_loop()
    {
        printf("m_loop = %d\n", *m_loop);
        return;
    }

private:
    up<int> m_loop;
};

class Son {
public:
    Son(up<int>& loop): m_loop(loop) {}
    ~Son() {}

    void print_m_loop()
    {
        printf("m_loop = %d\n", *m_loop);
        return;
    }

private:
    up<int> m_loop;
};

int main()
{
    up<int> loop = std::make_unique<int>(42);
    Father *f = new Father(std::move(loop));
    f->print_m_loop();
    delete f;
    f = nullptr;

    Son *s = new Son(loop);
    s->print_m_loop();
    delete s;
    s = nullptr;
    return 0;
}
