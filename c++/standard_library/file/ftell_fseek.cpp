/**
* 文 件 名: ftell_fseek.cpp
* 文件描述: 学习ftell和fseek函数
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
    FILE *stream;
    stream = fopen("MYFILE.TXT", "w+");
    fprintf(stream, "This is a test");
    printf("The file pointer is at byte \
    %ld\n", ftell(stream));
    fclose(stream);
	return;
}

static void test2()
{
    FILE *fp;
    int flen;
    char *p;
    /* 以只读方式打开文件 */
    if((fp = fopen ("1.txt","r"))==NULL)
    {
    printf("\nfile open error\n");
    exit(0);
    }
    fseek(fp,0L,SEEK_END); /* 定位到文件末尾 */
    flen=ftell(fp); /* 得到文件大小 */
    p=(char *)malloc(flen+1); /* 根据文件大小动态分配内存空间 */
    if(p==NULL)
    {
    fclose(fp);
    return 0;
    }
    fseek(fp,0L,SEEK_SET); /* 定位到文件开头 */
    fread(p,flen,1,fp); /* 一次性读取全部文件内容 */
    p[flen]='\0'; /* 字符串结束标志 */
    printf("%s",p);
    fclose(fp);
    free(p);
	return;
}

static void test3()
{
    FILE *myf;
    long f1;//此处将f1设置为long 可以读取更长的文件
    myf=fopen("1.txt","rb");
    fseek(myf,0,SEEK_END);
    f1=ftell(myf);
    fclose(myf);
    printf(“%d\n”,f1);
    return;
}

int main()
{
	test1();
	test2();
    return 0;
}