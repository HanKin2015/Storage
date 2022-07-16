/**
* 文 件 名: struct_null.c
* 文件描述: 看错了，并不是结构体可以判空，是地址，主要演示结构体指针赋值
* 作    者: HanKin
* 创建日期: 2022.07.12
* 修改日期：2022.07.12
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>

typedef struct _NODE {
    char *ch;
    int index;
} NODE, *PNODE;

// 只有指针判空，或者是变量地址，对于变量地址判空，本身就是一种画蛇添足的做法
static void test1()
{
    //NODE tmp;
    PNODE tmp;
    if (tmp == NULL) {
        printf("tmp is NULL\n");
    } else {
        printf("tmp is not NULL\n");
        printf("index = %d\n", tmp->index);
    }
    return;
}

typedef struct _PLANE {
    NODE cs;
    int index;
} PLANE, *PPLANE;

static void test2()
{
    printf("%lu, %lu\n", sizeof(PLANE), sizeof(PPLANE));
    PPLANE dev = (PPLANE)malloc(sizeof(PLANE));
    assert(dev);
    
    if (&dev->cs == NULL) {
        printf("cs is NULL\n");
    } else {
        printf("cs is not NULL\n");
    }
    return;
}


// 结构体指针不需要分配内存？？？
static void test3()
{
    NODE *ptr;
    if (ptr == NULL) {
        printf("ptr is NULL\n");
    } else {
        printf("ptr is not NULL\n");
        printf("index = %d\n", ptr->index);
    }
    
    /*
    这段注释的代码要与不要的区别
    [root@ubuntu0006:/media/hankin/vdb/study/log4cplus] #./a.out
    ptr is NULL
    p is NULL
    [root@ubuntu0006:/media/hankin/vdb/study/log4cplus] #gcc struct_null.c
    [root@ubuntu0006:/media/hankin/vdb/study/log4cplus] #./a.out
    ptr is not NULL
    index = 1280590165
    p is not NULL
    p address = 0x400510
    段错误
    */
    //int *q = (int *)malloc(sizeof(int));
    //assert(q);
    //*q = 2022;
    
    // 论初始化赋值的重要性
    int *p;
    if (ptr == NULL) {
        printf("p is NULL\n");
    } else {
        printf("p is not NULL\n");
        printf("p address = %p\n", p);
        *p = 2022;
    }
    return;
}

// 分配空间只能一层一层的分配，因为每个元素可能需要的空间不同
static void test4()
{
    PNODE p, q;
    printf("%lu, %lu\n", sizeof(NODE), sizeof(PNODE));
    p = (PNODE)malloc(sizeof(NODE));
    assert(p);
    if (p->ch == NULL) {
        printf("p->ch is NULL\n");
    } else {
        printf("p->ch is not NULL\n");
    }
    if (q->ch == NULL) {
        printf("q->ch is NULL\n");
    } else {
        printf("q->ch is not NULL\n");
    }
    
    *(p->ch) = 'a';
    *(q->ch) = 'b';
    return;
}

// 非指针变量不管赋值与否，地址都会存在，每次运行结果不一样
static void test5()
{
    int p;
    printf("p address: %p\n", &p);
    return;
}

int main(int argc, char *argv[])
{
    test5();
    return 0;
}