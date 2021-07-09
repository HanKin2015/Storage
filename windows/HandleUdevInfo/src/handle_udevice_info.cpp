/*
 * handle_udev_info.cpp
 * 处理压缩包中收集的外设信息
 * 
 * 1.解压缩获取到每个json文件
 * 
 * date  : 2021.05.25
 * author: hejian
 * 
 * Copyright (c) 2021 hejian. All rights reserved.
 *
 */

#include "handle_udevice_info.hpp"
#include "trie.hpp"

 /*
  * @brief 判断文件或者目录是否存在
  * @note
  * @param path [in] 文件或者目录路径
  * @return 存在返回true，反之false
  */
static bool IsExist(string path)
{
    return (_access(path.c_str(), F_OK) != -1);
}

/*
 * @brief 获取json文件并拷贝到data/json文件夹中
 * @note 
 * @param path [in] 数据文件夹路径
 * @return 无
 */
void UnzipFile(vector<string> files_path, string target_dir)
{
    for (string file_path : files_path) {
        // 获取文件后缀
        size_t idx = file_path.find_last_of('.');
        string postfix = file_path.substr(idx + 1);
        if (postfix == "zip") {
            // 解zip压缩文件到目标文件夹
            string cmd = ".\\tools\\7zx64.exe x -y " + file_path + " -o" + target_dir;
            system(cmd.c_str());
        }
    }
    return ;
}

/*
 * @brief 获取文件夹下所有文件的相对路径
 * @note
 * @param dir_path [in] 数据文件夹路径
 * @return 无
 */
void GetFileRelaPath(string dir_path, vector<string> &files_path)
{
    // 文件句柄
    intptr_t hFile = 0;
    // 文件信息
    struct _finddata_t file_info;
    string path;

    if ((hFile = _findfirst(path.assign(dir_path).append("\\*").c_str(), &file_info)) != -1) {
        do {
            string file_path = path.assign(dir_path).append("\\").append(file_info.name);
            // 如果是目录,迭代之,如果不是,加入列表
            if ((file_info.attrib & _A_SUBDIR)) {
                if (strcmp(file_info.name, ".") != 0 && strcmp(file_info.name, "..") != 0) {
                    GetFileRelaPath(file_path, files_path);
                }
            } else {
                printf("%s\n\n", file_path.c_str());
                files_path.push_back(file_path);
            }
        } while (_findnext(hFile, &file_info) == 0);
        _findclose(hFile);
    }
    return;
}

int main(int argc, char *argv[])
{
    // 1.利用7z程序解压缩文件到temp文件夹
    string cmd = ".\\tools\\7zx64.exe x -y " + DATA_FILE_PATH + " -o" + TEMP_DIR;
    //system(cmd.c_str());
	
    // 2.获取json文件并拷贝到data文件夹中
    clock_t start_time = clock(); 
    vector <string> files_path;
    //GetFileRelaPath(TEMP_DIR, files_path);
    //LOGI("TEMP_DIR has files_path size = %I64d", files_path.size());
    //UnzipFile(files_path, JSON_DATA_DIR);
    clock_t spend_time = clock() - start_time;
    printf("[GetJsonToData Function] exec time is %lf s.\n\n", (double)spend_time / CLOCKS_PER_SEC);
    
    // 3.删除中间创建的文件和文件夹
    cmd = "rd /s /q " + TEMP_DIR;
    //system(cmd.c_str());

    // 4.处理json文件
    files_path.clear();
    GetFileRelaPath(JSON_DATA_DIR, files_path);
    vector<JSON_DATA_STRUCT> json_data;
    cJSON* json_obj = nullptr;
    for (string file_path : files_path) {
        json_obj = GetJsonObject(file_path.c_str());
        GetJsonData(json_obj, json_data);
    }
    printf("json data size = %I64d\n", json_data.size());

    // 字典树存储
    Trie* udev_tree = new Trie();
    for (JSON_DATA_STRUCT udev_data : json_data) {
        string pvid = udev_data.vid + udev_data.pid;
        // 转换为小写字母，前期如果做了处理可以省略
        transform(pvid.begin(), pvid.end(), pvid.begin(), ::tolower);
        udev_tree->Insert(pvid, udev_data);
    }
    
    udev_tree->SortOutput(udev_tree->root);
    return 0;
}

