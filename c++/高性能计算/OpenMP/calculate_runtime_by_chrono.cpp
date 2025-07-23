/*******************************************************************************
* 文 件 名: calculate_runtime_by_chrono.cpp
* 文件描述: 如果不添加-fopenmp参数编译则程序无法使用并行计算，即使程序中含有#pragma，编译是正常
* 备    注: 可以不添加-fopenmp参数进行编译
* 作    者: HanKin
* 创建日期: 2025.07.22
* 修改日期：2025.07.22
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <vector>
#include <numeric>
#include <omp.h>  // OpenMP 头文件
#include <chrono>

int main()
{
    // 开始计时
    auto start = std::chrono::high_resolution_clock::now();

    const int N = 2e9;
    long long sum = 0;
    // 并行区域：多个线程共同计算总和
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; ++i) {
        sum += i;
    }

    std::cout << "Sum: " << sum << std::endl;

    // 结束计时
    auto end = std::chrono::high_resolution_clock::now();

    // 计算耗时（毫秒）
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Code took " << duration << " milliseconds." << std::endl;
    return 0;
}