/*******************************************************************************
* 文 件 名: const_error.cpp
* 文件描述: error: passing ‘const Count’ as ‘this’ argument discards qualifiers [-fpermissive]
* 备    注: https://blog.csdn.net/u010168781/article/details/103399188
* 作    者: HanKin
* 创建日期: 2024.01.03
* 修改日期：2024.01.03
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstdio>

struct Count {
    uint32_t c;

    Count(uint32_t i=0):c(i) {}

    // add(const Count& count)的参数count是const的，在函数内部使用是调用了count.getCount()；但是getCount是非const的
    uint32_t getCount() const {
        return c;
    }

    uint32_t add(const Count& count) {
        uint32_t total = c + count.getCount();
        return total;
    }
};

int main()
{
    return 0;
}