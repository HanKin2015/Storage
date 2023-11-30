/*******************************************************************************
* 文 件 名: polymorphic.c
* 文件描述: 函数指针与多态
* 备    注: 
* 作    者: HanKin
* 创建日期: 2023.11.30
* 修改日期：2023.11.30
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>

typedef struct shape
{
    void (*draw)(struct shape *);
} shape_t;

typedef struct circle
{
    shape_t shape;
    int x;
    int y;
    int r;
} circle_t;

typedef struct rectangle
{
    shape_t shape;
    int x;
    int y;
    int w;
    int h;
} rectangle_t;

void circle_draw(shape_t *shape)
{
    circle_t *circle = (circle_t *)shape;
    printf("Drawing a circle at (%d, %d) with radius %d.\n", circle->x, circle->y, circle->r);
}

void rectangle_draw(shape_t *shape)
{
    rectangle_t *rectangle = (rectangle_t *)shape;
    printf("Drawing a rectangle at (%d, %d) with width %d and height %d.\n", rectangle->x, rectangle->y, rectangle->w, rectangle->h);
}

int main()
{
    circle_t circle =
    {
        .shape = {circle_draw},
        .x = 10,
        .y = 20,
        .r = 5,
    };
    rectangle_t rectangle =
    {
        .shape = {rectangle_draw},
        .x = 30,
        .y = 40,
        .w = 15,
        .h = 20,
    };
    shape_t *shapes[] = {(shape_t *)&circle, (shape_t *)&rectangle};
    for (size_t i = 0; i < sizeof(shapes) / sizeof(shape_t *); i++)
    {
        shapes[i]->draw(shapes[i]); 
    }
    return 0;
}
/*
Drawing a circle at (10, 20) with radius 5.
Drawing a rectangle at (30, 40) with width 15 and height 20.
*/