/**
* 文 件 名: fprintf_example.cpp
* 文件描述: 学习fprintf函数
* 作    者: HanKin
* 创建日期: 2022.09.17
* 修改日期：2022.12.06
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <iostream>
#include <stdio.h>
#include <unistd.h>
using namespace std;

void test1()
{
	const char *log = "this is a log";

	FILE *fp = fopen("./log.txt", "a");
	if (!fp) return;
	fprintf(fp, "%s\n", log);
	fclose(fp);
	return;
}

void test2()
{
	const char *log = "this this this";
	fprintf(stderr, "%s\n", log);
	return;
}

int main()
{
	test1();
	test2();

	printf("%d\n", STDIN_FILENO);
	printf("%d\n", STDOUT_FILENO);
	printf("%d\n", STDERR_FILENO);
	printf("%p\n", stdin);
	printf("%p\n", stdout);
	printf("%p\n", stderr);
	return 0;
}
