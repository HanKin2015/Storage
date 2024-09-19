/*******************************************************************************
* 文 件 名: isxdigit_example.c
* 文件描述: isxdigit函数，相关函数有isalnum，isdigit，isascii，isalpha
* 备    注: 找出字符串str中为十六进制数字的字符
* 作    者: HanKin
* 创建日期: 2024.09.14
* 修改日期：2024.09.14
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <ctype.h>
#include <stdio.h>

int main()
{
    char str[]="123c@#FDsP[e?";
    int i;
    for (i = 0; str[i] != '\0'; i++)
        if (isxdigit(str[i]))
            printf("%c is a hex adecimal digit\n", str[i]);
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
1 is a hex adecimal digit
2 is a hex adecimal digit
3 is a hex adecimal digit
c is a hex adecimal digit
F is a hex adecimal digit
D is a hex adecimal digit
e is a hex adecimal digit
*/