/** 
 * @file 	Log.h
 * @brief 	������־����
 * @author 	xxx
 * @version 1.0    
 * @date 	2022/01/18
 * @remark	ʹ��DbgPrint����־
 */
#pragma once
#ifndef LOG_H_
#define LOG_H_

#ifdef __cplusplus
extern "C" {
#endif

#define Trace(format,...) WriteLogA(kLogTrace,"[HEJIAN][TRACE] " __FUNCTION__ "," format "\r\n",__VA_ARGS__)
#define Info(format,...) WriteLogA(kLogInfo,"[HEJIAN][INFO] " __FUNCTION__ "," format "\r\n",__VA_ARGS__)
#define Warn(format,...) WriteLogA(kLogWarn,"[HEJIAN][WARN] " __FUNCTION__ "," format "\r\n",__VA_ARGS__)
#define Err(format,...) WriteLogA(kLogError,"[HEJIAN][ERROR] " __FUNCTION__ "," format "\r\n",__VA_ARGS__)

//��ӡ��־�ļ���
typedef enum _LogLevel
{
	kLogNull = 0,	//����ӡ
	kLogError,		//��ӡ����
	kLogWarn,		//��ӡ����
	kLogInfo,		//��ӡ������Ϣ
	kLogTrace		//��ӡ������Ϣ
}LogLevel;

/** 
 * ������־����
 * @param	level	
 * @return	
 */
void SetLogLevel(LogLevel level);

/** 
 * д��־
 * @param	level	��־����
 * @param	format	�ַ�����ʽ��ͬRtlStringCchPrintfA����
 * @return	void
 */
void WriteLogA(LogLevel level,char* format,...);

#ifdef __cplusplus
};
#endif

#endif
