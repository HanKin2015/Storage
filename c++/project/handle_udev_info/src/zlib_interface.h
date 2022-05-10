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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h> 
#include <dirent.h>
#include <sys/stat.h>
#include <stdlib.h>

#ifdef _WIN32
# include <direct.h>
# include <io.h>
#else
# include <unistd.h>
# include <utime.h>
#endif

#include "unzip.h"
#include "zip.h"
#include "log.h"

#define ZIP_SUFFIX ".zip"
#include <sys/stat.h>
#include <sys/types.h>
#define READ_SIZE 256
#define MAX_FILENAME 256
#define DIR_DELIMITER '/'
#define MALLOC_MAX_LENGTH 256
#define TMP_PATH "./tmp/"

#ifdef __cplusplus
extern "C" {
#endif

int unzip_file(const char *zfile_path, const char *target_path);

#ifdef __cplusplus
}
#endif
