/*
 * json_interface.hpp
 * json文件处理接口
 * 
 * 1.解压缩获取到每个json文件
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

// 文件打开模式
#define R_OK 4 /* Test for read permission. */
#define W_OK 2 /* Test for write permission. */
#define X_OK 1 /* Test for execute permission. */
#define F_OK 0 /* Test for existence. */

// json文件数据结构体
struct udev_info {
    string vid;     // 厂商id
    string pid;     // 产品id
    string rev;     // 版本
    string man_str; // 厂商字符串描述符
    string pro_str; // 产品字符串描述符
};
typedef udev_info JSON_DATA_STRUCT;

// 将json文件内容解析成cjson对象
cJSON* GetJsonObject(const char* json_file_path);
// 递归获取json对象的数据
void GetJsonData(cJSON* json_obj, vector<JSON_DATA_STRUCT> &json_data);



#ifdef __cplusplus
}
#endif
