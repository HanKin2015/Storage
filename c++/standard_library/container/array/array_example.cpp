/*******************************************************************************
* 文 件 名: array_example.cpp
* 文件描述: 定义在 <array> 头文件中，用于表示固定大小的数组
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.03.27
* 修改日期：2025.03.27
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <array>

int main()
{
    // 定义一个包含 5 个整数的 std::array
    std::array<int, 5> arr = {1, 2, 3, 4, 5};

    // 输出数组的大小
    std::cout << "Size of array: " << arr.size() << std::endl;

    // 遍历并输出数组元素
    for (const auto& element : arr) {
        std::cout << element << " ";
    }
    std::cout << std::endl;

    return 0;
}
