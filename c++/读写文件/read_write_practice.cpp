/**
* 文 件 名: read_write_practice.cpp
* 文件描述: 读写文件的最佳实践
* 作    者: HanKin
* 创建日期: 2022.04.12
* 修改日期：2022.04.12
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
#include <string.h>
#include <assert.h>
// 默认测试30MB数据，文件大小60MB
#define DATA_COUNT		5*1024*1024		// 5,242,880
#define BUF_MAX			10*1024*1024	//10,485,760
#define ROW_DATA_COUNT 100
#define DATA_MAX_VALUE 10
using namespace std;

// 生成数据
static int generate_data(const char *file_name)
{
	assert(file_name);
	
	srand((unsigned)time(NULL));
	
	FILE *fp = fopen(file_name, "w");
	if (fp == NULL) {
		printf("err: open file failed!\n");
		return -1;
	}

	for (int i = 1; i <= DATA_COUNT; i++) {
		int data = rand() % DATA_MAX_VALUE;
		fprintf(fp, "%d%c", data, i % ROW_DATA_COUNT ? ' ' : '\n');
	}
	fclose(fp);
	fp = NULL;
	return 0;
}

#ifndef DATA_COUNT
	#define DATA_COUNT		5*1024*1024
#endif
#ifndef BUF_MAX
	#define BUF_MAX			10*1024*1024
#endif
#ifndef MAXN
	#define MAXN			50000
#endif
// 字符串转化为数组
static void analyse(uint8_t *data, char *buf, int len=BUF_MAX)
{
	assert(data);
	assert(buf);
	
	int i = 0;
	for (char *p = buf; *p && p-buf < len; p++) {
		if (*p != ' ' && *p != '\n') {
			//printf("i: %d, *p: %c\n", i, *p);
			data[i++] = *p - '0';
		}
	}
	return;
}

char buf[BUF_MAX];
static void read_file(const char *file_name, uint8_t *data)
{
	assert(file_name);
	assert(data);
	
	size_t len = 0;
	
	freopen(file_name, "rb", stdin);
	memset(buf, 0, sizeof(buf));
	len = fread(buf, 1, BUF_MAX, stdin);
	printf("fread len: %lu\n", len);
	buf[len] = '\0';
	analyse(data, buf, len);
	return;
}

#ifndef ROW_DATA_COUNT
	#define ROW_DATA_COUNT 100
#endif
static int write_file(const char *file_name, uint8_t *data)
{
	assert(file_name);
	assert(data);
	
	FILE *fp = fopen(file_name, "w");
	if (fp == NULL) {
		printf("err: open file failed!\n");
		return -1;
	}

	for (int i = 1; i <= DATA_COUNT; i++) {
		fprintf(fp, "%c%c", data[i-1], i % ROW_DATA_COUNT ? ' ' : '\n');
	}
	fclose(fp);
	fp = NULL;
	return 0;
}

static int fwrite_file(const char *file_name, uint8_t *data)
{
	assert(file_name);
	assert(data);
	
	size_t len = 0;
	
	freopen(file_name, "w", stdout);
	len = fwrite(data, 1, DATA_COUNT, stdout);
	printf("fwrite len: %lu\n", len);
	return 0;
}

int main(int argc, char *argv[])
{
	const char *file_in_name  = "./data_in.txt";
	const char *file_out_name = "./data_out.txt";
	uint8_t *data = NULL;
	size_t len = MAXN + 1;
	
	data = (uint8_t *)malloc(sizeof(uint8_t) * DATA_COUNT);
	if (data == NULL) {
		printf("malloc failed!\n");
		return -1;
	}
	printf("sizeof(data): %lu, sizeof(*data): %lu\n", sizeof(data), sizeof(*data));
	memset(data, 0, sizeof(*data) * DATA_COUNT);
	
	int start = clock();
	// 生成数据
	//generate_data(file_in_name);
	
	// 不固定大小读取的话不好对比，因此设计成同样大小即可
	if (len > MAXN) {
		start = clock();
		data = (uint8_t *)realloc(data, sizeof(uint8_t) * DATA_COUNT);
		if (data == NULL) {
			printf("realloc failed!\n");
			return -1;
		}
		len = DATA_COUNT;
		read_file(file_in_name, data);
		printf("read用时: %.3lf s\n", double(clock() - start) / CLOCKS_PER_SEC);
	}
	
	for (int i = 0; i < 20; i++)
	{
		printf("%02x ", data[i]);
		//printf("%c ", data[i]);
	}
	printf("\n");
	
	// 这里需要写入到多个文件中，并不是单纯的覆盖
	static int file_index = 0;
	do {
		char file_name[105] = { 0 };
		(void)snprintf(file_name, 105, "data_out_%d.txt", file_index);
		file_index++;
		if (len > MAXN) {
			start = clock();
			//fwrite_file(file_name, data);
			data = (uint8_t *)realloc(data, sizeof(uint8_t) * DATA_COUNT);
			if (data == NULL) {
				printf("realloc failed!\n");
				return -1;
			}
			len = DATA_COUNT;
			write_file(file_name, data);
			printf("write用时: %.3lf s\n", double(clock() - start) / CLOCKS_PER_SEC);
		}
	} while (file_index < 5);
	return 0;
}