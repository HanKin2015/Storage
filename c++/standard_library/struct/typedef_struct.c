/*******************************************************************************
* 文 件 名: typedef_struct.c
* 文件描述: typedef struct的优点
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.01.03
* 修改日期：2025.01.03
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdint.h>
#include <stdio.h>

// 第一种写法：匿名结构体：在这个定义中，您定义了一个匿名结构体（没有名字）可以直接使用 MyStruct 来声明该结构体类型的变量
typedef struct {
    uint8_t field1;
    uint16_t field2;
    uint8_t field3;
    uint32_t field4;
} MyStructTypedef;

// 第二种写法：命名结构体：在这个定义中，您定义了一个命名结构体 MyStruct，需要在声明变量时使用 struct 关键字
struct MyStruct {
    uint8_t field1;
    uint16_t field2;
    uint8_t field3;
    uint32_t field4;
};

int main()
{
    // 使用 typedef 定义的结构体
    MyStructTypedef myVar1;
    myVar1.field1 = 1;
    myVar1.field2 = 2;
    myVar1.field3 = 3;
    myVar1.field4 = 4;

    // 使用命名结构体
    struct MyStruct myVar2;
    myVar2.field1 = 5;
    myVar2.field2 = 6;
    myVar2.field3 = 7;
    myVar2.field4 = 8;

    // 打印结果，两种写法在语法上不同，但它们在功能上是等价的，使用 typedef 可以使代码更简洁，特别是在需要频繁使用结构体的情况下
    printf("myVar1: %u, %u, %u, %u\n", myVar1.field1, myVar1.field2, myVar1.field3, myVar1.field4);
    printf("myVar2: %u, %u, %u, %u\n", myVar2.field1, myVar2.field2, myVar2.field3, myVar2.field4);

    return 0;
}
