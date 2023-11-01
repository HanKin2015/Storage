/*******************************************************************************
* 文 件 名: cJSON_example.c
* 文件描述: 系统学习cJSON库
* 备    注: gcc在编译时添加 -lm 参数来链接数学库
            gcc cJSON_example.c cJSON.c -lm
* 作    者: HanKin
* 创建日期: 2023.11.01
* 修改日期：2023.11.01
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cJSON.h"

/*
输出会有个列表包含
[{
                "id":   "c1",
                "option":       "hejian",
                "fid":  "1"
        }, {
                "id":   "p1",
                "option":       "handsome",
                "fid":  "2"
        }]
*/
int example1()
{
    FILE *fp = fopen("cJSON_example.json", "w");
    cJSON *root=cJSON_CreateArray();
    cJSON *fld;

    cJSON_AddItemToArray(root, fld=cJSON_CreateObject());

    cJSON_AddStringToObject(fld, "id", "c1");
    cJSON_AddStringToObject(fld, "option", "hejian");
    cJSON_AddStringToObject(fld, "fid", "1");

    cJSON_AddItemToArray(root, fld=cJSON_CreateObject());
    cJSON_AddStringToObject(fld, "id", "p1");
    cJSON_AddStringToObject(fld, "option", "handsome");
    cJSON_AddStringToObject(fld, "fid", "2");  

    char *out = cJSON_Print(root);
    fprintf(fp, "%s", out);   
    fclose(fp);

    cJSON_Delete(root);
    free(out);

    out = NULL;
    root = NULL;
    return 0;
}

int example2()
{
    // 1、创建json对象根节点
    cJSON *RootObj = cJSON_CreateObject();
    if (!RootObj) {
      printf("cJSON_CreateObject failed!\n");
      return -1;
    }
    
    // 2、创建json对象列表
    cJSON *DeviceListObj = cJSON_CreateArray();
    
    // 3、临时json对象
    cJSON *TempObj = cJSON_CreateObject();
    
    // 4、添加内容
    cJSON_AddNumberToObject(TempObj, "bLength", 18);
    cJSON_AddNumberToObject(TempObj, "bcdUSB", 528);
    cJSON_AddStringToObject(TempObj, "product", "DataTraveler 3.0");
    
    // 5、组合
    cJSON_AddItemToArray(DeviceListObj, TempObj);
    cJSON_AddItemToObject(RootObj, "device_list", DeviceListObj);
    
    // 6、保存到文件
    FILE *fp = fopen("cJSON_example.json", "w");
    fprintf(fp, "%s", cJSON_Print(RootObj));   
    fclose(fp);
    fp = NULL;

    cJSON_Delete(RootObj);
    RootObj = NULL;
    return 0;
}

int main(int argc, char *argv[])
{
    // 创建根节点
    cJSON *RootObj = cJSON_CreateObject();
    if (!RootObj) {
      printf("cJSON_CreateObject failed!\n");
      return -1;
    }
    
    // 创建设备列表
    cJSON *DeviceListObj = cJSON_CreateArray();
    
    for (int i = 0; i < 2; i++) {
        // 创建设备描述符对象
        cJSON *DevDescObj = cJSON_CreateObject();
        cJSON_AddNumberToObject(DevDescObj, "bLength", 18);
        cJSON_AddNumberToObject(DevDescObj, "bDescriptorType", 1);
        cJSON_AddNumberToObject(DevDescObj, "bNumConfigurations", 1);
        cJSON_AddStringToObject(DevDescObj, "product", "DataTraveler 3.0");
        cJSON_AddItemToArray(DeviceListObj, DevDescObj);
        
        // 创建配置描述符列表
        cJSON *ConfDescListObj = cJSON_CreateArray();
        cJSON *TempObj = cJSON_GetObjectItem(DevDescObj, "bNumConfigurations");
        if (TempObj->type == cJSON_NULL) {
            printf("TempObj type is cJSON_NULL\n");
            return -1;
        }
        int ConfDescCnt = TempObj->valueint;
        for (int j = 0; j < ConfDescCnt; j++) {
            // 创建配置描述符对象
            cJSON *ConfDescObj = cJSON_CreateObject();
            cJSON_AddNumberToObject(ConfDescObj, "bLength", 9);
            cJSON_AddNumberToObject(ConfDescObj, "bDescriptorType", 2);
            cJSON_AddNumberToObject(ConfDescObj, "bNumInterfaces", 1);
            cJSON_AddItemToArray(ConfDescListObj, ConfDescObj);
            
            // 创建接口描述符列表
            cJSON *InfDescListObj = cJSON_CreateArray();
            TempObj = cJSON_GetObjectItem(ConfDescObj, "bNumInterfaces");
            int InfDescCnt = TempObj->valueint;
            for (int k = 0; k < InfDescCnt; k++) {
                // 创建配置描述符对象
                cJSON *InfDescObj = cJSON_CreateObject();
                cJSON_AddNumberToObject(InfDescObj, "bLength", 9);
                cJSON_AddNumberToObject(InfDescObj, "bDescriptorType", 4);
                cJSON_AddNumberToObject(InfDescObj, "bNumEndpoints", 2);
                cJSON_AddItemToArray(InfDescListObj, InfDescObj);
                
                // 创建端点描述符列表
                cJSON *EpDescListObj = cJSON_CreateArray();
                TempObj = cJSON_GetObjectItem(InfDescObj, "bNumEndpoints");
                int EpDescCnt = TempObj->valueint;
                for (int l = 0; l < EpDescCnt; l++) {
                    // 创建端点描述符对象
                    cJSON *EpDescObj = cJSON_CreateObject();
                    cJSON_AddNumberToObject(EpDescObj, "bLength", 7);
                    cJSON_AddNumberToObject(EpDescObj, "bDescriptorType", 5);
                    cJSON_AddNumberToObject(EpDescObj, "bEndpointAddress", 129);
                    cJSON_AddItemToArray(EpDescListObj, EpDescObj);
                }
                cJSON_AddItemToArray(InfDescListObj, EpDescListObj);
            }
            cJSON_AddItemToArray(ConfDescListObj, InfDescListObj);
        }
        cJSON_AddItemToArray(DeviceListObj, ConfDescListObj);
    }
    cJSON_AddItemToObject(RootObj, "device_list", DeviceListObj);
    
    // 6、保存到文件
    FILE *fp = fopen("cJSON_example.json", "w");
    fprintf(fp, "%s", cJSON_Print(RootObj));   
    fclose(fp);
    fp = NULL;

    cJSON_Delete(RootObj);
    RootObj = NULL;
    return 0;
}
