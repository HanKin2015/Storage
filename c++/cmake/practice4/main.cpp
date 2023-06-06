#include <iostream>
#include <cstdio>
#include "mymath.h"
#include <functional>

int main()
{
    int ret = sum(5, 6);
    printf("ret = %d\n", ret);
    
    // 使用function封装函数指针
    std::function<int(int, int)> func = sum;
    std::cout << func(1, 2) << std::endl; // 输出3
    return 0;
}