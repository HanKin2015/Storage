/* study_env.cpp
 *
 * 学习getenv/putenv/setenv/unsetenv函数
 *
 * 头文件：#include <stdlib.h>
 * getenv()用来取得参数name环境变量的内容
 * putenv用来改变或者增加环境变量的内容
 * setenv用来改变或者增加环境变量
 * unset删除name环境变量的定义，即使不存在也不会出错
 *
 * author: hankin
 * time  : 2021.04.15
 *
 * Copyright (c) 2021 HanKin. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>

/*
不管是系统环境变量还是用户环境变量，都会找到输出
如果同时拥有path结果会是很奇怪好像是系统，但是输出TEMP是用户
*/
static void TestFunction()
{
    if (getenv("GOPATH"))
    {
        printf("%s\n", getenv("GOPATH"));
    }
    if (getenv("OneDrive"))
    {
        printf("%s\n", getenv("OneDrive"));
    }
    if (getenv("TEMP"))
    {
        printf("%s\n", getenv("TEMP"));
    }
    return;
}

int main()
{
    char *log_level_str;
    int g_debug_level = 0;

    log_level_str = getenv("LOG_LEVEL");
    if (log_level_str) {
        printf("There is $LOG_LEVEL value\n");
        g_debug_level = atoi(log_level_str);
    }
    printf("current OS $LOG_LEVEL = %d\n", g_debug_level);

    //getenv函数
    char *user = getenv("USER");
    printf("current OS $USER = %s\n", user);
    
    //putenv函数
    putenv((char*)"USER=test");
    user = getenv("USER");
    printf("current OS $USER = %s\n", user);

    //setenv函数
    setenv("USER", "true", true);
    user = getenv("USER");
    printf("current OS $USER = %s\n", user);
    setenv("USER", "false", false);
    user = getenv("USER");
    printf("current OS $USER = %s\n", user);
 

    //unsetenv函数
    unsetenv("USER");
    user = getenv("USER");
    printf("current OS $USER = %s\n", user);
    return 0;
}

