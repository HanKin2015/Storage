/*******************************************************************************
* 文 件 名: attribute_constructor.c
* 文件描述: GCC 特有的属性 constructor 和 destructor，用于在程序的加载和卸载时执行特定的函数
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.03.11
* 修改日期：2025.03.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>

static void __attribute__ ((constructor)) my_load(void);
static void __attribute__ ((destructor)) my_unload(void);

static void my_load(void)
{
    printf("my_load\n");
}

static void my_unload(void)
{
    printf("my_unload\n");
}

int main()
{
    printf("main\n");
    return 0;
}
/*
[root@ubuntu0006:/media/vdb/TransferStation] #gcc attribute_constructor.c
[root@ubuntu0006:/media/vdb/TransferStation] #./a.out
my_load
main
my_unload
*/