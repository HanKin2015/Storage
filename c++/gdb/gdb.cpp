/**
* 文 件 名: gdb.cpp
* 文件描述: 学习gdb调试
* 作    者: HanKin
* 创建日期: 2021.10.06
* 修改日期：2021.10.06
*
* Copyright (c) 2021 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>

// 不需要这么复杂的段错误，只需要assert或者抛异常即可
void *tfn(void *arg)
{
	int i = 0;
	printf("arg = %p, arg addr = %p\n", arg, &arg);
	if (arg != NULL) {
		//i = *((int *)&arg);   // 正确写法
		i = *((int *)arg);      // 加参数使用会有Segmentation fault
	}
	printf("i = %d\n", i);
	return NULL;
}

int main(int argc, char *argv[])
{
	int a = 0;
	printf("a = %p\n", a);

	int n = 1;
	if (argc == 2) {
		n = atoi(argv[1]);
	}

	for (int i = 0; i < n; i++) {
		printf("i addr = %p\n", &i);
		tfn((void *)(long)i);
	}
	return 0;
}


