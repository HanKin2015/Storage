/*******************************************************************************
* 文 件 名: goto_example.c
* 文件描述: error: jump to label ‘END’ [-fpermissive]
* 备    注: 中间部分不能有变量声明
* 作    者: HanKin
* 创建日期: 2025.03.11
* 修改日期：2025.03.11
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>

int main()
{
    goto END;
    int x = 10;

END:
    return 0;
}
