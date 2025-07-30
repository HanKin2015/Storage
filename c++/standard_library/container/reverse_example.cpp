/*******************************************************************************
* 文 件 名: reverse_example.cpp
* 文件描述: reverse 是标准库提供的一个函数，用于反转容器或数组中的元素顺序。
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.29
* 修改日期：2025.07.29
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

int main()
{
    // 反转数组
    int arr[] = {1, 2, 3, 4, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    std::reverse(arr, arr + n);
    std::cout << "Reversed array: ";
    for (int i = 0; i < n; ++i)
        std::cout << arr[i] << " ";  // 输出: 5 4 3 2 1
    std::cout << std::endl;

    // 反转 vector
    std::vector<int> vec = {10, 20, 30, 40};
    std::reverse(vec.begin(), vec.end());
    std::cout << "Reversed vector: ";
    for (int num : vec)
        std::cout << num << " ";  // 输出: 40 30 20 10
    std::cout << std::endl;

    // 反转字符串
    std::string str = "hello";
    std::reverse(str.begin(), str.end());
    std::cout << "Reversed string: " << str << std::endl;  // 输出: olleh

    return 0;
}