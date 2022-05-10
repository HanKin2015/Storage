/**
 * �� �� ��: handle_udev_info.h
 * �ļ�����: ����ѹ�������ռ���������Ϣ
 * ��    ��: HJ
 * ��������: 2021.05.25
 * �޸����ڣ�2021.05.25
 *
 * Copyright (c) 2021 HJ. All rights reserved.
 */

#pragma once

#include "json_interface.h"
#include "trie.h"
#include <thread>
#include "zlib_interface.h"

#define MAX_BUF_LEN 256

#define DATA_FILE_PATH "../data/test.zip"    // ����ѹ����
#define TEMP_DIR "../data/temp/"                 // ��ʱ��ѹ���ļ���
#define JSON_DATA_DIR "../data/json/"            // ȫ��json�ļ�����
#define CSV_FILE_PATH "../data/result.csv"       // �����������ݵ�����csv�ļ���

int GetFileRelaPath(string dir_path, vector<string>& files_path);
static int SaveData2Csv(vector<udev_info> udev_data);
int handle_udev_main();

#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif