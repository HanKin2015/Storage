/*
 * json_interface.cpp
 * json�ļ�����ӿ�
 * 
 * date  : 2021.06.25
 * author: hejian
 * 
 * Copyright (c) 2021 hejian. All rights reserved.
 *
 */

#include "json_interface.hpp"

/*
 * @brief ��json�ļ����ݽ�����cjson����
 * @param [IN]	json_file_path  json�ļ�·��
 */
cJSON* GetJsonObject(const char* json_file_path)
{
    // 1.�ж��ļ��Ƿ����
    if (_access(json_file_path, F_OK) != 0) {
        LOGE("json file is not exist, path error!");
        return nullptr;
    }

    // 2.����cjson����
    cJSON* json_obj = cJSON_CreateObject();
    if (json_obj == nullptr) {
      LOGE("cJSON_CreateObject failed!");
      return nullptr;
    }
    
    // 3.��ȡjson�ļ�����
    fstream fs(json_file_path); // �������ļ�������, �����ļ�
    stringstream ss;            // �����ַ���������
    ss << fs.rdbuf();           // ���ļ����е��ַ����뵽�ַ�������
    string content = ss.str();  // ��ȡ���е��ַ�������
    
    // 4.�����ַ���Ϊjson����
    json_obj = cJSON_Parse(content.c_str());
    if (json_obj == nullptr) {
        LOGE("cJSON_Parse failed!");
        return nullptr;
    }

    // 4.��ӡjson��������
    char* json_cont = cJSON_Print(json_obj);
    LOGD("json_cont:\n%s.", json_cont);

    // 5.��ȡjson�����С
    int json_array_size = cJSON_GetArraySize(json_obj);
    LOGD("json_array_size: %d.", json_array_size);
    return json_obj;
}

/*
 * @brief ���json��������,���������ͽ���ת��Ϊ�ַ�������
 * @param [IN]	json_obj  json����
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
 * @brief �ݹ��ȡjson���������
 * @param [IN]	json_obj  json�ļ�·��
 * @param [OUT]	json_data json��������
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
            LOGW("type: %s\n", PrintCjsonObjectType(iter).c_str());
        }
    }
}

