/*
 * handle_udev_info.cpp
 * 处理压缩包中收集的外设信息
 * 
 * 1.解压缩获取到每个json文件
 * 
 * date  : 2021.05.25
 * author: hankin
 * 
 * Copyright (c) 2021 hankin. All rights reserved.
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include <io.h>
#include <ctime>
#include <cstdlib>
#include <direct.h>

using namespace std;

/*
 * 
 * 
 */
void GetJsonToData(string path)
{
    // 文件句柄
    long hFile = 0;
    // 文件信息
    struct _finddata_t fileinfo;
    string p;

    if((hFile = _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1) {
        do {
            string file_path = p.assign(path).append("\\").append(fileinfo.name);
            // 如果是目录,迭代之,如果不是,加入列表
            if ((fileinfo.attrib &  _A_SUBDIR)) {
                if(strcmp(fileinfo.name, ".") != 0  &&  strcmp(fileinfo.name, "..") != 0) {
                    GetJsonToData(file_path);
                }
            } else {
                // 获取文件后缀
                int idx = file_path.find_last_of('.');
	            string postfix = file_path.substr(idx + 1);
                if (postfix == "zip") {
                    // 解压缩到data文件夹
                    string cmd = "7zx64.exe x -y " + file_path + " -odata";
                    system(cmd.c_str());
                }
            }
        } while (_findnext(hFile, &fileinfo)  == 0);
        _findclose(hFile);
    }
    return ;
}

int main(int argc, char *argv[])
{
    string target_file_path = ".\\test.zip";
    string temp_dir = ".\\temp";

    // 1.解压缩文件到temp文件夹
    string cmd = "7zx64.exe x -y " + target_file_path + " -o" + temp_dir;
    //system(cmd.c_str());
	
    // 2.获取json文件并拷贝到data文件夹中
    clock_t start = clock(); 
    GetJsonToData(temp_dir.c_str());
    printf("[GetJsonToData Function] exec time is %lf s.\n", (double)(clock() - start) / CLOCKS_PER_SEC);

    // 3.处理json文件


    // 删除中间创建的文件和文件夹
    //system("rd /s /q temp");
    return 0;
}

