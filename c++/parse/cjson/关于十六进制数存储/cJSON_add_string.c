/*******************************************************************************
* 文 件 名: cJSON_add_string.c
* 文件描述: cJSON添加字符串
* 作    者: HanKin
* 创建日期: 2023.11.20
* 修改日期：2023.11.20
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include <string.h>
#include <inttypes.h>

int main()
{
    // 创建 JSON 对象
    cJSON *root = cJSON_CreateObject();

    // 十六进制数
    uint16_t hexValue = 0xABCD;

     // 将十六进制数存储为字符串形式到 JSON 对象中
    char hexString[10] = { 0 };
    //snprintf(hexString, sizeof(hexString), "%04X", hexValue);     // 将十六进制数格式化为字符串
    snprintf(hexString, sizeof(hexString), "0x%04X", hexValue);     // 有没有0x前缀对转换没有影响
    cJSON_AddStringToObject(root, "hexValue", hexString);
    snprintf(hexString, sizeof(hexString), "0x%05X", hexValue);     // 这个对添加字符串无影响
    snprintf(hexString, sizeof(hexString), "0x%06X", hexValue);     // 这个对添加字符串无影响
    printf("hexString: %s\n", hexString);
    
    // 将十六进制字符串转换为长整型
    long hexValue2 = strtol(hexString, NULL, 16);
    printf("hexValue2: %ld\n", hexValue2);

    // 将 JSON 对象转换为字符串
    char *jsonString = cJSON_Print(root);

    // 输出 JSON 字符串
    printf("%s\n", jsonString);
    
    FILE *fp = fopen("s.json", "w");
    if (fp) {
        int ret = fwrite(jsonString, sizeof(char), strlen(jsonString), fp);
        if (ret < 0) {
            printf("write to file failed.\n");
        }
    } else {
        printf("m_outfile stream invalid, write file failed!\n");
        return -1;
    }

    // 释放内存
    cJSON_Delete(root);
    free(jsonString);
    return 0;
}
