/**
* 文 件 名: mem_fn_example.cpp
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

struct Foo {
    void display(int x) const
    {
        std::cout << "Foo::display called with " << x << std::endl;
        return;
    }
};

int main()
{
    Foo foo;
    auto memFunc = std::mem_fn(&Foo::display);
    memFunc(foo, 42); // 输出: Foo::display called with 42

    return 0;
}


