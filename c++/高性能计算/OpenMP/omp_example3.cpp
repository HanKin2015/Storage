/*******************************************************************************
* 文 件 名: omp_example3.cpp
* 文件描述: 你会发现std::endl;居然会跟前面的语句脱节
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.23
* 修改日期：2025.07.23
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include<omp.h>

int main()
{
    #pragma omp parallel
    {
        std::cout << "Hello, world!" << std::endl;
    }
    return 0;
}
/*
root@hankin:~/opencv# OMP_NUM_THREADS=1 ./a.out 
Hello, world!
root@hankin:~/opencv# OMP_NUM_THREADS=2 ./a.out 
Hello, world!
Hello, world!
root@hankin:~/opencv# OMP_NUM_THREADS=3 ./a.out 
Hello, world!
Hello, world!
Hello, world!
root@hankin:~/opencv# OMP_NUM_THREADS=4 ./a.out 
Hello, world!
Hello, world!
Hello, world!
Hello, world!
root@hankin:~/opencv# OMP_NUM_THREADS=4 ./a.out 
Hello, world!Hello, world!
Hello, world!Hello, world!


*/