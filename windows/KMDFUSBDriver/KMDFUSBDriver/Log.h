/** 
 * @file 	Log.h
 * @brief 	驱动日志函数
 * @author 	xxx
 * @version 1.0    
 * @date 	2022/01/18
 * @remark	使用DbgPrint打日志
 */
#pragma once
#ifndef LOG_H_
#define LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define Trace(format,...) WriteLogA(kLogTrace,"[HEJIAN][TRACE] [%s:%s:%d] " format "\r\n", __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define Info(format,...)  WriteLogA(kLogInfo, "[HEJIAN][INFO ] [%s:%s:%d] " format "\r\n", __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define Warn(format,...)  WriteLogA(kLogWarn, "[HEJIAN][WARN ] [%s:%s:%d] " format "\r\n", __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)
#define Err(format,...)   WriteLogA(kLogError,"[HEJIAN][ERROR] [%s:%s:%d] " format "\r\n", __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__)

//打印日志的级别
typedef enum _LogLevel
{
	kLogNull = 0,	//不打印
	kLogError,		//打印错误
	kLogWarn,		//打印警告
	kLogInfo,		//打印调试信息
	kLogTrace		//打印跟踪信息
}LogLevel;

/** 
 * 设置日志级别
 * @param	level	
 * @return	
 */
void SetLogLevel(LogLevel level);

/** 
 * 写日志
 * @param	level	日志级别
 * @param	format	字符串格式，同RtlStringCchPrintfA参数
 * @return	void
 */
void WriteLogA(LogLevel level,char* format,...);

#ifdef __cplusplus
};
#endif

#endif
