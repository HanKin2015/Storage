/*******************************************************************************
* 文 件 名: compare_between_array_and_vector.cpp
* 文件描述: 既然std::vector用起来那么灵活，干嘛还要std::array
* 备    注: std::array为确定性、高性能和类型安全二生的
* 作    者: HanKin
* 创建日期: 2025.08.06
* 修改日期：2025.08.06
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <vector>
#include <array>

int main()
{
    std::vector<int> v = {1, 2, 3};
    std::array<int, 3> a{1, 2, 3};
    
    std::cout << sizeof(v) << std::endl;
    std::cout << sizeof(a) << std::endl;
    return 0;
}
