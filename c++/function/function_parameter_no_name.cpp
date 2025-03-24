/*******************************************************************************
* 文 件 名: function_parameter_no_name.cpp
* 文件描述: c++函数参数没有参数名的骚操作
* 备    注: https://www.zhihu.com/question/558268446
* 作    者: HanKin
* 创建日期: 2025.03.19
* 修改日期：2025.03.19
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <cstdio>
#include <iostream>

inline auto func1(int a, int = 2);
inline auto func2(int, int = 2);

void test(int x, int y, int = 10)
{
    printf("%d %d\n", x, y);
    return;
}

auto func1(int x, int y)
{
    printf("%d %d\n", x, y);
    return;
}

auto func2(int x, int y)
{
    printf("%d %d\n", x, y);
    return;
}

int main()
{
    test(1, 2);     // 1 2
    test(3, 4, 5);  // 3 4

    func1(1);       // 1 2
    func2(2);       // 2 2
    return 0;
}