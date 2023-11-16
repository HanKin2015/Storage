/**
* 文 件 名: binary_file_operation.cpp
* 文件描述: 二进制文件读写操作(c++版本)
* 作    者: HanKin
* 备    注: 
* 创建日期: 2023.11.15
* 修改日期：2023.11.15
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

typedef struct  _NodeInfo
{
    int x;
    int y;
} NodeInfo;

int main(void) 
{
    // 以时间为文件名
    time_t timer = time(NULL);  // time_t就是long int 类型
    struct tm *local = localtime(&timer);
    if (local == NULL) {
        printf("get localtime failed.\n");
        return -1;
    }
    char filename[BUFSIZ] = { 0 };
    (void)strftime(filename, BUFSIZ, "%Y-%m-%d", local);//格式化时间字符串：年-月-日
    printf("filename: %s\n", filename);
    
    std::ofstream os;
    (void)os.open(filename, std::ofstream::out | std::ofstream::binary | std::ofstream::trunc);
    if (!os.is_open()) {
        printf("open file %s failed.\n", filename);
        return -1;
    }

    const char content[] = "hello world\n";
    os.write(content, strlen(content));
    NodeInfo node;
    node.x = 100;
    node.y = 1234;
    (void)os.write((char*)&node, sizeof(NodeInfo));
    (void)os.close();
    
    std::ifstream is(filename, ios::in | ios::binary | ios::ate);
    if (!is.is_open()) {
        printf("open file %s failed.\n", filename);
        return -1;
    }
    size_t file_size = is.tellg();
    is.seekg(0, ios::beg);
    char *buffer = new(std::nothrow)char[file_size]();
    assert(buffer);
    (void)is.read(buffer, file_size);
    (void)is.close();
    NodeInfo *ret = (NodeInfo *)(buffer + strlen(content));
    printf("ret->x: %d, ret->y: %d\n", ret->x, ret->y);
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
filename: 2023-11-15
ret->x: 100, ret->y: 1234
[root@ubuntu0006:~/cmake] #cat 2023-11-15
hello world
d▒[root@ubuntu0006:~/cmake] #
*/