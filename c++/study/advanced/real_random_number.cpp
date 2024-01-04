/*******************************************************************************
* 文 件 名: real_random_number.cpp
* 文件描述: 读取linux系统中的文件来获取随机数
* 备    注: 
* 作    者: HanKin
* 创建日期: 2024.01.04
* 修改日期：2024.01.04
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstdio>
#include <cassert>
#include <string>
#include <cstring>

#if 0
windows:
    std::wstring resultStr;
    std::wstring defalut(L"helloworld");
    BYTE lpBuffer[g_PwdLen + 1] = {0};
    WCHAR buf[g_PwdLen] = { 0 };
    HCRYPTPROV hCryptProv = NULL;
    if(CryptAcquireContext((HCRYPTPROV*)&hCryptProv,NULL,NULL,PROV_RSA_FULL,0) == FALSE) {
        LOGERRORA("[ZSZQ] CryptAcquireContext failed. code = %u.",GetLastError());
        return defalut;
    }
    if(CryptGenRandom(hCryptProv,g_PwdLen,(BYTE*)lpBuffer) == FALSE) {
        LOGERRORA("[ZSZQ] CryptGenRandom failed. code = %u.",GetLastError());
        return defalut;
    }
#endif

/*
获取系统随机数(会产生负数)
@param [in]  rand_len 随机数的长度
@param [out] output   存储随机数的buff
@return 0成功，-1失败
*/
static int platform_entropy_poll(size_t rand_len, char *output)
{
    assert(output != NULL);
    size_t ret = 0;

    FILE *fp = fopen("/dev/urandom", "rb"); // 另一个/dev/random
    if (fp == NULL) {
        perror("fopen");
        return -1;
    }

    ret = fread(output, 1, rand_len, fp);
    if(ret != rand_len) {
        perror("fread");
        fclose(fp);
        return -1;
    }
    fclose(fp);
    return 0;
}

int main()
{
    char random_number[BUFSIZ] = { 0 };
    const int random_len = 4; 
    platform_entropy_poll(random_len, random_number);
    printf("random_number: %s\n", random_number);
    for (int i = 0; i < random_len; i++) {
        int tmp = random_number[i];
        printf("%d ", tmp);
    }
    printf("\n");
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
random_number: K▒9
75 -18 -76 57
[root@ubuntu0006:~/cmake] #./a.out
random_number: 8喺
56 -27 -106 -70
*/