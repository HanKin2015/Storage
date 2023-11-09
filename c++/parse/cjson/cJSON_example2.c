/*******************************************************************************
* 文 件 名: cJSON_example2.c
* 文件描述: cJSON_PrintUnformatted和cJSON_Print区别
* 备    注: gcc在编译时添加 -lm 参数来链接数学库
            gcc cJSON_example2.c cJSON.c -lm
* 作    者: HanKin
* 创建日期: 2023.11.06
* 修改日期：2023.11.06
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON.h"

int main(int argc, char *argv[])
{
    cJSON *RootObj = cJSON_CreateObject();
    
    cJSON_AddStringToObject(RootObj, "name", "zhangsan");
    cJSON_AddStringToObject(RootObj, "age", "12");
    cJSON_AddStringToObject(RootObj, "name", "lisi");
    cJSON_AddStringToObject(RootObj, "age", "21");
    cJSON_AddStringToObject(RootObj, "name", "wangmazi");
    cJSON_AddStringToObject(RootObj, "age", "22");

    char *JsonStr1 = cJSON_PrintUnformatted(RootObj);
    char *JsonStr2 = cJSON_Print(RootObj);
    printf("cJSON_PrintUnformatted: %s\n", JsonStr1);
    printf("cJSON_Print: %s\n", JsonStr2);

    cJSON_Delete(RootObj);
    RootObj = NULL;
    return 0;
}
/*
json支持重复键值
[root@ubuntu0006:~/cmake] #gcc cJSON_example.c cJSON.c -lm
[root@ubuntu0006:~/cmake] #./a.out
cJSON_PrintUnformatted: {"name":"zhangsan","age":"12","name":"lisi","age":"21","name":"wangmazi","age":"22"}
cJSON_Print: {
        "name": "zhangsan",
        "age":  "12",
        "name": "lisi",
        "age":  "21",
        "name": "wangmazi",
        "age":  "22"
}
*/
