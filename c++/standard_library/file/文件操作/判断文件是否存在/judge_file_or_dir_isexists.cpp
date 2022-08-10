/**
* 文 件 名: judge_file_or_dir_isexists.cpp
* 文件描述: 判断文件或者文件夹是否存在
* 作    者: HanKin
* 创建日期: 2022.08.10
* 修改日期：2022.08.10
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sys/stat.h>
#include<bits/stdc++.h>

bool file_or_dir_is_exists_by_access(std::string &path)
{
    printf("%s: ", __FUNCTION__);
    bool ret = access(path.c_str(), F_OK);
    return !ret;
}

bool file_or_dir_is_exists_by_ifstream(std::string &path)
{
    printf("%s: ", __FUNCTION__);
    std::ifstream f(path.c_str());
    return f.good();
}

bool file_or_dir_is_exists_by_fopen(std::string &path)
{
    printf("%s: ", __FUNCTION__);
    if (FILE *fp = fopen(path.c_str(), "r")) {
        fclose(fp);
        fp = NULL;
        return true;
    }
    return false;
}

bool file_or_dir_is_exists_by_stat(std::string &path)
{
    printf("%s: ", __FUNCTION__);
    struct stat buffer;   
    return (stat(path.c_str(), &buffer) == 0); 
}

void test(std::string &path)
{
    printf("--------- %s ---------\n", path.c_str());
    std::cout << std::boolalpha << file_or_dir_is_exists_by_access(path) << std::endl;
    std::cout << std::boolalpha << file_or_dir_is_exists_by_ifstream(path) << std::endl;
    std::cout << std::boolalpha << file_or_dir_is_exists_by_fopen(path) << std::endl;
    std::cout << std::boolalpha << file_or_dir_is_exists_by_stat(path) << std::endl;
    return;
}

int main(int argc, char *argv[])
{
    std::string path1 = "/media/python2.7-minimal_2.7.15~rc1-1_amd64.deb";
    std::string path2 = "/media/python2.7-minimal_2.7.15~rc1-1_amd64.de";
    std::string path3 = "/media/";
    std::string path4 = "/media";
    std::string path5 = "/hj/";
    
    test(path1);
    test(path2);
    test(path3);
    test(path4);
    test(path5);
    return 0;
}
