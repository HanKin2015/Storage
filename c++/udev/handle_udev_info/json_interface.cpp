/*
 * json_interface.cpp
 * json文件处理接口
 * 
 * date  : 2021.06.25
 * author: hankin
 * 
 * Copyright (c) 2021 hankin. All rights reserved.
 *
 */

#include "json_interface.hpp"

/*
 * @brief 将json文件内容解析成cjson对象
 * @param [IN]	json_file_path  json文件路径
 */
cJSON* GetJsonObject(const char* json_file_path)
{
    // 1.判断文件是否存在
    if (_access(json_file_path, F_OK) != 0) {
        printf("json file is not exist, path error!\n");
        return nullptr;
    }

    // 2.创建cjson对象
    cJSON* json_obj = cJSON_CreateObject();
    if (json_obj == nullptr) {
      printf("cJSON_CreateObject failed!\n");
      return nullptr;
    }
    
    // 3.读取json文件内容
    fstream fs(json_file_path); // 创建个文件流对象, 并打开文件
    stringstream ss;            // 创建字符串流对象
    ss << fs.rdbuf();           // 把文件流中的字符输入到字符串流中
    string content = ss.str();  // 获取流中的字符串内容
    
    // 4.解析字符串为json对象
    json_obj = cJSON_Parse(content.c_str());
    if (json_obj == nullptr) {
        printf("cJSON_Parse failed!\n");
        return nullptr;
    }

#if 0
    // 4.打印json对象内容
    char* json_cont = cJSON_Print(json_obj);
    printf("json_cont:\n%s\n", json_cont);

    // 5.获取json对象大小
    int json_array_size = cJSON_GetArraySize(json_obj);
    printf("json_array_size: %d\n", json_array_size);
#endif

    return json_obj;
}

/*
 * @brief 输出json对象类型,对数型类型进行转换为字符串类型
 * @param [IN]	json_obj  json对象
 */
string PrintCjsonObjectType(cJSON* json_obj)
{
    switch (json_obj->type) {
    case cJSON_Number: return "cJSON_Number";
    case cJSON_String: return "cJSON_String";
    case cJSON_Array : return "cJSON_Array";
    case cJSON_Object: return "cJSON_Object";
    case cJSON_Raw   : return "cJSON_Raw";
    default          : return "other";
    }
}

/*
 * @brief 递归获取json对象的数据
 * @param [IN]	json_obj  json文件路径
 * @param [OUT]	json_data json对象数据
 */
void GetJsonData(cJSON* json_obj, vector<JSON_DATA_STRUCT> &json_data)
{
    cJSON* iter = nullptr;
    cJSON_ArrayForEach(iter, json_obj) {
        if (iter->type == cJSON_Array) {
            GetJsonData(iter, json_data);
        } else if (iter->type == cJSON_Object) {
            JSON_DATA_STRUCT tmp_json_data{
                .vid = cJSON_GetObjectItem(iter, "VendorID")->valuestring,
                .pid = cJSON_GetObjectItem(iter, "ProductID")->valuestring,
                .rev = cJSON_GetObjectItem(iter, "Rev")->valuestring,
                .man_str = cJSON_GetObjectItem(iter, "Manufacturer")->valuestring,
                .pro_str = cJSON_GetObjectItem(iter, "Product")->valuestring
            };
            json_data.push_back(tmp_json_data);
        } else {
            printf("type: %s\n", PrintCjsonObjectType(iter).c_str());
        }
    }
}

