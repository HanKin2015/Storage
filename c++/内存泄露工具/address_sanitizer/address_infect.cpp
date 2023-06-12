/**
* 文 件 名: address_infect.cpp
* 文件描述: 地址感染
* 作    者: HanKin
* 创建日期: 2022.12.27
* 修改日期：2022.12.27
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <iostream>
#include <stdio.h>
using namespace std;

int main()
{
    // 被测代码：预埋一个栈溢出bug
    int num[5] = {0};
    num[5] = 100;
    printf("num[5] = %d\n", num[5]);
    return 0;
}
