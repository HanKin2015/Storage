/*
 * json_interface.hpp
 * json文件处理接口
 * 
 * 1.解压缩获取到每个json文件
 * 
 * date  : 2021.06.25
 * author: hankin
 * 
 * Copyright (c) 2021 hankin. All rights reserved.
 *
 */

#pragma once

#include "cJSON.h"
#include "common.hpp"

#ifdef __cplusplus
extern "C" {
#endif

// 将json文件内容解析成cjson对象
cJSON* GetJsonObject(const char* json_file_path);
//
void PrintJsonValue(cJSON* json_obj);

#ifdef __cplusplus
}
#endif

