/**
* 文 件 名: log.cpp
* 文件描述: 日志接口(Linux版本)
* 作    者: HanKin
* 创建日期: 2021.08.23
* 修改日期：2023.06.19
*
* Copyright (c) 2021 HanKin. All rights reserved.
*/
#include "log.h"
#include <pthread.h>
#include <stdlib.h>

static pthread_mutex_t log_lock = PTHREAD_MUTEX_INITIALIZER;

void init_log(const char *log_file_path)
{
    init_done_flag = true;
    if (log_file_path == NULL) {
        printf("not init log file path, use default log file path, ./log/project.log.\n");
        if (access("./log/", F_OK) != 0) {
            char cmd[BUFSIZ] = {0};
            snprintf(cmd, sizeof(cmd), "mkdir -p %s", "./log/");
            pid_t status = system(cmd);
            if (!(status != -1 && WIFEXITED(status) && WEXITSTATUS(status) == 0)) {
                printf("[usb record] mkdir path failed, strerror[%s]", strerror(errno));
                return;
            }
            printf("create log directory success.\n");
        }
        return;
    }
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

    pthread_mutex_lock(&log_lock);
    FILE *fp = fopen(LOG_FILE_PATH, "a");
    if (!fp) {
        fprintf(stderr, "open log file<%s> failed, errno %s(%d)\n",
        LOG_FILE_PATH, strerror(errno), errno);
        return;
    }
    fprintf(fp, "%s %s [%" PRIu64 ":%" PRIu64 "] %s\n",
        ntime, type_names[type], (uint64_t)getpid(),
        (uint64_t)gettid(), logmsg);
    printf("%s %s [%" PRIu64 ":%" PRIu64 "] %s\n",
        ntime, type_names[type], (uint64_t)getpid(),
        (uint64_t)gettid(), logmsg);
    fclose(fp);
    pthread_mutex_unlock(&log_lock);
    return;
}

void printf_log(int type, const char *format, ...)
{
    if (!init_done_flag) init_log(nullptr);
    va_list args;
    va_start(args, format);
    printf_logv(type, format, args);
    va_end(args);
    return;
}