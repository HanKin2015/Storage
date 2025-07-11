/*******************************************************************************
* 文 件 名: initializer_list_example.cpp
* 文件描述: 当所有参数的类型一样时，可以使用std::initializer_list
* 备    注: 
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