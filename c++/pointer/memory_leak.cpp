/*******************************************************************************
* 文 件 名: memory_leak.cpp
* 文件描述: new int和new int()区别
* 备    注: 注意new int已分配好指针，重新指向则会导致内存泄漏
* 作    者: HanKin
* 创建日期: 2025.08.04
* 修改日期：2025.08.04
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

int main()
{
    int n = 100;
    // 此时 p1 和 p2 分别指向两块动态分配的内存（p1 指向的内存值不确定，p2 指向的内存值为 0）
    int *p1 = new int;  // 分配一块未初始化的int内存，p1指向该内存
    int *p2 = new int();// 分配一块初始化为0的int内存，p2指向该内存
    std::cout << *p1 << ' ' << *p2 << std::endl;
    delete p1;
    delete p2;
    p1 = &n;
    p2 = &n;
    std::cout << *p1 << ' ' << *p2 << std::endl;
    // 这里不需要再释放内存了，因为n不是动态分配的
    return 0;
}
/*
valgrind --leak-check=full ./your_program  # 运行程序并检测内存泄漏

g++ -fsanitize=address -g your_code.cpp -o your_program
./your_program  # 运行时自动检测并输出内存问题

root@hankin:~/opencv# g++ main.cpp -lasan
root@hankin:~/opencv# ./a.out 
-1094795586 0
100 100
root@hankin:~/opencv# g++ main.cpp
root@hankin:~/opencv# ./a.out 
0 0
100 100
*/