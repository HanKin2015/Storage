/**
* This file is part of password
*
*	log.hpp 日志打印 
*
*	History:
*		hanKin@2020-04-13: create file
*
*	Copyright (C) 2020 HanKin All rights reserved
*/

#ifndef __LOG_HPP__
#define __LOG_HPP__


#include <iostream>
#include <string>
#include <algorithm>
#include <cstdio>
#include <set>
#include <map>
#include <stdarg.h>
using namespace std;



typedef enum LogType {
	NONE = 0,
	INFO = 1,
    WARNING = 2,
    ERROR = 3,
    //DEBUG = 4,
    ALL = 5,
};

#define DEBUG INFO

#define LOG_TAG  "NONE"                //输出log所在的模块,可将此宏放到makefile中赋值

#if defined(DEBUG)			//defined而不是define
#define DEBUGLEVEL DEBUG
#else
#define DEBUGLEVEL ALL		//默认log等级，打印 LOG_ERR LOG_WARN LOG_INFO
#endif

int dprintf_info(int level, const char *module, const char *pfun, const int line, const char *fmt, ...);

#define LOGE(x...) dprintf_msg(ERROR, x)
#define LOGW(x...) dprintf_msg(WARNING, x)
#define LOGI(x...) dprintf_msg(INFO, x)
#define LOGD(x...) dprintf_msg(DEBUG, x)	

#define LOGH(fmt...) dprintf(INFO, fmt)
#define dprintf(level, fmt...)  do{\
									if(level <= DEBUGLEVEL)  \
										printf(fmt);    \
									printf("\n");	\
								}while(0)                      
								




#define dprintf_msg(level, x...) do{\
									if(level <= DEBUGLEVEL)  \
										printf("hejian\n"); \
										dprintf_info(level, LOG_TAG, __FUNCTION__, __LINE__, x);    \
									}while(0)   

										 


#endif
