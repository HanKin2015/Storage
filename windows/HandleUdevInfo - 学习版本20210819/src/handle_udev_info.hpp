
/*
 * handle_udev_info.hpp
 * ����ѹ�������ռ���������Ϣ
 * 
 * 1.��ѹ����ȡ��ÿ��json�ļ�
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

const string DATA_FILE_PATH = R"(.\data\������Ϣ.zip)"; // ����ѹ����
const string TEMP_DIR = R"(.\data\temp\)";	            // ��ʱ��ѹ���ļ���
const string JSON_DATA_DIR = R"(.\data\json)";			// ȫ��json�ļ�����
const string CSV_FILE_PATH = R"(.\data\result.csv)";	// �����������ݵ�����csv�ļ���

void UnzipFileBy7z(vector<string> files_path, string target_dir);
int GetFileRelaPath(string dir_path, vector<string>& files_path);
static int SaveData2Csv(vector<udev_info> udev_data);
int handle_udev_main();