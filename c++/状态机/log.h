/**
* 文 件 名: log.h
* 文件描述: 日志接口(Linux版本)
* 作    者: HanKin
* 创建日期: 2021.08.23
* 修改日期：2023.06.19
*
* Copyright (c) 2021 HanKin. All rights reserved.
*/
#ifndef __LOG_H__
#define __LOG_H__

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#if __GLIBC__ == 2 && __GLIBC_MINOR__ < 30
#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)
#endif

#if __cplusplus
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#endif

#define MAX_LOGBUF_LEN 4096
static char LOG_FILE_PATH[MAX_LOGBUF_LEN] = "./log/project.log";
static bool init_done_flag = false;

enum {
    LOG_DEBUG = 0,  // 调试
    LOG_INFO,       // 提示
    LOG_WARN,       // 警告
    LOG_ERROR,      // 错误
    LOG_FATAL       // 致命
};

#ifdef _DEBUG
static unsigned int LOG_LEVEL = LOG_DEBUG;
#else
static unsigned int LOG_LEVEL = LOG_INFO;
#endif

void init_log(const char *log_file_path);           // 提供给外部接口
void printf_log(int type, const char *format, ...); // 不是直接提供给外部

#define LOG(type, format, ...) do { \
    if (type >= LOG_LEVEL && type <= LOG_FATAL) {   \
        printf_log(type, "[%s:%d:%s] " format, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__);  \
    }   \
} while(0)

// 提供给外部接口
#define LOGD(format, ...) LOG(LOG_DEBUG, format, ##__VA_ARGS__)
#define LOGI(format, ...) LOG(LOG_INFO,  format, ##__VA_ARGS__)
#define LOGW(format, ...) LOG(LOG_WARN,  format, ##__VA_ARGS__)
#define LOGE(format, ...) LOG(LOG_ERROR, format, ##__VA_ARGS__)

#endif