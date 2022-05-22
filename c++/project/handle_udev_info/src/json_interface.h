/**
 * 文 件 名: json_interface.h
 * 文件描述: json文件解析接口
 * 作    者: HJ
 * 创建日期: 2021.06.25
 * 修改日期：2021.06.25
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

// json文件数据结构体
struct udev_info {
    string vid;     // 厂商id
    string pid;     // 产品id
    string rev;     // 版本
    string man_str; // 厂商字符串描述符
    string pro_str; // 产品字符串描述符
};

typedef udev_info JSON_DATA_STRUCT;

cJSON* get_json_obj(const char* json_file_path);
void get_json_data(cJSON* json_obj, vector<JSON_DATA_STRUCT> &json_data);

#ifdef __cplusplus
}
#endif
