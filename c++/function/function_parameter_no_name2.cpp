/*******************************************************************************
* 文 件 名: function_parameter_no_name2.cpp
* 文件描述: c++函数参数没有参数名的骚操作
* 备    注: https://www.zhihu.com/question/558268446
* 作    者: HanKin
* 创建日期: 2025.03.19
* 修改日期：2025.03.19
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include < stdio.h >

void  greeting_omit( const  char *  name);
void  greeting_unuse( const  char *  name);
void  greeting_nowarning( const  char *  name);

void  greeting_omit( const  char *  ) {
    printf( " hello world\n " );
}

void  greeting_unuse( const  char *  name) {
    printf( " hello Cherrie\n " );
}

void  greeting_nowarning( const  char *  name) {
    ( void )name;
    printf( " hello OwnWaterloo\n " );
}

int  main( void ) {
    greeting_omit( "" );
    greeting_unuse( "" );
    greeting_nowarning( "" );
    ( void )getchar();
    return  0 ;
}