/*******************************************************************************
* 文 件 名: iota_example.cpp
* 文件描述: 源自希腊字母 ι（iota），在数学中常用于表示递增值
* 备    注: 该算法的主要功能是用连续递增的值填充一个区间，常用于初始化数组或容器
* 作    者: HanKin
* 创建日期: 2025.07.23
* 修改日期：2025.07.23
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <vector>
#include <numeric>
#include <ctime>

// 加括号可以声明作用域，因此不会出现重复定义问题
#define PRINT_CUR_TIME() {  \
    time_t timestamp = time(NULL);  \
    char *time_str = ctime(&timestamp); \
    std::cout << timestamp << ' ' << time_str;  \
}

int main()
{
    clock_t start = clock();  // 开始计时

    const int N = 1e9;
    PRINT_CUR_TIME();
    std::vector<int> data(N);
    PRINT_CUR_TIME();
    std::cout << data[10] << std::endl;
    std::iota(data.begin(), data.end(), 3);  // 填充 1~N
    PRINT_CUR_TIME();
    std::cout << data[10] << std::endl;

    clock_t end = clock();    // 结束计时
    double time_taken = double(end - start) / CLOCKS_PER_SEC;  // 转换为秒
    std::cout << "Code took " << time_taken * 1000 << " milliseconds." << std::endl;
    return 0;
}
/*
root@hankin:~/opencv# g++ main.cpp -Wall
root@hankin:~/opencv# ./a.out 
1753260023 Wed Jul 23 16:40:23 2025
1753260027 Wed Jul 23 16:40:27 2025
0
1753260032 Wed Jul 23 16:40:32 2025
13
Code took 9239.24 milliseconds.
*/