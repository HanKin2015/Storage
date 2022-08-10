/**
* 文 件 名: cross_platform.cpp
* 文件描述: 以判断文件是否存在和创建目录进行跨平台示例
* 作    者: HanKin
* 创建日期: 2022.08.09
* 修改日期：2022.08.09
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <io.h>
    #include<direct.h>
    #define R_OK 4 /* Test for read permission. */
    #define W_OK 2 /* Test for write permission. */
    #define X_OK 1 /* Test for execute permission. */
    #define F_OK 0 /* Test for existence. */
#else
    #include <unistd.h>
    #include <sys/stat.h>
    #include <sys/types.h>
#endif

bool is_exist(const char *file_path)
{
    /*
    io.h文件定义了_access函数，后面又类似于宏定义了access函数
    _Check_return_ _CRT_NONSTDC_DEPRECATE(_access) _CRTIMP int __cdecl access(_In_z_ const char * _Filename, _In_ int _AccessMode);
    */
    if (!access(file_path, F_OK)) {
        printf("%s file exist.\n", file_path);
        return true;
    }
    printf("%s file not exist.\n", file_path);
    return false;
}

bool mkdir_directory(const char *dir_path)
{
    #ifdef _WIN32
        /*
        和access函数一样也会存在两种定义
        _Check_return_ _CRT_NONSTDC_DEPRECATE(_mkdir) _CRTIMP int __cdecl mkdir(_In_z_ const char * _Path);
        */
        _mkdir(dir_path);
    #else
        mkdir(dir_path, 0666);
    #endif
    return true;
}

int main(int argc, char *argv[])
{
    const char *file_path1 = "D:\\Users\\User\\Desktop\\config.json";
    const char *file_path2 = "/media/python2.7-minimal_2.7.15~rc1-1_amd64.deb";
    
    #ifdef _WIN32
        is_exist(file_path1);
    #else
        is_exist(file_path2);
    #endif
    mkdir_directory("./my_test");
    return 0;
}