/**
* 文 件 名: log.h
* 文件描述: 
* 作    者: HanKin
* 创建日期: 2023.07.24
* 修改日期：2023.07.24
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#ifndef LOG_H_
#define LOG_H_

#define LOGE(str) log_printf(str)
void log_printf(const char *str);

#endif