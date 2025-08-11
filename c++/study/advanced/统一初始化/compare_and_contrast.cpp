/*******************************************************************************
* 文 件 名: compare_and_contrast.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.11
* 修改日期：2025.08.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

class MyClass
{
public:
    MyClass() {}
    ~MyClass() {}
};

void c98()
{
    std::cout << __func__ << std::endl;
    
    // 基础类型
    int x = 1;
    int y(1);
    std::cout << x << ' ' << y << std::endl;
    
    // 类对象 (默认构造)
    MyClass obj;
    // warning: empty parentheses were disambiguated as a function declaration [-Wvexing-parse]
    // 能正常编译，但是有警告
    //MyClass err(); // 陷阱!

    // 窄化转换
    int xx = 3.14; // 隐式转换，数据丢失
    return;
}

void c11()
{
    std::cout << __func__ << std::endl;
    
    // 基础类型
    int x{1};
    int y = {1};
    std::cout << x << ' ' << y << std::endl;
    
    // 类对象 (默认构造)
    MyClass obj{};

    // 窄化转换
    int xx{3.14}; // 编译错误
    return;
}

int main()
{
    c98();
    c11();
    return 0;
}