/*******************************************************************************
* 文 件 名: constexpr_const_compare.cpp
* 文件描述: 
* 备    注: 待编译，在线编译器无法使用
* 作    者: HanKin
* 创建日期: 2025.07.11
* 修改日期：2025.07.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <ctime>
#include <cstdio>

constexpr long long fib_constexpr(int n) 
{ 
    return (n <= 1) ? n : fib_constexpr(n-1) + fib_constexpr(n-2);
} 

const long long fib_const(int n)
{
    return (n <= 1) ? n : fib_const(n-1) + fib_const(n-2);
}

void test_constexpr()
{
	time_t timestamp = time(NULL);
	char *timestr = ctime(&timestamp);
    printf("%lu 当前时间为：%s\n", timestamp, timestr);
	
	std::cout << fib_constexpr(45) << std::endl;
	
	timestamp = time(NULL);
	timestr = ctime(&timestamp);
    printf("%lu 当前时间为：%s\n", timestamp, timestr);
}

void test_const()
{
	time_t timestamp = time(NULL);
	char *timestr = ctime(&timestamp);
    printf("%lu 当前时间为：%s\n", timestamp, timestr);
	
	std::cout << fib_const(35) << std::endl;
	
	timestamp = time(NULL);
	timestr = ctime(&timestamp);
    printf("%lu 当前时间为：%s\n", timestamp, timestr);
}

int main()
{
	test_constexpr();
	test_const();
	return 0;
}