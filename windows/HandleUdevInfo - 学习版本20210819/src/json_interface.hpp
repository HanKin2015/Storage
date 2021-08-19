/*
 * json_interface.hpp
 * json�ļ�����ӿ�
 * 
 * 1.��ѹ����ȡ��ÿ��json�ļ�
 * 
 * date  : 2021.06.25
 * author: hejian
 * 
 * Copyright (c) 2021 hejian. All rights reserved.
 *
 */

#pragma once

#include "cJSON.h"
#include "common.hpp"

#ifdef __cplusplus
extern "C" {
#endif

// �ļ���ģʽ
#define R_OK 4 /* Test for read permission. */
#define W_OK 2 /* Test for write permission. */
#define X_OK 1 /* Test for execute permission. */
#define F_OK 0 /* Test for existence. */

// json�ļ����ݽṹ��
struct udev_info {
    string vid;     // ����id
    string pid;     // ��Ʒid
    string rev;     // �汾
    string man_str; // �����ַ���������
    string pro_str; // ��Ʒ�ַ���������
};
typedef udev_info JSON_DATA_STRUCT;

// ��json�ļ����ݽ�����cjson����
cJSON* GetJsonObject(const char* json_file_path);
// �ݹ��ȡjson���������
void GetJsonData(cJSON* json_obj, vector<JSON_DATA_STRUCT> &json_data);



#ifdef __cplusplus
}
#endif
