/**
* 文 件 名: read_write_senior.cpp
* 文件描述: 探究读写文件速度效率
* 作    者: HanKin
* 参    考: https://blog.csdn.net/ZHANG_TIMI/article/details/118120684
* 创建日期: 2022.04.13
* 修改日期：2022.04.13
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
#define MAXN           5500000
#define DATA_COUNT     10*1024*1024	// 10MB数据，加空格就会有20MB数据
#define ROW_DATA_COUNT 100
#define DATA_MAX_VALUE 10
using namespace std;

static int generate_data(const char *file_name)
{
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

void read_file(const char *file_name)
{
	uint8_t *data = NULL;
	size_t  len   = 0;
	FILE    *fp   = NULL;
	
	fp = fopen(file_name, "r");
	for (int i = 0; i < 10; i++) {
		fscanf(fp, "%d", &len);
		printf("len: %d\n", len);
	}
	
	return;
}



void fscanf

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