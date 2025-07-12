/*******************************************************************************
* 文 件 名: isalnum_example.cpp
* 文件描述: 判断字符是否为字母数字字符，如果 c 是字母或数字，返回非零值（通常为 1），但是我这里返回的是8
* 备    注: isalpha(c)：判断字符是否为字母（A-Z 或 a-z）。
			isdigit(c)：判断字符是否为数字（0-9）。
			isalnum(c)：等价于 isalpha(c) || isdigit(c)。
			isxdigit(c)：判断字符是否为十六进制数字（0-9, A-F, a-f）。
* 作    者: HanKin
* 创建日期: 2025.07.13
* 修改日期：2025.07.13
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <string>
#include <cctype>

int main()
{
	std::cout << std::isalnum('a') << std::endl;
	std::cout << std::isalnum('A') << std::endl;
	std::cout << std::isalnum('_') << std::endl;
	std::cout << std::isalnum('3') << std::endl;
	return 0;
}