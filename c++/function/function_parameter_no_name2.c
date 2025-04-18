/*******************************************************************************
* 文 件 名: function_parameter_no_name2.c
* 文件描述: C中不能省略形参名字，-Wunused-parameter警告需要增加-Wall -Wextra参数编译
* 备    注: https://blog.csdn.net/a2796749/article/details/51312985
* 作    者: HanKin
* 创建日期: 2025.03.19
* 修改日期：2025.04.16
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <stdio.h>

// 声明中无论是C还是在C++，都可以省略形式参数名
void greeting_omit( const char *);
void greeting_unuse( const char *);
void greeting_nowarning( const char *);

// 无形参名
void greeting_omit(const char *)
{
    printf("hello world\n");
}

// 形参未使用
void greeting_unuse(const char *name)
{
    printf("hello Cherrie\n");
}

// 消除形参未使用警告
void greeting_nowarning(const char *name)
{
    ( void )name;
    printf("hello OwnWaterloo\n");
}

int main( void )
{
    greeting_omit("" );
    greeting_unuse("");
    greeting_nowarning("");
    return  0 ;
}
/*
[root@ubuntu0006:/media/sangfor/vdb] #gcc function_parameter_no_name2.c -Wextra
function_parameter_no_name2.c: In function ‘greeting_omit’:
function_parameter_no_name2.c:18:1: error: parameter name omitted
 void greeting_omit(const char *)
 ^
[root@ubuntu0006:/media/sangfor/vdb] #gcc function_parameter_no_name2.c -Wall -Wextra
function_parameter_no_name2.c: In function ‘greeting_omit’:
function_parameter_no_name2.c:18:1: error: parameter name omitted
 void greeting_omit(const char *)
 ^
function_parameter_no_name2.c: In function ‘greeting_unuse’:
function_parameter_no_name2.c:24:33: warning: unused parameter ‘name’ [-Wunused-parameter]
 void greeting_unuse(const char *name)
                                 ^
[root@ubuntu0006:/media/sangfor/vdb] #g++ function_parameter_no_name2.c -Wall -Wextra
function_parameter_no_name2.c:24:33: warning: unused parameter ‘name’ [-Wunused-parameter]
 void greeting_unuse(const char *name)
                                 ^
*/