/**
 * �� �� ��: json_interface.h
 * �ļ�����: json�ļ������ӿ�
 * ��    ��: HJ
 * ��������: 2021.06.25
 * �޸����ڣ�2021.06.25
 *
 * Copyright (c) 2021 HJ. All rights reserved.
 */

#pragma once

#include "cJSON.h"
#include <string.h>
#include <vector>
#include <iostream>
#include <unistd.h>
#include "log.h"
#include <sstream>
#include <fstream>

using namespace std;

#ifdef __cplusplus
extern "C" {
#endif

// json�ļ����ݽṹ��
struct udev_info {
    string vid;     // ����id
    string pid;     // ��Ʒid
    string rev;     // �汾
    string man_str; // �����ַ���������
    string pro_str; // ��Ʒ�ַ���������
};

typedef udev_info JSON_DATA_STRUCT;

cJSON* get_json_obj(const char* json_file_path);
void get_json_data(cJSON* json_obj, vector<JSON_DATA_STRUCT> &json_data);

#ifdef __cplusplus
}
#endif
