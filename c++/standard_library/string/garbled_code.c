/**
* 文 件 名: garbled_code.c
* 文件描述: 处理字符串中的乱码问题
* 作    者: HanKin
* 创建日期: 2024.07.08
* 修改日期：2024.07.08
*
* Copyright (c) 2024 HanKin. All rights reserved.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iconv.h>

void iconv_example()
{
    char *inbuf = "姹夊瓧";
    unsigned int inlen = strlen(inbuf);
    iconv_t cd = iconv_open("GBK", "UTF-8");
    char *outbuf = (char *)malloc(inlen * 4);
    bzero(outbuf, inlen * 4);
    char *in = inbuf;
    char *out = outbuf;
    size_t outlen = inlen * 4;
    iconv(cd, &in, (size_t *)&inlen, &out, &outlen);
    outlen = strlen(outbuf);
    printf("inbuf: %s\n", inbuf);   // 姹夊瓧
    printf("outbuf: %s\n", outbuf); // 汉字
    free(outbuf);
    iconv_close(cd);
    return;
}

// 0x20是空格 0x7f是删除键
void replace_invalid_chars(char* str, char replacement)
{
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        if ((unsigned char)str[i] < 0x80) {
            // 如果字符是有效的ASCII字符，则保留
            continue;
        }
        // 否则，将乱码字符替换为指定的字符
        str[i] = replacement;
    }
    return;
}

int main()
{
    char str[] = "乱码字符测试abc乱码字符测试";
    printf("origin str: %s\n", str);
    replace_invalid_chars(str, '*');
    printf("str: %s\n", str);  // 输出：乱码字符测试abc***********
    
    iconv_example();
    return 0;
}
/*
origin str: 乱码字符测试abc乱码字符测试
str: ******************abc******************
inbuf: 姹夊瓧
outbuf: 汉字
*/