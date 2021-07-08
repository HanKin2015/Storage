
/*
 * handle_udev_info.hpp
 * 处理压缩包中收集的外设信息
 * 
 * 1.解压缩获取到每个json文件
 * 
 * date  : 2021.05.25
 * author: hankin
 * 
 * Copyright (c) 2021 hankin. All rights reserved.
 *
 */

#pragma once

#include "common.hpp"
#include "json_interface.hpp"
#include "log.hpp"

#ifdef __cplusplus
extern "C" {
#endif

const string DATA_FILE_PATH = ".\\data\\test.zip";  // 数据压缩包
const string TEMP_DIR = ".\\data\\temp";            // 临时解压缩文件夹
const string JSON_DATA_DIR = ".\\data\\json";       // 全部json文件数据

// 获取json文件并拷贝到data/json文件夹中
void GetJsonToData(string path);

#ifdef __cplusplus
}
#endif
