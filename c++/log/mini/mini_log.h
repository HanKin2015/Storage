/*******************************************************************************
* 文 件 名: mini_log.h
* 文件描述: c语言版本日志接口
* 备    注: 不支持多线程，支持动态调整
* 作    者: HanKin
* 创建日期: 2024.01.16
* 修改日期：2024.01.16
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#ifndef __MINI_LOG_H__
#define __MINI_LOG_H__

#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <inttypes.h>

#if __GLIBC__ == 2 && __GLIBC_MINOR__ < 30
#include <sys/syscall.h>
#define gettid() syscall(SYS_gettid)
#endif

// 日志级别
enum {
    LOG_DEBUG = 0,  // 调试
    LOG_INFO,       // 提示
    LOG_WARN,       // 警告
    LOG_ERROR,      // 错误
    LOG_FATAL       // 致命
};

// 日志输出等级
static unsigned int LOG_LEVEL = LOG_INFO;

// 日志输出位置
static int PRINTF_FILE = 1;

// 日志对应名称
const char *LOG_NAMES[] = { "[DEBUG]", "[INFO]", "[WARN]", "[ERROR]", "[FATAL]" };

// 日志文件路径
static char LOG_FILE_PATH[BUFSIZ] = "/tmp/hankin.log";

// 动态调整文件路径
#define PRINTF_CONTROL  "/tmp/printf_control"   // 默认输出到文件
#define DONOT_DEL_LOG   "/tmp/donot_del_log"    // 默认每次都删除日志文件
#define DEBUG           "/tmp/debug"            // 默认不输出debug日志

static void logout(int type, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    
    // 获取当前时间
    time_t timep = time(NULL);
    struct tm *lt = localtime(&timep);
    char ntime[BUFSIZ] = { 0 };
    strftime(ntime, sizeof(ntime), "%Y-%m-%d %H:%M:%S", lt);

    // 日志内容字符串
    char logmsg[BUFSIZ] = { 0 };
    vsnprintf(logmsg, sizeof(logmsg), format, args);

    if (PRINTF_FILE) {
        FILE *fp = fopen(LOG_FILE_PATH, "a");
        if (!fp) {
            fprintf(stderr, "open log file<%s> failed, errno %s(%d)\n",
            LOG_FILE_PATH, strerror(errno), errno);
            return;
        }
        fprintf(fp, "%s %s [%lu:%lu] %s\n", ntime, LOG_NAMES[type], (uint64_t)getpid(),
                (uint64_t)gettid(), logmsg);
        fclose(fp);
        fp = NULL;
    } else {
        printf("%s %s [%lu:%lu] %s\n", ntime, LOG_NAMES[type], (uint64_t)getpid(),
                (uint64_t)gettid(), logmsg);
    }

    va_end(args);
    return;
}

#define LOG(type, format, ...) do { \
    if (type >= LOG_LEVEL && type <= LOG_FATAL) {   \
        logout(type, "[%s:%d:%s] " format, __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__);  \
    }   \
} while(0)

// 提供给外部接口
#define LOGD(format, ...) LOG(LOG_DEBUG, format, ##__VA_ARGS__)
#define LOGI(format, ...) LOG(LOG_INFO,  format, ##__VA_ARGS__)
#define LOGW(format, ...) LOG(LOG_WARN,  format, ##__VA_ARGS__)
#define LOGE(format, ...) LOG(LOG_ERROR, format, ##__VA_ARGS__)

void log_init()
{
    if (!access(PRINTF_CONTROL, F_OK)) {
        PRINTF_FILE = 0;
    }
    if (!access(DEBUG, F_OK)) {
        LOG_LEVEL = LOG_DEBUG;
    }
    return;
}

void log_deinit()
{
    if (access(DONOT_DEL_LOG, F_OK)) {
        remove(LOG_FILE_PATH);
    }
    return;
}

#endif  // __MINI_LOG_H__