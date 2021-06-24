
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

#include <iostream>
#include <string>
#include <vector>
#include <io.h>
#include <ctime>
#include <cstdlib>
#include <direct.h>

using namespace std;

#define R_OK 4 /* Test for read permission. */
#define W_OK 2 /* Test for write permission. */
#define X_OK 1 /* Test for execute permission. */
#define F_OK 0 /* Test for existence. */

const string DATA_FILE_PATH = ".\\data\\test.zip";    // 数据压缩包
const string TEMP_DIR = ".\\data\\temp";             // 临时解压缩文件夹
const string JSON_DATA_DIR = ".\\data\\json";        // 全部json文件数据