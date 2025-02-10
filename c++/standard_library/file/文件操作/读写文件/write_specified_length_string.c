/*******************************************************************************
* 文 件 名: write_specified_length_string.c
* 文件描述: 写入指定长度字符串
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.02.10
* 修改日期：2025.02.10
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>

int main()
{
    // 要写入的文本数据
    const char *text = "Hello, World!";
    size_t length = 4; // 要写入的长度

    // 打开文件以写入文本数据
    FILE *file = fopen("output.txt", "a"); // 使用 "w" 打开文件
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // 使用 fprintf 写入指定长度的文本数据
    fprintf(file, "%.*s\n", (int)length, text); // %.*s 用于控制写入的长度

    // 关闭文件
    fclose(file);
    printf("Successfully wrote %zu characters to the file.\n", length);
    return 0;
}

