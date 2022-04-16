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
#include <string.h>
#include <assert.h>
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
	uint8_t *data;
	size_t len;
	
	
	
	return;
}

int numbers[MAXN];
void scanf_read()
{
	freopen("data.txt", "r", stdin);
	for (int i = 0; i < MAXN; i++) {
		scanf("%d", &numbers[i]);
	}
}

/*
默认的时候，cin与stdin总是保持同步的，也就是说这两种方法可以混用，而不必担心文件指针混乱，同时cout和stdout也一样，两者混用不会输出顺序错乱。正因为这个兼容性的特性，导致cin有许多额外的开销
*/
void cin_read()
{
	freopen("data.txt", "r", stdin);
	for (int i = 0; i < MAXN; i++) {
		std::cin >> numbers[i];
	}
}

// 取消同步
void cin_read_nosync()
{
	freopen("data.txt", "r", stdin);
	std::ios::sync_with_stdio(false);
	for (int i = 0; i < MAXN; i++) {
		std::cin >> numbers[i];
	}
}

// 字符串转化为数组
const int MAXS = 60*1024*1024;
char buf[MAXS];
void analyse(char *buf,int len = MAXS)
{
	int i;
	numbers[i=0]=0;
	for (char *p=buf;*p && p-buf<len;p++)
		if (*p == ' ')
			numbers[++i]=0;
		else
			numbers[i] = numbers[i] * 10 + *p - '0';
}
// 把整个文件读入一个字符串最常用的方法是用fread
void fread_analyse()
{
	freopen("data.txt","rb",stdin);
	int len = fread(buf,1,MAXS,stdin);
	buf[len] = '\0';
	analyse(buf,len);
}

void read_analyse()
{
	int fd = open("data.txt",O_RDONLY);
	int len = read(fd,buf,MAXS);
	buf[len] = '\0';
	analyse(buf,len);
}

void mmap_analyse()
{
	int fd = open("data.txt",O_RDONLY);
	int len = lseek(fd,0,SEEK_END);
	char *mbuf = (char *) mmap(NULL,len,PROT_READ,MAP_PRIVATE,fd,0);	
	analyse(mbuf,len);
}

// 0.317s
void fscanf_read_file(const char *file_name, uint8_t *data)
{
	assert(file_name);
	assert(data);
	
    size_t  len   = 0;
    FILE    *fp   = NULL;
	int     num   = 0;
	int     i     = 0;

    fp = fopen(file_name, "r");
	if (fp == NULL) {
		printf("fopen failed!\n");
		return;
	}
    for (i = 0; i < DATA_COUNT; i++) {
        fscanf(fp, "%d", &data[i]);
        //printf("num: %d\n", data[i]);
    }
	printf("i: %d\n", i);
	
	fclose(fp);
	fp = NULL;
    return;
}

int main(int argc, char *argv[])
{
	const char *file_name = "./data.txt";
	
	int start = clock();
	// 生成数据
	//generate_data(file_name);
	
	//scanf_read();
	//cin_read();
	//cin_read_nosync();
	//fread_analyse();
	//read_analyse();
	mmap_analyse();
	
	printf("本次用时: %.3lf s\n", double(clock() - start) / CLOCKS_PER_SEC);
	return 0;
}