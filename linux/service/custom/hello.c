/**
* 文 件 名: hello.c
* 文件描述: gcc -o /home/hello hello.c
* 作    者: HanKin
* 创建日期: 2022.07.06
* 修改日期：2022.07.06
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
int main(int argc, char **argv)
{
    while (1) {
        printf("hello world\n");
        sleep (2); //2s
    }
    return 0;
}