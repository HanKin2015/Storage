/*
 * main.cpp
 * 学习cJSON.c文件的使用
 * 
 * 1.从json文件读取成json对象
 * 2.获取json对象的key和value值
 * 3.遍历json对象
 * 4.json类型
 * 5.输出为json文件
 * 
 * date: 2021.05.25
 * author: hankin
 * 
 * Copyright (c) 2021 hankin. All rights reserved.
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include "cJSON.h"
using namespace std;

/*
 * @brief 将json文件内容解析成cjson对象
 * @param [IN]	json_file_path  json文件路径
 */
cJSON* GetJsonObject(const char* json_file_path)
{
    // 1.创建cjson对象
    cJSON* obj_json = cJSON_CreateObject();
    if (obj_json == nullptr) {
      printf("cJSON_CreateObject failed!\n");
      return nullptr;
    }
    
    // 2.打开json文件
    FILE* fp = fopen(json_file_path, "rb+");
    if(!fp) {
        printf("open json file failed!\n");
        return nullptr;
    }
    
    // 3.获取json文件内容长度
    fseek(fp, 0, SEEK_END);
    int content_len = ftell(fp);
    if(content_len == 0) {
        printf("json file no content!\n");
        return nullptr;
    }
    
    // 4.获取json文件内容到字符串中
    fseek(fp, 0, SEEK_SET);
    char* content = (char*) malloc (sizeof(char) * content_len);
    int ret = fread(content, 1, content_len, fp);
    fclose(fp);
    
    // 5.解析字符串为json对象
    obj_json = cJSON_Parse(content);
    if (obj_json == nullptr) {
        printf("cJSON_Parse failed!\n");
        return nullptr;
    }
    free(content);
    return obj_json;
}

/*
 * @brief 将cjson文件所有内容输出到一个字符串中
 * @param [IN]	json_file_path  json文件路径
 */
void GetFileContentToString(const char* json_file_path)
{
    fstream fs( "file.txt" );  // 创建个文件流对象,并打开"file.txt"
    stringstream ss;           // 创建字符串流对象
    ss << fs.rdbuf();          // 把文件流中的字符输入到字符串流中
    string str = ss.str();     // 获取流中的字符串
}

/*
 * @brief cjson文件用法示例
 * @param [IN]	pApc			APC指针
 * @param [IN]	pNormalRoutine	APC函数指针
 * @param [IN]	ppNormalContext	APC函数参数指针的指针
 * @param [IN]	ppSystemArg1	初始化
 */
void PrintJsonFile(char* fileName, char* option1, char* option2)
{
    cJSON *root,*fld;
    char *out;
    FILE* fp = fopen(fileName, "a+");
    root=cJSON_CreateArray();

    cJSON_AddItemToArray(root, fld=cJSON_CreateObject());

    cJSON_AddStringToObject(fld, "id", "c1");
    cJSON_AddStringToObject(fld, "option", option1);
    cJSON_AddStringToObject(fld, "fid", "1");

    cJSON_AddItemToArray(root, fld=cJSON_CreateObject());
    cJSON_AddStringToObject(fld, "id", "p1");
    cJSON_AddStringToObject(fld, "option", option2);
    cJSON_AddStringToObject(fld, "fid", "2");  

    out = cJSON_Print(root);
    fprintf(fp, out);   
    fclose(fp);

    cJSON_Delete(root);
    free(out);

    out = NULL;
    root = NULL;
}

string PrintCjsonType(cJSON* json_obj)
{
    switch (json_obj->type) {
    case cJSON_Number: return "cJSON_Number";
    case cJSON_String: return "cJSON_String";
    case cJSON_Array: return "cJSON_Array";
    case cJSON_Object: return "cJSON_Object";
    case cJSON_Raw: return "cJSON_Raw";
    default: return "other";
    }
}

/*
 * @brief 递归输出json对象的值
 * @param [IN]	json_file_path  json文件路径
 */
void PrintJsonValue(cJSON* json_obj)
{
    cJSON* iter1 = nullptr;  // 迭代器
    cJSON_ArrayForEach(iter1, json_obj) {
        if (iter1->type == cJSON_Array) {
            PrintJsonValue(iter1);
        } else if (iter1->type == cJSON_Object) {
            cJSON* iter2 = nullptr;
            cJSON_ArrayForEach(iter2, iter1) {
                char *key = nullptr, *value = nullptr;
                
                key = iter2->string;
                if (iter2->type == cJSON_Number) {  // 坑点,int和double如何去区分
                    printf("valueint: %d, valuedouble: %lf\n", iter2->valueint, iter2->valuedouble);
                    itoa(iter2->valueint, value, 16);
                } else if (iter2->type == cJSON_String || iter2->type == cJSON_Raw) {
                    value = iter2->valuestring;
                }

                printf("key: %s, value: %s\n", key, value);
            }
        } else {
            printf("type: %s\n", PrintCjsonType(iter1));
        }
    }
}

/*
 * @brief cjson文件用法示例
 * @param [IN]	json_file_path  json文件路径
 */
static void CjsonUsageExample(const char* json_file_path)
{
    // 1.将json文件内容解析成cjson对象
    cJSON* json_obj = GetJsonObject(json_file_path);

    // 2.打印json对象内容
    char* json_cont = cJSON_Print(json_obj);
    printf("json_cont:\n%s\n", json_cont);

    // 3.获取json对象大小
    int json_array_size = cJSON_GetArraySize(json_obj);
    printf("json_array_size: %d\n", json_array_size);

    // 4.获取子json对象，对象数组下标从0开始计算
    cJSON* sub_json_obj = cJSON_GetArrayItem(json_obj, json_array_size - 1);
    printf("sub_json_obj:\n%s\n", cJSON_Print(sub_json_obj));
    printf("json_obj valuestring: %s\n", json_obj->valuestring);
    printf("sub_json_obj valuestring: %s\n", sub_json_obj->valuestring);
    printf("sub_json_obj string: %s\n", sub_json_obj->string);
    printf("sub_json_obj type: %d, cJSON_Array is 32.\n", sub_json_obj->type);

    // 5.获取最内部的json子对象
    json_array_size = cJSON_GetArraySize(sub_json_obj);
    sub_json_obj = cJSON_GetArrayItem(sub_json_obj, json_array_size - 1);
    printf("sub_json_obj type: %d, cJSON_Object is 64.\n", sub_json_obj->type);

    // 6.
    json_array_size = cJSON_GetArraySize(sub_json_obj);
    printf("json_array_size: %d\n", json_array_size);
    cJSON* value = cJSON_GetObjectItem(sub_json_obj, "Product");
    printf("type: %d, valuestring: %s\n", value->type, value->valuestring);

    //printf("%s\n", sub_json_obj["Product"]);

    //Create_Pkgs("/sf/data/local/hj/jh.json", "12", "34");

    // 7.遍历json对象
    cJSON* pos = nullptr;
    cJSON_ArrayForEach(pos, json_obj) {
        printf("pos string: %s\n", pos->string);
    }

    // 8.输出所有的pvid值
    PrintJsonValue(json_obj);
    return ;
}

int main(int argc, char *argv[])
{
    // json文件路径
    string json_file_path = "./example.json";

    // cJSON库使用示例
    CjsonUsageExample(json_file_path.c_str());
    return 0;
}








