/*
 * handle_udev_info.cpp
 * 处理压缩包中收集的外设信息
 * 
 * 1.解压缩获取到每个json文件
 * 
 * date  : 2021.05.25
 * author: hankin
 * 
 * Copyright (c) 2021 hankin. All rights reserved.
 *
 */

#include <iostream>
#include <cmath>
#include <ctime>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    const int BUF_LEN = 10;
    const int SN_CNT  = 100;

    char buf[BUF_LEN + 1];  // 特别注意需要留个结束符位置，否则输出有其他奇怪字符
    srand((unsigned)time(NULL));

    FILE *fp = fopen("./sn.txt", "w");
    if (fp == nullptr) {
        printf("err: open file failed!\n");
        return -1;
    }

    for (int i = 0; i < SN_CNT; i++) {
        memset(buf, 0, sizeof(buf));
        int x, y;
        do {
            x = rand() % BUF_LEN;
            y = rand() % BUF_LEN;
        } while (x == y);
        buf[x] = 'H';
        buf[y] = 'J';

        for (int j = 0; j < BUF_LEN; j++) {
            if (!buf[j]) {
                buf[j] = '0' + rand() % BUF_LEN;
            }
        }
        printf("%s\n", buf);
        fprintf(fp, "%s\n", buf);
    }
    fclose(fp);
    fp = nullptr;
    return 0;
}