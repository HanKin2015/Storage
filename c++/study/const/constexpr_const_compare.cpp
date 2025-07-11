/*******************************************************************************
* 文 件 名: constexpr_const_compare.cpp
* 文件描述: constexpr编译时很费时间
* 备    注: 
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
	
	constexpr long long ret = fib_constexpr(45);
	std::cout << ret << std::endl;
	
	timestamp = time(NULL);
	timestr = ctime(&timestamp);
    printf("%lu 当前时间为：%s\n", timestamp, timestr);
}

void test_const()
{
	time_t timestamp = time(NULL);
	char *timestr = ctime(&timestamp);
    printf("%lu 当前时间为：%s\n", timestamp, timestr);
	
	const long long ret = fib_const(45);
	std::cout << ret << std::endl;
	
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
/*
root@hankin:~# g++ k.cpp -fconstexpr-ops-limit=1000000000
root@hankin:~# ./a.out 
1752216711 当前时间为：Fri Jul 11 14:51:51 2025

102334155
1752216711 当前时间为：Fri Jul 11 14:51:51 2025

1752216711 当前时间为：Fri Jul 11 14:51:51 2025

102334155
1752216712 当前时间为：Fri Jul 11 14:51:52 2025
*/