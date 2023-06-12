/**
* 文 件 名: main.cpp
* 文件描述: 调用so文件使用
* 备    注：g++ main.cpp -Lbuild/ -lmymath -std=c++11
* 作    者: HanKin
* 创建日期: 2023.06.09
* 修改日期：2023.06.09
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <iostream>
#include <cstdio>
#include "mymath.h"
#include <functional>

int main()
{
    int ret = sum(5, 6);
    printf("ret = %d\n", ret);
    
    // 使用function封装函数指针
    std::function<int(int, int)> func = sum;
    std::cout << func(1, 2) << std::endl; // 输出3
    return 0;
}