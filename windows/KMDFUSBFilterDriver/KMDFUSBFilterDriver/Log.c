/** 
 * @file 	Log.c
 * @brief 	驱动日志函数
 * @author 	xxx
 * @version 1.0    
 * @date 	2022/01/18
 * @remark	使用DbgPrint打日志
 */
#include "Log.h"
#include <fltKernel.h>
#include <Ntstrsafe.h>

enum DrvLogConstants
{
	///日志文本最大长度
	kMaxLogLength = 512
};

///日志级别
#ifdef _DEBUG
static LogLevel s_logLevel = kLogTrace;
#else
static LogLevel s_logLevel = kLogInfo;
#endif // DEBUG



#ifndef _countof
#define _countof(arr) (sizeof(arr)/sizeof((arr)[0]))
#endif

/** 
 * 设置日志级别
 * @param	level	
 * @return	
 */
void SetLogLevel(LogLevel level)
{
	s_logLevel = level;
}

/** 
 * 写日志
 * @param	level	日志级别
 * @param	format	字符串格式，同RtlStringCchPrintfA参数
 * @return	void
 */
void WriteLogA(LogLevel level, char* format,...)
{
	CHAR szLog[kMaxLogLength];
	va_list args = NULL;

	if(level > s_logLevel)
	{
		return;
	}
	
	va_start(args, format);
	RtlStringCchVPrintfA(szLog,
		_countof(szLog),
		format,
		args);
	va_end(args);
	szLog[kMaxLogLength - 1] = '\0';

	DbgPrint("%s",szLog);
}
