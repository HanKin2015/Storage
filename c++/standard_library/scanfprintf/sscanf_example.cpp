/**
* 文 件 名: strdup_example.cpp
* 文件描述: 学习sscanf函数
* 备    注: sscanf通常被用来解析并转换字符串，其格式定义灵活多变，可以实现很强大的字符串解析功能
* 作    者: HanKin
* 创建日期: 2022.06.22
* 修改日期：2022.12.06
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <iostream>
#include <cstdio>
#include <stdint.h>

/*
sscanf的原型:
#include <stdio.h>
int sscanf(const char *str, const char *format, ...);

str:待解析的字符串;
format:字符串格式描述;
其后是一序列数目不定的指针参数，存储解析后的数据.
*/

static void test1()
{
    const char *str = "1234:4321";
    char vid[64] = { 0 };
    char pid[64] = { 0 };
    // 一定需要这样做，否则sscanf不清楚到哪里结束
    sscanf(str, "%[^:]:%s", vid, pid);
    printf("vid:pid[%s:%s]\n", vid, pid);
    return;
}
// vid:pid[1234:4321]

static void test2()
{
    const char *str = "1234=4321";
    char vid[64] = { 0 };
    char pid[64] = { 0 };
    sscanf(str, "%[^=]=%s", vid, pid);
    printf("%s == %s\n", vid, pid);
    return;
}
// 1234 == 4321

static void test3()
{
    const char *str = "134=54321";
    unsigned int vid = 0;
    unsigned int pid = 0;
    sscanf(str, "%04x=%04x", &vid, &pid);
    printf("%04x == %04x\n", vid, pid);
    return;
}
// 0134 == 5432

static void test4()
{
    int year, month, day;
    int converted1 = sscanf("20191103", "%04d%02d%02d", &year, &month, &day);
    printf("converted1=%d, year=%d, month=%d, day=%d\n", converted1, year, month, day);
    
    double longitude, latitude;
    int converted2 = sscanf("113.123456789 31.123456789", "%lf %lf", &longitude, &latitude);
    printf("converted2=%d, longitude=%.9lf, latitude=%lf\n", converted2, longitude, latitude);
    
    // [0-9]表示这是一个仅包含0-9这几个字符的字符串，前面使用数字31修饰词表示这个字符串缓冲区的最大长度(这也是sscanf最为人诟病的地方，
    // 很容易出现缓冲区溢出错误，实际上sscanf是可以避免出现缓冲区溢出的，只要在书写任何字符串解析的格式时，注意加上其缓冲区尺寸的限制)。
    char str1[32] = "";
    sscanf("123456abcdedf", "%31[0-9]", str1);
    printf("str1=%s\n", str1);

    char str2[32] = "";
    sscanf("123456abcdedf", "%31[0-9a-z]", str2);
    printf("str2=%s\n", str2);
    
    // 在[^]中增加表示相反的意思，上面的[a-z]表示一个不包含任何a-z之间的字符串。
    char str3[32] = "";
    sscanf("123456abcdedf", "%31[^a-z]", str3);
    printf("str3=%s\n", str3);
    
    // 加上*修饰表示一个被忽略的数据，同时也不需要为它准备空间存放解析结果。如上面的例子中，我们就只使用了str一个参数存放%31[a-z]的解析结果，而sscanf也只返回1，表示只解析了一个数据。
    // 掌握了[], ^, *如何使用后，我们会发现sscanf原来是一个如此强大的工具，很多我们原先认为必须使用正则表达式的地方，很可能使用sscanf就可以实现。
    char str4[32] = "";
    int ret = sscanf("123456abcdedf", "%*[0-9]%31[a-z]", str4);
    printf("ret=%d, str4=%s\n", ret, str4);
    return;
}
/*
converted1=3, year=2019, month=11, day=3
converted2=2, longitude=113.123456789, latitude=31.123457
str1=123456
str2=123456abcdedf
str3=123456
ret=1, str4=abcdedf
*/

int main()
{
    (void)test1();
    (void)test2();
    (void)test3();
    (void)test4();
    return 0;
}
