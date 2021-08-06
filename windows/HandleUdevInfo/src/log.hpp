/*
 * log.hpp
 * 日志接口
 *
 * date  : 2021.07.01
 * author: hankin
 *
 * Copyright (c) 2021 hankin. All rights reserved.
 *
 */

#pragma once

#include "common.hpp"

static const char *LOG_FILE_PATH = ".\\log\\log.txt";

enum {
	LOG_DEBUG = 0,	// 调试
	LOG_INFO,		// 提示
	LOG_WARN,		// 警告
	LOG_ERROR,		// 错误
	LOG_FATAL		// 致命
};

#define MAX_LOGBUF_LEN 4096

#ifdef _DEBUG
static unsigned int LOG_LEVEL = LOG_DEBUG;
#else
static unsigned int LOG_LEVEL = LOG_INFO;
#endif

#ifdef  _USE_32BIT_TIME_T
#define _timeb      __timeb32
#define _ftime      _ftime32
#define _ftime_s    _ftime32_s
#else
#define _timeb      __timeb64
#define _ftime      _ftime64
#define _ftime_s    _ftime64_s
#endif

static void DbgPrintLine(const int type, const char *file_path, const char *func_name, const char* format, ...)
{
	// 1.日志级别
	const char* type_as_char[] = { "[DEBUG]", "[INFO]", "[WARN]", "[ERROR]", "[FATAL]" };
	// 2.获取当前时间
	struct _timeb now;
	struct tm today;
	char datetime_str[20];
	_ftime_s(&now);
	localtime_s(&today, &now.time);
	strftime(datetime_str, 20, "%Y-%m-%d %H:%M:%S", &today);
	// 3.去掉文件路径前缀
	const char* file_name = strrchr(file_path, '\\');
	// 4.构造日志前部分
	char pre_header[MAX_LOGBUF_LEN] = { 0 };
	snprintf(pre_header, MAX_LOGBUF_LEN, "%s [%04d/%04d] %s [%s:%s]",
		datetime_str, GetCurrentProcessId(), GetCurrentThreadId(), type_as_char[type], file_name+1, func_name);
	// 5.拼接日志内容
	char line[MAX_LOGBUF_LEN + sizeof(pre_header)] = { 0 };
	char* buf = line + strlen(pre_header) + 1;		// bu指向前部分靠后的位置
	va_list ap;
	strncpy(line, pre_header, sizeof(line) - 1);	// 将前部分内容写入line中
	line[strlen(pre_header)] = ' ';
	va_start(ap, format);
	_vsnprintf(buf, MAX_LOGBUF_LEN * 2 - 1, format, ap);	// 将后部分动态日志写入line中
	va_end(ap);
	// 6.写入日志文件
	FILE *fp = fopen(LOG_FILE_PATH, "a");
    if (!fp) {
        fprintf(stderr, "open log file<%s> failed, errno %s(%d)\n", LOG_FILE_PATH, strerror(errno), errno);
        return ;
    }
    fprintf(fp, "%s\n", line);
    fclose(fp);
    return ;
}

/*
* 属性->C/C++->高级->使用完全路径->否
* 这样无法完全解决，还是会出现相对路径src\xxx.cpp
*/
#define LOG(type, format, ...) do {											\
    if (type >= LOG_LEVEL && type <= LOG_FATAL) {							\
        DbgPrintLine(type, __FILE__, __FUNCTION__, format, ##__VA_ARGS__);	\
	}																		\
} while(0)

#define LOGD(format, ...) LOG(LOG_DEBUG, format, ##__VA_ARGS__)
#define LOGI(format, ...) LOG(LOG_INFO,  format, ##__VA_ARGS__)
#define LOGW(format, ...) LOG(LOG_WARN,  format, ##__VA_ARGS__)
#define LOGE(format, ...) LOG(LOG_ERROR, format, ##__VA_ARGS__)
