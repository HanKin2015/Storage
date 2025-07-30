/*******************************************************************************
* 文 件 名: class_init_list.cpp
* 文件描述: 初始化列表中各个成员的初始化顺序不是由初始化列表本身的书写顺序决定的，而是严格遵循它们在类定义中被声明的顺序。这一点非常重要，避免因初始化顺序引发的潜在错误。
* 备    注: 难道是我想错了嘛，我记得开发过程中如果初始化顺序不一致会编译失败的。后续遇到后再探究
* 作    者: HanKin
* 创建日期: 2025.07.29
* 修改日期：2025.07.29
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

class Test {
public:
    Test(int x, int y, int z): m_x(x), m_y(y), m_z(z) {}

    void print()
    {
        std::cout << m_x << ' ' << m_y << ' ' << m_z << std::endl;
    }

private:
    int m_z;
    int m_y;
    int m_x;
};

int main()
{
    Test *obj = new Test(4, 5, 6);
    obj->print();
    return 0;
}