/**
 * �� �� ��: json_interface.cpp
 * �ļ�����: json�ļ������ӿ�
 * ��    ��: HJ
 * ��������: 2021.06.25
 * �޸����ڣ�2021.06.25
 *
 * Copyright (c) 2021 HJ. All rights reserved.
 */

#include "json_interface.h"

/*
 * @brief  ��json�ļ����ݽ�����cjson����
 * @param  json_file_path [in] json�ļ�·��
 * @return json����
 */
cJSON* get_json_obj(const char* json_file_path)
{
    if (access(json_file_path, F_OK) != 0) {
        LOGE("json file is not exist, path error!");
        return nullptr;
    }

    cJSON* json_obj = cJSON_CreateObject();
    if (json_obj == nullptr) {
        LOGE("cJSON_CreateObject failed!");
        return nullptr;
    }

    fstream fs(json_file_path);
    stringstream ss;
    ss << fs.rdbuf();
    string content = ss.str();

    json_obj = cJSON_Parse(content.c_str());
    if (json_obj == nullptr) {
        LOGE("cJSON_Parse failed!");
        return nullptr;
    }

    char* json_cont = cJSON_Print(json_obj);
    LOGD("json_cont:\n%s.", json_cont);
    int json_array_size = cJSON_GetArraySize(json_obj);
    LOGD("json_array_size: %d.", json_array_size);
    return json_obj;
}

/*
 * @brief ���json��������,���������ͽ���ת��Ϊ�ַ�������
 * @param json_obj [in] json����
 */
static string get_type_name(cJSON* json_obj)
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
 * @param json_obj  [in]  json�ļ�·��
 * @param json_data [out] json��������
 */
void get_json_data(cJSON* json_obj, vector<JSON_DATA_STRUCT> &json_data)
{
    cJSON* iter = nullptr;
    cJSON_ArrayForEach(iter, json_obj) {
        if (iter->type == cJSON_Array) {
            get_json_data(iter, json_data);
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
            LOGW("type: %s", get_type_name(iter).c_str());
        }
    }
}

