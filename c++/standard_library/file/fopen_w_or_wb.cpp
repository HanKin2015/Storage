/**
* 文 件 名: fopen_w_or_wb.cpp
* 文件描述: fopen函数的b参数作用
* 作    者: HanKin
* 创建日期: 2022.07.04
* 修改日期：2022.07.04
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <iostream>
#include <typeinfo>
#include <string>
#include <cstdio>
#include <cstring>
#include <cxxabi.h>
using namespace std;

static void test1()
{
	FILE *fp = fopen("out1.txt", "w");
	fprintf(fp, "hello world\n");
	fclose(fp);
	fp = NULL;
	return;
}

static void test2()
{
	FILE *fp = fopen("out2.txt", "wb");
	fprintf(fp, "hello world\n");
	fclose(fp);
	fp = NULL;
	return;
}

/*
[root@ubuntu0006:/media/hankin/vdb/TransferStation] #md5sum out1.txt
6f5902ac237024bdd0c176cb93063dc4  out1.txt
[root@ubuntu0006:/media/hankin/vdb/TransferStation] #md5sum out2.txt
6f5902ac237024bdd0c176cb93063dc4  out2.txt
*/
int main()
{
	test1();
	test2();
    return 0;
}