/*******************************************************************************
* 文 件 名: 运算符优先级.cpp
* 文件描述: 先算加减乘除，再计算-=
* 备    注: 
* 作    者: HanKin
* 创建日期: 2023.07.28
* 修改日期：2025.07.28
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/

#include <cstdio>
#include <iostream>

int main(int argc, char *argv[])
{
    int x = 100;
    x -= 20 - 10;
    std::cout << x << std::endl;    // 90

    int y = 100;
    y -= 20 + 10;
    std::cout << y << std::endl;    // 70
    return 0;
}