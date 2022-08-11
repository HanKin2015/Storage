/**
* 文 件 名: research_read_write_speed.cpp
* 文件描述: 探究读写文件速度效率
* 作    者: HanKin
* 参    考: https://blog.csdn.net/ZHANG_TIMI/article/details/118120684
* 创建日期: 2022.04.09
* 修改日期：2022.08.10
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
#define DATA_COUNT     10*1024*1024	// 20MB数据，加空格就会有30MB数据
#define ROW_DATA_COUNT 100
#define DATA_MAX_VALUE 0xFF
#define BUFFER_SIZE    50*1024*1024 // 缓存大小
using namespace std;

/**
* @brief  生成20MB数据，加空格文件有30MB
* @note   使用rand函数生成数字数据，100个数字换行，数字是两位数的十六进制
* @param  file_path [in] 文件路径
* @return 0成功 -1失败
*/
static int generate_data(const char *file_path)
{
    printf("---------- %s ----------\n", __FUNCTION__);
    assert(file_path);
    
    srand((unsigned)time(NULL));
    FILE *fp = fopen(file_path, "w");
    if (fp == NULL) {
        printf("err: open file[%s] failed!\n", file_path);
        return -1;
    }

    for (int i = 1; i <= DATA_COUNT; i++) {
        int data = rand() % DATA_MAX_VALUE;
        fprintf(fp, "%02x%c", data, i % ROW_DATA_COUNT ? ' ' : '\n');
    }
    fclose(fp);
    fp = NULL;
    return 0;
}

/**
* @brief  使用scanf函数读取
* @note   读取MAXN个数字，想读取完文件，但是使用这个函数没有办法
* @param  file_path [in] 文件路径
* @param  data [out] 文件内容数据
* @return 无
* @result 0.362 s
*/
static void scanf_read(const char *file_path, int *data)
{
    printf("---------- %s ----------\n", __FUNCTION__);
    assert(file_path);
    assert(data);
    
    freopen(file_path, "r", stdin);
    for (int i = 0; i < MAXN; i++) {
        scanf("%x", &data[i]);
    }
    return;
}

/**
* @brief  使用cin函数读取
* @note   默认的时候，cin与stdin总是保持同步的，也就是说这两种方法可以混用，而不必担心文件指针混乱，同时cout和stdout也一样，两者混用不会输出顺序错乱。正因为这个兼容性的特性，导致cin有许多额外的开销
* @param  file_path [in] 文件路径
* @param  data [out] 文件内容数据
* @return 无
* @result 0.848 s
*/
static void cin_read(const char *file_path, int *data)
{
    printf("---------- %s ----------\n", __FUNCTION__);
    assert(file_path);
    assert(data);
    
    freopen(file_path, "r", stdin);
    std::cin.setf(ios_base::hex,ios_base::basefield);
    for (int i = 0; i < MAXN; i++) {
        std::cin >> data[i];
    }
    return;
}

/**
* @brief  使用cin函数读取（取消同步）
* @note   无
* @param  file_path [in] 文件路径
* @param  data [out] 文件内容数据
* @return 无
* @result 0.320 s
*/
static void cin_read_nosync(const char *file_path, int *data)
{
    printf("---------- %s ----------\n", __FUNCTION__);
    assert(file_path);
    assert(data);
    
    freopen(file_path, "r", stdin);
    std::ios::sync_with_stdio(false);
    std::cin.unsetf(ios::dec);
    std::cin.setf(ios::hex);
    for (int i = 0; i < MAXN; i++) {
        std::cin >> data[i];
    }
    return;
}

/**
* @brief  使用fscanf函数读取
* @note   无
* @param  file_path [in] 文件路径
* @param  data [out] 文件内容数据
* @return 无
* @result 0.361 s
*/
void fscanf_read(const char *file_path, int *data)
{
    printf("---------- %s ----------\n", __FUNCTION__);
    assert(file_path);
    assert(data);

    size_t  len   = 0;
    FILE    *fp   = NULL;
    int     num   = 0;
    int     i     = 0;

    fp = fopen(file_path, "r");
    if (fp == NULL) {
        printf("fopen failed!\n");
        return;
    }
    for (i = 0; i < MAXN; i++) {
        fscanf(fp, "%x", &data[i]);
        //printf("num: %d\n", data[i]);
    }
    //printf("i: %d\n", i);

    fclose(fp);
    fp = NULL;
    return;
}

