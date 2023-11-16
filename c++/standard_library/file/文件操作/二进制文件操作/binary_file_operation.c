/**
* 文 件 名: binary_file_operation.c
* 文件描述: 二进制文件读写操作
* 作    者: HanKin
* 备    注: 
* 创建日期: 2023.11.15
* 修改日期：2023.11.15
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include <stdio.h>
#include <time.h>
#include <assert.h>

int main(void) 
{
    // 以时间为文件名
    time_t timer = time(NULL);  // time_t就是long int 类型
    struct tm *local = localtime(&timer);
    if (local == NULL) {
        printf("get localtime failed.\n");
        return -1;
    }
    char filename[BUFSIZ] = { 0 };
    (void)strftime(filename, BUFSIZ, "%Y-%m-%d", local);//格式化时间字符串：年-月-日
    printf("filename: %s\n", filename);
    
    FILE *fp = fopen(filename, "wb+");
    assert(fp);
    
    fprintf(fp, "hello world\n");
    
    fclose(fp);
    fp = NULL;
    return 0;
}