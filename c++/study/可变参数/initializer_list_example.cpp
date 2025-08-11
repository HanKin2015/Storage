/*******************************************************************************
* 文 件 名: initializer_list_example.cpp
* 文件描述: 当所有参数的类型一样时，可以使用std::initializer_list
* 备    注: 它并非容器，而是一个轻量级的迭代器范围，指向存储在常量区的临时数组（列表元素的拷贝）。其内部包含两个指针（或指针 + 长度），分别指向列表的首元素和尾后位置
std::initializer_list 中的元素是常量（const T），不能修改其值
std::initializer_list 一旦创建，长度就固定了，不能动态添加或删除元素
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <initializer_list>
#include <list>
#include <vector>

// 计算多个整数的和
int sum(std::initializer_list<int> args)
{
    int total = 0;
    for (int num : args) {
        total += num;
    }
    return total;
}

int sum_list(std::list<int> args)
{
    int total = 0;
    for (int num : args) {
        total += num;
    }
    return total;
}

int sum_vector(std::vector<int> args)
{
    int total = 0;
    for (int num : args) {
        total += num;
    }
    return total;
}

int main()
{
    std::cout << sum({1, 2, 3}) << std::endl; // 输出6
    std::cout << sum({10, 20, 30, 40}) << std::endl; // 输出100

    std::cout << sum_list({10, 20, 30, 40}) << std::endl;
    std::cout << sum_vector({10, 20, 30, 40}) << std::endl;
    return 0;
}