/**
* @brief  字符串转化为数字
* @note   无
* @param  file_path [in] 文件路径
* @param  data [out] 文件内容数据
* @return 无
*/
static void string_convert_to_number(char *buf, int *data, int len = BUFFER_SIZE)
{
    printf("---------- %s ----------\n", __FUNCTION__);
    assert(buf);
    assert(data);
    
    //printf("buf: %s\n", buf);
    
    int i = 0;
    data[0] = 0;
    for (char *p = buf; *p && p-buf < len && i < MAXN; p++) {
        if (*p == ' ' || *p == '\n') {
            //printf("i: %d, data[%d]: %02x\n", i, i, data[i]);
            data[++i] = 0;
        } else if (*p == '\n') {    // 注意创建数据时末尾要么是换行符要么是空格
            continue;
        } else {
            if (*p >= '0' && *p <='9') {
                data[i] = data[i] * 16 + *p - '0';
            } else if (*p >= 'a' && *p <='f') {
                data[i] = data[i] * 16 + *p - 'a' + 10;
            } else if (*p >= 'A' && *p <='F') {
                data[i] = data[i] * 16 + *p - 'A' + 10;
            }
        }
    }
    //printf("i: %d, data[%d]: %02x\n", i, i, data[i]);
    return;
}

/**
* @brief  把整个文件读入一个字符串最常用的方法是用fread
* @note   无
* @param  file_path [in] 文件路径
* @param  data [out] 文件内容数据
* @return 无
* @result 0.139 s
*/
static void fread_analyse(const char *file_path, int *data)
{
    printf("---------- %s ----------\n", __FUNCTION__);
    assert(file_path);
    assert(data);
    
    freopen(file_path, "rb", stdin);
    char *buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    memset(buf, 0, sizeof(char) * BUFFER_SIZE);
    int len = fread(buf, 1, sizeof(char) * BUFFER_SIZE, stdin);
    buf[len] = '\0';
    printf("len = %d\n", len);
    
    string_convert_to_number(buf, data, len);
    
    free(buf);
    buf = NULL;
    return;
}

/**
* @brief  使用read函数
* @note   无
* @param  file_path [in] 文件路径
* @param  data [out] 文件内容数据
* @return 无
* @result 0.142 s
*/
static void read_analyse(const char *file_path, int *data)
{
    printf("---------- %s ----------\n", __FUNCTION__);
    assert(file_path);
    assert(data);
    
    int fd = open(file_path, O_RDONLY);
    char *buf = (char *)malloc(sizeof(char) * BUFFER_SIZE);
    memset(buf, 0, sizeof(char) * BUFFER_SIZE);
    int len = read(fd, buf, sizeof(char) * BUFFER_SIZE);
    buf[len] = '\0';
    printf("len = %d\n", len);
    
    string_convert_to_number(buf, data, len);
    
    free(buf);
    buf = NULL;
    return;
}

/**
* @brief  把整个文件读入一个字符串最常用的方法是用fread
* @note   无
* @param  file_path [in] 文件路径
* @param  data [out] 文件内容数据
* @return 无
* @result 0.108 s
*/
static void mmap_analyse(const char *file_path, int *data)
{
    printf("---------- %s ----------\n", __FUNCTION__);
    assert(file_path);
    assert(data);
    
    int fd = open(file_path, O_RDONLY);
    int len = lseek(fd, 0, SEEK_END);
    char *mbuf = (char *) mmap(NULL, len, PROT_READ, MAP_PRIVATE, fd, 0);	
    string_convert_to_number(mbuf, data, len);
    return;
}

static void verify_data(int *data)
{
    printf("---------- %s ----------\n", __FUNCTION__);
    assert(data);
    
    for (int i = 99; i >= 89; i--) {
        printf("%02x ", data[i]);
    }
    printf("\n");
    return;
}

int main(int argc, char *argv[])
{
    const char *file_path = "./data.txt";
    int *data = (int *)malloc(sizeof(int) * MAXN);
    memset(data, 0, sizeof(int) * MAXN);

    int start = clock();
    //generate_data(file_path); // 生成数据

    //scanf_read(file_path, data);
    //cin_read(file_path, data);
    //cin_read_nosync(file_path, data);
    //fscanf_read(file_path, data);
    //fread_analyse(file_path, data);
    //read_analyse(file_path, data);
    mmap_analyse(file_path, data);
    //string_convert_to_number("1b 91 b8 92", data, 11);

    printf("本次用时: %.3lf s\n", double(clock() - start) / CLOCKS_PER_SEC);
    verify_data(data);
    return 0;
}