/**
 * 文 件 名: handle_udev_info.h
 * 文件描述: 处理压缩包中收集的外设信息
 * 作    者: HJ
 * 创建日期: 2021.05.25
 * 修改日期：2021.05.25
 *
 * Copyright (c) 2021 HJ. All rights reserved.
 */

#pragma once

#include "json_interface.h"
#include "trie.h"
#include <thread>
#include "zlib_interface.h"

#define MAX_BUF_LEN 256

#define DATA_FILE_PATH "../data/test.zip"    // 数据压缩包
#define TEMP_DIR "../data/temp/"                 // 临时解压缩文件夹
#define JSON_DATA_DIR "../data/json/"            // 全部json文件数据
#define CSV_FILE_PATH "../data/result.csv"       // 保存最终数据到本地csv文件中

int GetFileRelaPath(string dir_path, vector<string>& files_path);
static int SaveData2Csv(vector<udev_info> udev_data);
int handle_udev_main();

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif