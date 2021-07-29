#pragma once

#include "common.h"

#if 0   // 消除编译警告提示
#pragma pack(show)		// 16(可以理解栈里面初始化只有一个默认值,无法再pop)
#pragma pack(push, 8)
#pragma pack(show)		// 8
#pragma pack(push)
#pragma pack(show)		// 8
#pragma pack(pop, 2)	// warning C4086: pragma 参数应为 "1"、"2"、"4"、"8" 或者 "16"
#pragma pack(show)		// 2
#pragma pack(pop)
#pragma pack(show)		// 16(默认值)
#pragma pack(pop)		// warning C4161: #pragma pack(pop...): 出栈的比入栈的多
#pragma pack(show)		// 16

#pragma pack(push, a, 1)
#pragma pack(push, b, 2)
#pragma pack(push, c, 4)
#pragma pack(push, d, 8)
#pragma pack(pop, c)	// 直接找到b这个identifier,然后弹出后就是下一个数字
#pragma pack(show)		// 2
#pragma pack(pop, e)	// 如果找不到不做任何操作,warning C4160: #pragma pack(pop,...): 未找到先前入栈的标识符“e”
#pragma pack(show)		// 2
#pragma pack()			// 这个操作会恢复默认值
#pragma pack(show)		// 16
#pragma pack(pop)		// 居然会有警告,warning C4159: #pragma pack(pop,...): 将先前入栈的标识符“b” 弹出栈
#pragma pack(show)		// 1
#pragma pack(pop)       // 恢复默认值,无push入栈

#pragma pack(show)      // 默认值16
#endif

struct TEST1
{
    char a;     // 1
    int b;      // 4+3
    double c;   // 8
};// 验证：TEST8尝试删除char结果依然是16

#pragma pack(push, 2)
struct TEST2
{
    char a;     // 1+1
    int b;      // 4
    double c;   // 8
};// 验证：TEST8尝试使用三个char结果是3
#pragma pack(pop)

struct TEST3
{
    int b;      // 4+4
    double c;   // 8
    char a;     // 1+7
};

struct TEST4
{
    double c;   // 8
    int b;      // 4
    char a;     // 1+3
};

struct TEST5
{
    char a;     // 1+3
    int b;      // 4
};

struct TEST6
{
    double c;   // 8
    int b;      // 4
    char a;     // 1+3
    char a1;
    char a2;
    char a3;
};

struct TEST7
{
    double c;   // 8
    int b;      // 4
    char a;     // 1+3
    char a1;
    char a2;
    char a3;
    char a4;    // 1+7
};

struct TEST8
{
    int b;      // 4+4
    double c;   // 8
};

#pragma pack(push, 2)
struct TEST9
{
    char a;     // 1
    char b;     // 1
    char c;     // 1
};
#pragma pack(pop)

#pragma pack(push, 2)
struct TESTa
{
    char a;     // 1+1
    int b;      // 4
};
#pragma pack(pop)

struct TESTb
{
    int b;              // 4
    static double c;    // 0
    char a;             // 1+3
};

/*
* 默认的对齐系数大于等于整个struct的对齐系数情况：（不再看默认系统眼神行事）
* 1、首先找出整个struct的对齐系数
* 2、然后再根据对齐系数来进行补位
* 规则：只要多个连续的类型拼接在一起不超过对齐系数就不换行，超过就换行，缺省就补位
* 
* 默认的对齐系数小于整个struct的对齐系数情况：（成员系数是默认对齐系数的倍数则不需要补位）
* 1、成员系数小于默认对齐系数，则补位达到默认对齐系数
* 2、成员系数大于默认对齐系数，如果是它的倍数则不需要补位，否则需要补位到它的倍数
* 
* 静态变量的存放位置与结构体实例的存储地址无关，是单独存放在静态数据区的，因此用siezof计算其大小时没有将静态成员所占的空间计算进来。
*/
int test_study_program_pack()
{
    printf("char  共占 %lld 字节\n", sizeof(char));     // 1
    printf("int   共占 %lld 字节\n", sizeof(int));      // 4
    printf("double共占 %lld 字节\n", sizeof(double));   // 8
    printf("TEST1 共占 %lld 字节\n", sizeof(TEST1));    // 16
    printf("TEST2 共占 %lld 字节\n", sizeof(TEST2));    // 14
    printf("TEST3 共占 %lld 字节\n", sizeof(TEST3));    // 24
    printf("TEST4 共占 %lld 字节\n", sizeof(TEST4));    // 16
    printf("TEST5 共占 %lld 字节\n", sizeof(TEST5));    // 8
    printf("TEST6 共占 %lld 字节\n", sizeof(TEST6));    // 16
    printf("TEST7 共占 %lld 字节\n", sizeof(TEST7));    // 24
    printf("TEST8 共占 %lld 字节\n", sizeof(TEST8));    // 16
    printf("TEST9 共占 %lld 字节\n", sizeof(TEST9));    // 3
    printf("TESTa 共占 %lld 字节\n", sizeof(TESTa));    // 6
    printf("TESTb 共占 %lld 字节\n", sizeof(TESTb));    // 8
	return 0;
}