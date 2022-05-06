#pragma once

#include "resource.h"
#include <stdio.h>
#include <windowsx.h>
#include <io.h>
#include <time.h>
#include <sys\timeb.h>

typedef unsigned int         uint32_t;

#define IS_USE_OUTPUT_DEBUG_PRINT   1

#if  IS_USE_OUTPUT_DEBUG_PRINT 

#define  OUTPUT_DEBUG_PRINTF(str, ...)  OutputDebugPrintf(str, ##__VA_ARGS__)
void OutputDebugPrintf(const char * strOutputString, ...)
{
#define PUT_PUT_DEBUG_BUF_LEN   4096
	char strBuffer[PUT_PUT_DEBUG_BUF_LEN] = { 0 };
	va_list vlArgs;
	va_start(vlArgs, strOutputString);
	_vsnprintf_s(strBuffer, sizeof(strBuffer) - 1, strOutputString, vlArgs);  //_vsnprintf_s  _vsnprintf
	//vsprintf(strBuffer,strOutputString,vlArgs);
	va_end(vlArgs);

	// ����ĺ���������������debugview����
	OutputDebugStringA(strBuffer);  //OutputDebugString    // OutputDebugStringW
}
#else 
#define  OUTPUT_DEBUG_PRINTF(str) 
#endif

#define TRACE_HEADER "[keyboard]"
void DbgPrint(const char* format, ...)
{
	char line[4096 + sizeof(TRACE_HEADER)] = { 0 };
	char* buf = line + sizeof(TRACE_HEADER);	// bufָ��line��λ�ü���sizeof(TRACE_HEADER)���ȵĵ�ַ
	// ��ˣ�buf�����ս�����ַ�����line�Ƕ���ӵ��ַ�ͷ�ٽ������ս���ַ���ֱ��������
	va_list ap;
	strcpy(line, TRACE_HEADER);
	line[sizeof(TRACE_HEADER) - 1] = ' ';
	va_start(ap, format);
	_vsnprintf(buf, 4095, format, ap);
	va_end(ap);
	OutputDebugStringA(line);
}

#ifdef  _USE_32BIT_TIME_T

#define _timeb      __timeb32
#define _ftime      _ftime32
#define _ftime_s    _ftime32_s

#else

#define _timeb      __timeb64
#define _ftime      _ftime64
#define _ftime_s    _ftime64_s

#endif
enum {
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARN,
	LOG_ERROR,
	LOG_FATAL
};

#ifdef _DEBUG
static unsigned int log_level = LOG_DEBUG;
#else
static unsigned int log_level = LOG_INFO;
#endif

#define PRINT_LINE(type, format, datetime, ms, ...)               \
    printf("%s [%04d/%04d] %s [%s] " format "\n", \
		datetime, \
		GetCurrentProcessId(), \
		GetCurrentThreadId(),  \
		type, \
		__FUNCTION__, \
		##__VA_ARGS__)

// format������������...��һ�𣬷�����ܻ�������ݴ���
void DbgPrintLine(const char *type, const char *datetime, unsigned short ms, const char* format, ...)
{
#define MAX_BUF_LEN 4096
	char pre_header[MAX_BUF_LEN] = { 0 };
	snprintf(pre_header, MAX_BUF_LEN, "%s [%04d/%04d] %s [%s]",
		datetime, GetCurrentProcessId(), GetCurrentThreadId(), type, __FUNCTION__);
	
	char line[MAX_BUF_LEN + sizeof(pre_header)] = { 0 };
	char* buf = line + strlen(pre_header) + 1;	// ���������ԭ��ָ���λ����4096(sizeof(pre_header))�ĵط���
	va_list ap;
	strcpy(line, pre_header);
	/*
	�����ԭ��
	sizeof(pre_header)		4096
	sizeof(TRACE_HEADER)	11
	strlen(pre_header)		ʵ�ʳ���
	*/
	line[strlen(pre_header)] = ' ';	// �ӿո�

	va_start(ap, format);
	_vsnprintf(buf, MAX_BUF_LEN*2 - 1, format, ap);
	va_end(ap);
	OutputDebugStringA(line);
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
