/*******************************************************************************
* 文 件 名: hello_openmp.cpp
* 文件描述: 尝试着在编译选项里使用和不使用-openmp 这个编译选项分别编译并执行代码
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.07.23
* 修改日期：2025.07.23
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>

int main()
{
#ifdef _OPENMP  // 如果定义了这个宏
	std::cout << "Hello, OpenMP!" << std::endl;
#else
	std::cout << "OpenMP is not enabled." << std::endl;
#endif
	return 0;
}
/*
root@hankin:~/opencv# g++ main.cpp  -Wall -fopenmp
root@hankin:~/opencv# ./a.out 
Hello, OpenMP!
root@hankin:~/opencv# g++ main.cpp  -Wall
root@hankin:~/opencv# ./a.out 
OpenMP is not enabled.
*/
