calculate_runtime_by_clock.cpp
#include <iostream>
#include <vector>
#include <numeric>
#include <omp.h>  // OpenMP 头文件

int main()
{
    clock_t start = clock();  // 开始计时

    const int N = 2000000000;
    long long sum = 0;
    // 并行区域：多个线程共同计算总和
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; ++i) {
        sum += i;
    }

    std::cout << "Sum: " << sum << std::endl;

    clock_t end = clock();    // 结束计时
    double time_taken = double(end - start) / CLOCKS_PER_SEC;  // 转换为秒
    std::cout << "Code took " << time_taken * 1000 << " milliseconds." << std::endl;
    return 0;
}