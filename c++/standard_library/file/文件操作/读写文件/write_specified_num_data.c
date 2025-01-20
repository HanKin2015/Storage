/*******************************************************************************
* 文 件 名: write_specified_num_data.c
* 文件描述: 写入指定数量数据
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.01.07
* 修改日期：2025.01.07
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>

int main()
{
    // 要写入的整数数组
    int numbers[] = {1, 2, 3, 4, 5};
    size_t count = sizeof(numbers) / sizeof(numbers[0]); // 数组元素数量

    // 打开文件以写入二进制数据
    FILE *fp = fopen("o.txt", "w");
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    // 使用 fwrite 写入数据
    size_t written = fwrite(numbers, sizeof(int), count, fp);
    written = fwrite(numbers, sizeof(int), count, fp);
    if (written != count) {
        perror("Error writing to file");
    } else {
        printf("Successfully wrote %zu elements to the file.\n", written);
    }

    // 关闭文件
    fclose(fp);
    return 0;
}
