#include <iostream>
#include <omp.h>

int main()
{
    #pragma omp parallel
    {
        if (omp_get_thread_num() == 0) {
            std::cout << "Number of threads: " << omp_get_num_threads() << std::endl;
        }
    }

    long long sum = 0;
    double start = omp_get_wtime();  // 记录开始时间

    const long long N = 1e10;  // 显式转换为整数
    #pragma omp parallel for reduction(+:sum)  // 关键：使用归约，每个线程私有sum，最后合并
    for (long long i = 1; i <= N; i++) {
        sum += i;
    }

    double end = omp_get_wtime();
    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Code took " << (end - start) * 1000 << " milliseconds." << std::endl;
    return 0;
}