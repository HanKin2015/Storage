/**
* 文 件 名: study_string.cpp
* 文件描述: 学习字符串相关操作
* 作    者: HanKin
* 创建日期: 2021.10.26
* 修改日期：2021.10.26
*
* Copyright (c) 2021 HanKin. All rights reserved.
*/
#include <iostream>
#include <string>
#include <cstring>
#include <string.h>
#include <strings.h>
#inlcude <stdio.h>
using namespace std;

void C()
{
	char *str = "abcdefgde";
	char c = 'd';
	
	// 1、字符查找
	char *a = strchr(str, c);
	char *b = strrchr(str, c);
	printf("%s %s\n", a, b);
	
	// 2、
	return;
}

void CPLUSPLUS()
{
	string source_str = "abcdefgde";
	string object_str = "de";
	
	string str1 = "abcdefgde";
	string str2 = "de";
	
	// 1、字符串查找
	int a = str1.find(str2);         		//查找str1中第一次出现str2的位置，并返回（包括0）
	int b = str1.rfind(str2);        		//查找str1中最后次出现str2的位置，并返回（包括0）
	int c = str1.find_first_of(str2);		//查找在str2中任意一个·字符·在str1中第一次出现的位置，并返回（包括0）
	int d = str1.find_last_of(str2);		//查找在str2中任意一个·字符·在str1中最后一次出现的位置，并返回（包括0）
	int e = str1.find_first_not_of(str2);	//查找str1中第一个不属于str2中的·字符·的位置，并返回（包括0）
	int f = str1.find_last_not_of(str2);	//查找str1中最后一个不属于str2中的·字符·的位置，并返回（包括0）
	printf("%d %d %d %d %d %d\n", a, b, c, d, e, f);
	
	// 2、字符串截取
	basic_string<char> g = str1.substr(2, 4);	//截取s中从pos开始（包括0）的n个字符的子串，并返回
	string h = str1.substr(2);					//截取s中从从pos开始（包括0）到末尾的所有字符的子串，并返回
	printf("%s %s\n", g.c_str(), h.data());
	
	// 3、字符串替换
	string i = str1.replace(2, 4, str2);	//用str2替换str1中从pos开始（包括0）的n个字符的子串
	printf("%s\n", i.data());
	
	// 4、字符串比较
	
	// 5、字符串拼接
	return;
}

// 不写头文件strings.h也是能正常编译的
void OTHER()
{
	char *a = "aBcDeF";
	char *b = "AbCdEf";
	char *c = "abKLDSHAJ";
	if (!strcasecmp(a, b)) {
		printf("%s = %s\n", a, b);
	}
	if (!strncasecmp(a, c, 2)) {
		printf("%s = %s\n", a, c);
	}
	return;
}

int main()
{
    C();
	CPLUSPLUS();
	OTHER();
    return 0;
}
