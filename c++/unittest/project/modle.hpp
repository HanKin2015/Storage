#include <stdio.h>

#define ADD_METHOD_CNT 5	// 两数求和方式数量

// 位运算
int add1(int num1, int num2);

// 普通加法
int add2(int x, int y);

// 利用减号
int add3(int x, int y);

// 自加
int add4(int x, int y);

// 利用printf返回值
int add5(int x, int y);

// typedef函数指针用法
typedef int (*p_add)(int x, int y);
int add(int x, int y, int index);
