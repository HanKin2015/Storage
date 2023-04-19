/**
* 文 件 名: judge_is_android.c
* 文件描述: 判断当前运行系统是否是安卓系统
* 备    注: 使用docker交叉编译Android版本
*           source build/env.sh
*           lunch
*           编辑Android.mk文件
*           mm
*
*           gcc judge_is_android.c -lpthread -g
* 作    者: HanKin
* 创建日期: 2023.04.19
* 修改日期：2023.04.19
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <sys/utsname.h>
#include <stdio.h>
#include <string.h>

// 使用预编译指令判断
#ifdef __ANDROID__
    // 如果是安卓系统，执行相应的代码
    #define ANDROID_PRECOMPILE 1
#else
    // 如果不是安卓系统，执行相应的代码
    #define ANDROID_PRECOMPILE 0
#endif

// 使用宏定义判断
#if defined(__ANDROID__)
    // 如果是安卓系统，执行相应的代码
    #define ANDROID_DEFINE 1
#else
    // 如果不是安卓系统，执行相应的代码
    #define ANDROID_DEFINE 0
#endif

int main()
{
    struct utsname buf;
    uname(&buf);
    printf("sysname: %s\n", buf.sysname);
    if (strstr(buf.sysname, "Android")) {
        // 如果是安卓系统，执行相应的代码
        printf("this platform is android system\n");
    } else {
        // 如果不是安卓系统，执行相应的代码
        printf("this platform is not android system\n");
    }
    printf("ANDROID_PRECOMPILE %d ANDROID_DEFINE %d\n", ANDROID_PRECOMPILE, ANDROID_DEFINE);
    return 0;
}
/*
root@android:/system/bin # ./judge_is_android
sysname: Linux
this platform is not android system
ANDROID_PRECOMPILE 1 ANDROID_DEFINE 1
root@android:/system/bin # uname -a
Linux localhost 3.0.36+ #1 SMP PREEMPT Fri Sep 2 21:01:09 CST 2022 armv7l unknown
*/