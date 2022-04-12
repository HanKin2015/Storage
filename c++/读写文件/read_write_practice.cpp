/**
* 文 件 名: read_write.cpp
* 文件描述: 探究读写文件速度效率
* 作    者: HanKin
* 参    考: https://blog.csdn.net/ZHANG_TIMI/article/details/118120684
* 创建日期: 2022.04.09
* 修改日期：2022.04.09
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <iostream>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <inttypes.h>
#define DATA_COUNT		30*1024*1024
#define BUF_MAX			60*1024*1024
#define ROW_DATA_COUNT 100
#define DATA_MAX_VALUE 10
using namespace std;

// 字符串转化为数组
void analyse(char *buf, int len=BUF_MAX, uint8_t *data)
{
	int i = 0;
	for (char *p = buf; *p && p-buf < len; p++) {
		if (*p != ' ') {
			data[i++] = *p;
		}
	}
	return;
}

char buf[BUF_MAX];
void read_file(const char *file_name)
{
	uint8_t *data = NULL;
	size_t len = 0;
	
	data = (uint8_t *)malloc(sizeof(uint8_t) * DATA_COUNT);
	if (data == NULL) {
		printf("malloc failed!\n");
		return;
	}
	memset(data, 0, sizeof(data));
	
	freopen(file_name, "rb", stdin);
	len = fread(buf, 1, BUF_MAX, stdin);
	buf[len] = '\0';
	analyse(buf, len, data);
	return;
}

int main(int argc, char *argv[])
{
	const char *file_name = "./data.txt";
	
	int start = clock();
	// 生成数据
	//generate_data(file_name);

	read_file(file_name);
	printf("本次用时: %.3lf s\n", double(clock() - start) / CLOCKS_PER_SEC);
	return 0;
}