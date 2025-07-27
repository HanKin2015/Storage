
/*******************************************************************************
* 文 件 名: omp_parallel_for.cpp
* 文件描述: 
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.23
* 修改日期：2025.07.23
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <omp.h>
#include <chrono>
#include <thread>

void task(int index)
{
    std::cout << "execute the task " << index << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return;
}

int main()
{
    double start = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < 5; ++i) {
        task(i + 1);
    }

    double end = omp_get_wtime();
    std::cout << "Code took " << (end - start) * 1000 << "milliseconds" << std::endl;
    return 0;
}
/*
root@hankin:~/opencv# OMP_NUM_THREADS=4 ./a.out 
execute the task 1
execute the task 5
execute the task 3
execute the task 4
execute the task 2
Code took 4001.26milliseconds
root@hankin:~/opencv# OMP_NUM_THREADS=2 ./a.out 
execute the task 1
execute the task 4
execute the task 2
execute the task 5
execute the task 3
Code took 6001.92milliseconds
root@hankin:~/opencv# OMP_NUM_THREADS=1 ./a.out 
execute the task 1
execute the task 2
execute the task 3
execute the task 4
execute the task 5
Code took 10002.8milliseconds
root@hankin:~/opencv# OMP_NUM_THREADS=3 ./a.out 
execute the task 1
execute the task 5
execute the task 3
execute the task 4
execute the task 2
Code took 4001.26milliseconds
*/