
/*
 * handle_udev_info.hpp
 * 处理压缩包中收集的外设信息
 * 
 * 1.解压缩获取到每个json文件
 * 
 * date  : 2021.05.25
 * author: hejian
 * 
 * Copyright (c) 2021 hejian. All rights reserved.
 *
 */

#pragma once

#include "common.hpp"
#include "json_interface.hpp"
#include "trie.hpp"
#include "zip.h"
#include "unzip.h"
#include <tchar.h>
#include <thread>

#define MAX_BUF_LEN 256

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif

const string DATA_FILE_PATH = R"(.\data\外设信息.zip)"; // 数据压缩包
const string TEMP_DIR = R"(.\data\temp\)";	            // 临时解压缩文件夹
const string JSON_DATA_DIR = R"(.\data\json)";			// 全部json文件数据
const string CSV_FILE_PATH = R"(.\data\result.csv)";	// 保存最终数据到本地csv文件中

void UnzipFileBy7z(vector<string> files_path, string target_dir);
int GetFileRelaPath(string dir_path, vector<string>& files_path);
static int SaveData2Csv(vector<udev_info> udev_data);
int handle_udev_main();