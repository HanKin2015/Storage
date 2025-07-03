/*******************************************************************************
* 文 件 名: read_write.cpp
* 文件描述: 探究读写文件速度效率
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.01.03
* 修改日期：2025.01.03
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// 未使用的宏定义
#define MAXN 1000

// 未使用的函数
int get_age()
{
    return 100;
}

// 未使用的类
class Animal
{
public:
    Animal() {}
    ~Animal() {}

    int get_hight()
    {
        return m_hight;
    }
    int m_hight;

protected:
    int get_type()
    {
        return m_type;
    }
    int m_type;

private:
    int get_color()
    {
        return m_color;
    }
    int m_color;
};

int main()
{
    // 未使用的变量
    std::string s = "hello world";

    // 未释放的指针1
    int *p = new int(10);

    // 未释放的指针2
    int *q = (int *)malloc(sizeof(int));

    // 释放错误的指针
    char *str = new char[100];
    delete str;

    // 未关闭的句柄1
    FILE *fp = fopen("f.txt", "r");

    // 未关闭的句柄2
    int fd = open("f.txt", O_RDONLY);
    return 0;
}