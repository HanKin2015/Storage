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


#include <stdio.h>
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

void test5()
{
    //char hcid_path[BUFSIZ] = { 0 };
    //char *hcid_path = "IUSB3\\DevClass_01&SubClass_02&Prot_03";
    const char *hcid_path = "USB\\Class_07&SubClass_01&Prot_02";
    printf("%s\n", hcid_path);
    const int param_nums = 3;
    int cls = 0;
    int sub_cls = 0;
    int proto = 0;
    int ret1 = sscanf(hcid_path, "IUSB3\\DevClass_%02x&SubClass_%02x&Prot_%02x", &cls, &sub_cls, &proto);
    printf("ret = %d, cls %d, sub_cls %d proto %d\n", ret1, cls, sub_cls, proto);
    int ret2 = sscanf(hcid_path, "USB\\Class_%02x&SubClass_%02x&Prot_%02x", &cls, &sub_cls, &proto);
    printf("ret = %d, cls %d, sub_cls %d proto %d\n", ret2, cls, sub_cls, proto);

    if ((sscanf(hcid_path, "USB\\Class_%02x&SubClass_%02x&Prot_%02x",
        &cls, &sub_cls, &proto) != param_nums) && (sscanf(hcid_path, "IUSB3\\DevClass_%02x&SubClass_%02x&Prot_%02x",
        &cls, &sub_cls, &proto) != param_nums)) {
            printf("Cannot parse compatible id %s, maybe it have interfaces or have no driver", hcid_path);
            return;
    }
    return;
}

// sscanf返回值验证
void test6()
{
    printf("--- %s ---\n", __FUNCTION__);
    uint32_t mac_addr[6] = { 0 };
    
    // 缺失片段
    const char *mac_address1 = "FE:FC:FE:C0:0D";
    int ret1 = sscanf(mac_address1, "%2x:%2x:%2x:%2x:%2x:%2x", &mac_addr[0], &mac_addr[1], &mac_addr[2], &mac_addr[3], &mac_addr[4], &mac_addr[5]);
    printf("ret1 = %d\n", ret1);    // 5
    
    // 非十六进制1
    const char *mac_address2 = "FE:FC:FE:C0:0D:TB";
    int ret2 = sscanf(mac_address2, "%2x:%2x:%2x:%2x:%2x:%2x", &mac_addr[0], &mac_addr[1], &mac_addr[2], &mac_addr[3], &mac_addr[4], &mac_addr[5]);
    printf("ret2 = %d\n", ret2);    // 5
    
    // 非十六进制2，遇到异常就结束了
    const char *mac_address3 = "FE:FC:TE:C0:0D:AB";
    int ret3 = sscanf(mac_address3, "%2x:%2x:%2x:%2x:%2x:%2x", &mac_addr[0], &mac_addr[1], &mac_addr[2], &mac_addr[3], &mac_addr[4], &mac_addr[5]);
    printf("ret3 = %d\n", ret3);    // 2
    return;
}

// char*类型转int类型
void test7()
{
    const char* str = "123";
    int n = 2;
    
    // 将str转换为%d格式存储到n
    sscanf(str, "%d", &n);
    printf("n = %d\n", n);
    return;
}

int main()
{
    (void)test1();
    (void)test2();
    (void)test3();
    (void)test4();
    (void)test6();
    return 0;
}
