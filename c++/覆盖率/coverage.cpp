/**
* 文 件 名: coverage.cpp
* 文件描述: 覆盖率
* 备    注：g++ -fprofile-arcs -ftest-coverage -fPIC -O0 coverage.cpp -o program
* 作    者: HanKin
* 创建日期: 2023.06.12
* 修改日期：2023.06.12
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>

int main(int argc,char* argv[])
{
    if(argc > 1) {
       printf("AAAA\n");
       printf("AAAA\n");
    } else {
       printf("BBB\n");
       printf("BBB\n");
    }
    
    if(argc > 1) {
       printf("AAAA\n");
       printf("AAAA\n");
    } else {
       printf("BBB\n");
       printf("BBB\n");
    }
    return 0;
}




