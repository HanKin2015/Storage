/**
* 文 件 名: log.c
* 文件描述: 
* 作    者: HanKin
* 创建日期: 2023.07.24
* 修改日期：2023.07.24
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>
#include "log.h"

void log_printf(const char *str)
{
    printf("%s\n", str);
    return;
}