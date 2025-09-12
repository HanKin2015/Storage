/*******************************************************************************
* 文 件 名: 封装.c
* 文件描述: 模拟 “封装”（数据 + 操作方法）
* 备    注: 可以用结构体（存储数据）+ 函数指针（存储方法） 模拟
* 作    者: HanKin
* 创建日期: 2025.09.12
* 修改日期：2025.09.12
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>

// 定义"类"的结构体（存储数据）
typedef struct {
    float radius;  // 数据成员
    // 函数指针（模拟成员方法）
    float (*area)(const void* self);
    void (*set_radius)(void* self, float r);
} Circle;

// 实现"成员方法"
float circle_area(const void* self) {
    const Circle* c = (const Circle*)self;
    return 3.14f * c->radius * c->radius;
}

void circle_set_radius(void* self, float r) {
    Circle* c = (Circle*)self;
    c->radius = r;
}

// 模拟"构造函数"
Circle* circle_create(float radius) {
    Circle* c = (Circle*)malloc(sizeof(Circle));
    c->radius = radius;
    // 绑定方法
    c->area = circle_area;
    c->set_radius = circle_set_radius;
    return c;
}

// 模拟"析构函数"
void circle_destroy(Circle* c) {
    free(c);
}

int main()
{
    // 创建"对象"
    Circle* c = circle_create(2.0f);
    printf("Area: %.2f\n", c->area(c));  // 调用方法（需显式传self）
    
    c->set_radius(c, 3.0f);
    printf("New area: %.2f\n", c->area(c));
    
    // 销毁"对象"
    circle_destroy(c);
    return 0;
}