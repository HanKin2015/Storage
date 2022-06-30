/**
* 文 件 名: amazing_coredump.cpp
* 文件描述: 一个神奇的dump文件复现
* 作    者: HanKin
* 创建日期: 2022.06.30
* 修改日期：2022.06.30
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

// 赋值需要转换类型
static void test1()
{
	uint8_t *data = NULL;
	data = (uint8_t *)"hello world";
	printf("data: %s\n", data);
	return;
}

// 居然不会出现段错误
static void test2()
{
	const char *data = NULL;
	data = "hello world";
	printf("data: %s\n", data);
	return;
}

// 常指针不能赋值
static void test3()
{
	const char* const data = NULL;
	//data = "hello world";
	printf("data: %s\n", data);
	return;
}

// 段错误（这个也能看出strncpy的重要性）
static void test4()
{
	char *data = NULL;
	const char *str = "hello world";
	strncpy(data, str, strlen(str)-1);	// 正常来说后面的长度是data的长度
	printf("data: %s\n", data);
	return;
}

static void on_probe_rsp(char *data, int &len)
{
	free(data);
	data = NULL;
	len = 0;
	assert(data);
	return;
}

static void handle_ctrl_cbk(char *data, int len)
{
	char *tmp = (char *)malloc(len);
	if (len > 0) {
		memcpy(tmp, data, len);
		
		printf("data: %s, len: %d\n", data, len);
		on_probe_rsp(data, len);
	}
	return;
}
/*
一个神奇的段错误：在出错误的地方会显示data不为空指针，但是内容为空，长度为0

(gdb) r
Starting program: /media/sangfor/vdb/TransferStation/a.out
data: hello world
data: hello world
data: (null)
len: 20, size: 11
data: hello world, len: 11
a.out: amazing_coredump.cpp:59: void on_probe_rsp(char*, int&): Assertion `data' failed.

Program received signal SIGABRT, Aborted.
0x00007ffff7a42438 in raise () from /lib/x86_64-linux-gnu/libc.so.6
(gdb) bt
#0  0x00007ffff7a42438 in raise () from /lib/x86_64-linux-gnu/libc.so.6
#1  0x00007ffff7a4403a in abort () from /lib/x86_64-linux-gnu/libc.so.6
#2  0x00007ffff7a3abe7 in ?? () from /lib/x86_64-linux-gnu/libc.so.6
#3  0x00007ffff7a3ac92 in __assert_fail () from /lib/x86_64-linux-gnu/libc.so.6
#4  0x0000000000400873 in on_probe_rsp (data=0x0, len=@0x7fffffffe2c4: 0) at amazing_coredump.cpp:59
#5  0x00000000004008e2 in handle_ctrl_cbk (data=0x602420 "", len=0) at amazing_coredump.cpp:70
#6  0x0000000000400980 in test5 () at amazing_coredump.cpp:107
#7  0x00000000004009b6 in main () at amazing_coredump.cpp:121
*/
static void test5()
{
	int len = 20;
	char *data = (char *)malloc(len);
	memset(data, 0, len);
	const char *str = "hello world";
	strncpy(data, str, len - 1);
	printf("len: %d, size: %lu\n", len, strlen(data));

	handle_ctrl_cbk(data, strlen(data));
	
	free(data);
	data = NULL;
	len = 0;
	return;
}

int main()
{
	test1();
	test2();
	test3();
	//test4();
	test5();
	return 0;
}