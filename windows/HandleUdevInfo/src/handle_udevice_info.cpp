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

#include "handle_udevice_info.hpp"

/*
 * @brief 获取json文件并拷贝到data/json文件夹中
 * @note 
 * @param path [in] 数据文件夹路径
 * @return 无
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
                size_t idx = file_path.find_last_of('.');
	            string postfix = file_path.substr(idx + 1);
                if (postfix == "zip") {
                    // 解压缩到data/json文件夹
                    string cmd = ".\\tools\\7zx64.exe x -y " + file_path + " -o" + JSON_DATA_DIR;
                    system(cmd.c_str());
                }
            }
        } while (_findnext(hFile, &fileinfo)  == 0);
        _findclose(hFile);
    }
    return ;
}

/*
 * @brief 遍历处理给个json文件
 * @note
 * @param dir_path [in] 数据文件夹路径
 * @return 无
 */
void ForeachJson(string dir_path)
{
    // 文件句柄
    long hFile = 0;
    // 文件信息
    struct _finddata_t file_info;
    string path;

    if ((hFile = _findfirst(path.assign(dir_path).append("\\*").c_str(), &file_info)) != -1) {
        do {
            string file_path = path.assign(path).append("\\").append(file_info.name);
            // 如果是目录,迭代之,如果不是,加入列表
            if ((file_info.attrib & _A_SUBDIR)) {
                LOGE("%s is dir instead of file.", file_path.c_str());
                continue;
            } else {
                printf("%s\n", file_info.name);
            }
        } while (_findnext(hFile, &file_info) == 0);
        _findclose(hFile);
    }
    return;
}

/*
 * @brief 获取json文件并拷贝到data文件夹中
 * @note 
 * @param path [in] 数据文件夹路径
 * @return 文件存在返回true，反之false
 */
static bool IsExist(string file_path)
{
    return (_access(file_path.c_str(), F_OK) != -1);
}

int main(int argc, char *argv[])
{
    // 1.利用7z程序解压缩文件到temp文件夹
    string cmd = ".\\tools\\7zx64.exe x -y " + DATA_FILE_PATH + " -o" + TEMP_DIR;
    //system(cmd.c_str());
	
    // 2.获取json文件并拷贝到data文件夹中
    clock_t start_time = clock(); 
    //GetJsonToData(TEMP_DIR.c_str());
    clock_t spend_time = clock() - start_time;
    printf("[GetJsonToData Function] exec time is %lf s.\n\n", (double)spend_time / CLOCKS_PER_SEC);
    
    // 3.删除中间创建的文件和文件夹
    cmd = "rd /s /q " + TEMP_DIR;
    //system(cmd.c_str());

    // 4.处理json文件
    cJSON* json_obj = GetJsonObject(".\\data\\json\\11.22.33.44-2021.03.11.15.01.41.json");
    vector<JSON_DATA_STRUCT> json_data;
    GetJsonData(json_obj, json_data);
    printf("json data size = %I64d\n", json_data.size());

    ForeachJson(".\\data\\json");

    LOGE("hello world!");
    LOGI("hello world!");
    LOGW("hello world!");
    return 0;
}

