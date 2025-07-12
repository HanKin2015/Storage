/*******************************************************************************
* 文 件 名: regex_example.cpp
* 文件描述: 正则表达式
* 备    注: ^$锚定符，表示匹配字符串的开始和结束位置
* 作    者: HanKin
* 创建日期: 2025.07.13
* 修改日期：2025.07.13
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <string>
#include <regex>

int main()
{
	std::string str = " hello world";
	std::regex pattern("^[a-zA-Z0-9_]+$";
	if (std::regex_match(str, pattern)) {
		std::cout << "yes" << std::endl;
	} else {
		std::cout << "no" << std::endl;
	}
	return 0;
}