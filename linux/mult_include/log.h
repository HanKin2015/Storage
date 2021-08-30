/*
 * log.hpp
 * 日志接口(Linux版本)
 *
 * date  : 2021.08.23
 * author: hj
 *
 * Copyright (c) 2021 hj. All rights reserved.
 *
 */
#pragma once 

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
static char LOG_FILE_PATH[MAX_LOGBUF_LEN] = "./log.txt";

extern int nu6867323m;

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

static void init_log(const char *log_file_path)
{
    if (log_file_path == NULL) return;
    memset(LOG_FILE_PATH, 0, sizeof(LOG_FILE_PATH));
    strncpy(LOG_FILE_PATH, log_file_path, strlen(log_file_path));
    return;
}

static void printf_logv(int type, const char *format, va_list args)
{
    const char *type_names[] = { "[DEBUG]", "[INFO]", "[WARN]", "[ERROR]", "[FATAL]" };
    
    time_t timep = time(NULL);
	struct tm *lt = localtime(&timep);
	char ntime[MAX_LOGBUF_LEN] = {0};
	strftime(ntime, sizeof(ntime), "%Y-%m-%d %H:%M:%S", lt);

    char logmsg[MAX_LOGBUF_LEN];
    vsnprintf(logmsg, sizeof(logmsg), format, args);

    FILE *fp = fopen(LOG_FILE_PATH, "a");
    if (!fp) {
        fprintf(stderr, "open log file<%s> failed, errno %s(%d)\n",
        LOG_FILE_PATH, strerror(errno), errno);
        return;
    }
    fprintf(fp, "%s %s [%" PRIu64 ":%" PRIu64 "] %s\n",
        ntime, type_names[type], (uint64_t)getpid(),
        (uint64_t)gettid(), logmsg);
    fclose(fp);
    return;
}

static void printf_log(int type, const char *format, ...)
{
    va_list args;
    va_start (args, format);
    printf_logv(type, format, args);
    va_end (args);
    return;
}

#define LOG(type, format, ...) do { \
    if (type >= LOG_LEVEL && type <= LOG_FATAL) {   \
        printf_log(type, "[%s:%d:%s] " format, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__);  \
    }   \
} while(0)

#define LOGD(format, ...) LOG(LOG_DEBUG, format, ##__VA_ARGS__)
#define LOGI(format, ...) LOG(LOG_INFO,  format, ##__VA_ARGS__)
#define LOGW(format, ...) LOG(LOG_WARN,  format, ##__VA_ARGS__)
#define LOGE(format, ...) LOG(LOG_ERROR, format, ##__VA_ARGS__)

