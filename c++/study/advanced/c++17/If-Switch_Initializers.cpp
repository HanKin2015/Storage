/*******************************************************************************
* 文 件 名: If-Switch_Initializers.cpp
* 文件描述: 在if/switch条件判断前，先初始化一个局部变量，变量作用域仅限于if/switch块，避免污染外部作用域。
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.08.25
* 修改日期：2025.08.25
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <mutex>
#include <vector>

std::mutex mtx;
std::vector<int> data;

void safeAccess(int val)
{
    // 初始化锁后，立即判断是否锁定成功（C++17前需单独声明lock_guard）
    if (std::lock_guard lg(mtx); !data.empty()) { 
        data.push_back(val);
    }

    // switch同理：先初始化变量，再判断分支
    switch (int x = val % 3; x) { 
        case 0: std::cout << "x is 0\n"; break;
        case 1: std::cout << "x is 1\n"; break;
    }
}

int main()
{
    safeAccess(100);
    return 0;
}