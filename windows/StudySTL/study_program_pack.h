#pragma once

#include "common.h"

#if 0   // �������뾯����ʾ
#pragma pack(show)		// 16(�������ջ�����ʼ��ֻ��һ��Ĭ��ֵ,�޷���pop)
#pragma pack(push, 8)
#pragma pack(show)		// 8
#pragma pack(push)
#pragma pack(show)		// 8
#pragma pack(pop, 2)	// warning C4086: pragma ����ӦΪ "1"��"2"��"4"��"8" ���� "16"
#pragma pack(show)		// 2
#pragma pack(pop)
#pragma pack(show)		// 16(Ĭ��ֵ)
#pragma pack(pop)		// warning C4161: #pragma pack(pop...): ��ջ�ı���ջ�Ķ�
#pragma pack(show)		// 16

#pragma pack(push, a, 1)
#pragma pack(push, b, 2)
#pragma pack(push, c, 4)
#pragma pack(push, d, 8)
#pragma pack(pop, c)	// ֱ���ҵ�b���identifier,Ȼ�󵯳��������һ������
#pragma pack(show)		// 2
#pragma pack(pop, e)	// ����Ҳ��������κβ���,warning C4160: #pragma pack(pop,...): δ�ҵ���ǰ��ջ�ı�ʶ����e��
#pragma pack(show)		// 2
#pragma pack()			// ���������ָ�Ĭ��ֵ
#pragma pack(show)		// 16
#pragma pack(pop)		// ��Ȼ���о���,warning C4159: #pragma pack(pop,...): ����ǰ��ջ�ı�ʶ����b�� ����ջ
#pragma pack(show)		// 1
#pragma pack(pop)       // �ָ�Ĭ��ֵ,��push��ջ

#pragma pack(show)      // Ĭ��ֵ16
#endif

struct TEST1
{
    char a;     // 1
    int b;      // 4+3
    double c;   // 8
};// ��֤��TEST8����ɾ��char�����Ȼ��16

#pragma pack(push, 2)
struct TEST2
{
    char a;     // 1+1
    int b;      // 4
    double c;   // 8
};// ��֤��TEST8����ʹ������char�����3
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
* Ĭ�ϵĶ���ϵ�����ڵ�������struct�Ķ���ϵ������������ٿ�Ĭ��ϵͳ�������£�
* 1�������ҳ�����struct�Ķ���ϵ��
* 2��Ȼ���ٸ��ݶ���ϵ�������в�λ
* ����ֻҪ�������������ƴ����һ�𲻳�������ϵ���Ͳ����У������ͻ��У�ȱʡ�Ͳ�λ
* 
* Ĭ�ϵĶ���ϵ��С������struct�Ķ���ϵ�����������Աϵ����Ĭ�϶���ϵ���ı�������Ҫ��λ��
* 1����Աϵ��С��Ĭ�϶���ϵ������λ�ﵽĬ�϶���ϵ��
* 2����Աϵ������Ĭ�϶���ϵ������������ı�������Ҫ��λ��������Ҫ��λ�����ı���
* 
* ��̬�����Ĵ��λ����ṹ��ʵ���Ĵ洢��ַ�޹أ��ǵ�������ھ�̬�������ģ������siezof�������Сʱû�н���̬��Ա��ռ�Ŀռ���������
*/
int test_study_program_pack()
{
    printf("char  ��ռ %lld �ֽ�\n", sizeof(char));     // 1
    printf("int   ��ռ %lld �ֽ�\n", sizeof(int));      // 4
    printf("double��ռ %lld �ֽ�\n", sizeof(double));   // 8
    printf("TEST1 ��ռ %lld �ֽ�\n", sizeof(TEST1));    // 16
    printf("TEST2 ��ռ %lld �ֽ�\n", sizeof(TEST2));    // 14
    printf("TEST3 ��ռ %lld �ֽ�\n", sizeof(TEST3));    // 24
    printf("TEST4 ��ռ %lld �ֽ�\n", sizeof(TEST4));    // 16
    printf("TEST5 ��ռ %lld �ֽ�\n", sizeof(TEST5));    // 8
    printf("TEST6 ��ռ %lld �ֽ�\n", sizeof(TEST6));    // 16
    printf("TEST7 ��ռ %lld �ֽ�\n", sizeof(TEST7));    // 24
    printf("TEST8 ��ռ %lld �ֽ�\n", sizeof(TEST8));    // 16
    printf("TEST9 ��ռ %lld �ֽ�\n", sizeof(TEST9));    // 3
    printf("TESTa ��ռ %lld �ֽ�\n", sizeof(TESTa));    // 6
    printf("TESTb ��ռ %lld �ֽ�\n", sizeof(TESTb));    // 8
	return 0;
}