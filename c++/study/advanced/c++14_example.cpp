/*******************************************************************************
* 文 件 名: c++14_example.cpp
* 文件描述: 高级用法杂烩
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.04.24
* 修改日期：2025.04.24
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <memory>

int main()
{
    std::shared_ptr<int> p = std::make_shared<int>();
    std::cout << *p << std::endl;
    return 0;
}