/** 
 * @file 	Log.c
 * @brief 	������־����
 * @author 	xxx
 * @version 1.0    
 * @date 	2022/01/18
 * @remark	ʹ��DbgPrint����־
 */
#include "Log.h"
#include <fltKernel.h>
#include <Ntstrsafe.h>

enum DrvLogConstants
{
	///��־�ı���󳤶�
	kMaxLogLength = 512
};

///��־����
#ifdef _DEBUG
static LogLevel s_logLevel = kLogTrace;
#else
static LogLevel s_logLevel = kLogInfo;
#endif // DEBUG



#ifndef _countof
#define _countof(arr) (sizeof(arr)/sizeof((arr)[0]))
#endif

/** 
 * ������־����
 * @param	level	
 * @return	
 */
void SetLogLevel(LogLevel level)
{
	s_logLevel = level;
}

/** 
 * д��־
 * @param	level	��־����
 * @param	format	�ַ�����ʽ��ͬRtlStringCchPrintfA����
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
