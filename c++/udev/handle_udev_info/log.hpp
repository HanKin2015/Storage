#ifndef LOG_HPP
#define LOG_HPP

#include "common.hpp"

enum {
	LOG_DEBUG = 0,
	LOG_INFO,
	LOG_WARN,
	LOG_ERROR,
	LOG_FATAL
};

#define MAX_BUF_LEN 4096

#ifdef _DEBUG
static unsigned int log_level = LOG_DEBUG;
#else
static unsigned int log_level = LOG_INFO;
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

void DbgPrintLine(const char *type, const char *datetime, unsigned short ms, const char* format, ...)
{
	char pre_header[MAX_BUF_LEN] = { 0 };
	snprintf(pre_header, MAX_BUF_LEN, "%s [%04d/%04d] %s [%s]",
		datetime, GetCurrentProcessId(), GetCurrentThreadId(), type, __FUNCTION__);
	
	char line[MAX_BUF_LEN + sizeof(pre_header)] = { 0 };
	char* buf = line + strlen(pre_header) + 1;
	va_list ap;
	strcpy(line, pre_header);
	line[strlen(pre_header)] = ' ';

	va_start(ap, format);
	_vsnprintf(buf, MAX_BUF_LEN*2 - 1, format, ap);
	va_end(ap);
	
    FILE *fp = fopen(".\\log\\log.txt", "a");
    if (!fp) {
        fprintf(stderr, "open log file failed, errno %s(%d)\n", strerror(errno), errno);
        return ;
    }
    fprintf(fp, "%s\n", line);
    fclose(fp);
    return ;
}

#define LOG(type, format, ...) do {                                     \
    if (type >= log_level && type <= LOG_FATAL) {                                     \
        const char *type_as_char[] = { "[DEBUG] ", "[INFO]  ", "[WARN]  ", "[ERROR] ", "[FATAL] " }; \
        struct _timeb now;                                              \
        struct tm today;                                                \
        char datetime_str[20];                                          \
        _ftime_s(&now);                                                 \
        localtime_s(&today, &now.time);                                 \
        strftime(datetime_str, 20, "%Y-%m-%d %H:%M:%S", &today);        \
        DbgPrintLine(type_as_char[type], datetime_str, now.millitm, format, ##__VA_ARGS__); \
	}																	\
} while(0)

#define vd_printf(format, ...) LOG(LOG_INFO,  format, ##__VA_ARGS__)
#define LOG_INFO(format,  ...) LOG(LOG_INFO,  format, ##__VA_ARGS__)
#define LOG_WARN(format,  ...) LOG(LOG_WARN,  format, ##__VA_ARGS__)
#define LOG_ERROR(format, ...) LOG(LOG_ERROR, format, ##__VA_ARGS__)

#endif  // LOG_HPP