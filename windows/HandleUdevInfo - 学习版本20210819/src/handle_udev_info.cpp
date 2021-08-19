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

#include "handle_udev_info.hpp"

/*
 * @brief 判断文件或者目录是否存在
 * @note
 * 
 * @param path [in] 文件或者目录路径
 * @return 存在返回true，反之false
 */
static bool IsExist(string path)
{
    return (_access(path.c_str(), F_OK) != -1);
}

/*
 * @brief 解压zip文件到目标文件夹
 * @note  使用7z.exe工具解压
 * 
 * @param path [in] 数据文件夹路径
 * @param target_dir [in] 目标文件夹路径
 * @return 无
 */
void UnzipFileBy7z(vector<string> files_path, string target_dir)
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
 * @brief string类型转tchar类型
 * @note 更改通过设置字符集为使用多字节字符集来转换
 * 
 * @param src [in] string字符串
 * @param buf [out] tchar字符串
 * @return 无
 */
static void string2tchar(std::string& src, TCHAR* buf)
{
#ifdef _UNICODE  
    _stprintf_s(buf, MAX_PATH, _T("%S"), src.c_str());  // %S宽字符  
#else  
    _stprintf_s(buf, MAX_PATH, _T("%s"), src.c_str());  // %s单字符
#endif
    return;
}

/*
 * @brief 解压zip文件到目标文件夹
 * @note  使用Zip Utils库
 *
 * @param path [in] 数据文件路径
 * @param target_dir [in] 目标文件夹路径
 * @return 无
 */
static int UnzipFile(string file_path, string target_dir)
{
    // 获取文件后缀
    size_t idx = file_path.find_last_of('.');
    string postfix = file_path.substr(idx + 1);
    if (postfix == "zip") {
        // 解zip压缩文件到目标文件夹
        HZIP hz = OpenZip(file_path.c_str(), nullptr);
        if (!hz) {
            LOGE("OpenZip failed.");
            return -1;
        }
        ZRESULT zret = SetUnzipBaseDir(hz, target_dir.c_str());	// 指定文件夹
        if (zret != ZR_OK) {
            LOGE("SetUnzipBaseDir failed, 0x%x.", zret);
            return -1;
        }

        ZIPENTRY ze;
        GetZipItem(hz, -1, &ze);
        int numitems = ze.index;
        for (int i = 0; i < numitems; i++) {
            GetZipItem(hz, i, &ze);
            UnzipItem(hz, i, ze.name);
        }
        CloseZip(hz);
    }
    return 0;
}

/*
 * @brief 解压zip文件到目标文件夹
 * @note  使用Zip Utils库（单线程版本）
 * 
 * @param path [in] 数据文件夹路径
 * @param target_dir [in] 目标文件夹路径
 * @return 无
 */
int UnzipFileSinglethread(vector<string> files_path, string target_dir)
{
    for (string file_path : files_path) {
        UnzipFile(file_path, target_dir);
    }
    return 0;
}

/*
 * @brief 解压zip文件到目标文件夹
 * @note  使用Zip Utils库（多线程版本）
 * 
 * @param path [in] 数据文件夹路径
 * @param target_dir [in] 目标文件夹路径
 * @return 无
 */
int UnzipFileMultithread(vector<string> files_path, string target_dir)
{
    list<thread> threads;

    for (string file_path : files_path) {
        threads.push_back(thread(UnzipFile, file_path, target_dir));
    }
    for (thread& t : threads) {
        t.join();
    }
    return 0;
}

/*
 * @brief 获取dir_path文件夹下所有文件的相对路径
 * @note
 * @param dir_path [in] 数据文件夹路径
 * @param files_path [out] 文件的相对路径
 * @return 无
 */
int GetFileRelaPath(string dir_path, vector<string> &files_path)
{
    intptr_t hFile = 0;             // 文件句柄
    struct _finddata_t file_info;   // 文件信息
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
                LOGD("%s", file_path.c_str());
                files_path.push_back(file_path);
            }
        } while (_findnext(hFile, &file_info) == 0);
        _findclose(hFile);
    } else {
        LOGE("dir_path is not exist.");
        return -1;
    }
    return 0;
}

/*
 * @brief 保存数据到本地csv文件
 * @note
 * @param udev_data [in] USB设备信息数据
 * @return 无
 */
static int SaveData2Csv(vector<udev_info> udev_data)
{
    LOGI("start to save data to local csv file [%s].", CSV_FILE_PATH.c_str());

    FILE* fp = fopen(CSV_FILE_PATH.c_str(), "w");
    if (!fp) {
        LOGE("open CSV_FILE_PATH failed! strerror: %s", strerror(errno));
        return -1;
    }
    for (udev_info& it : udev_data) {
        fprintf(fp, "%s,%s,%s,%s,%s\n", it.vid.c_str(), it.pid.c_str(), \
            it.rev.c_str(), it.man_str.c_str(), it.pro_str.c_str());
    }
    fclose(fp);
    return 0;
}

/*
 * @brief 删除一个文件夹下的所有内容
 * @note
 * @param dir_path [in] 文件夹路径
 * @return 无
 */
int DeleteDirectory(string dir_path)
{
    LOGD("start delete directory [%s].", dir_path.c_str());

    intptr_t hFile = 0;             // 文件句柄
    struct _finddata_t file_info;   // 文件信息
    string path;

    if ((hFile = _findfirst(path.assign(dir_path).append("\\*").c_str(), &file_info)) != -1) {
        do {
            string file_path = path.assign(dir_path).append("\\").append(file_info.name);
            // 如果是目录,迭代之,如果不是,加入列表
            if ((file_info.attrib & _A_SUBDIR)) {
                if (strcmp(file_info.name, ".") != 0 && strcmp(file_info.name, "..") != 0) {
                    DeleteDirectory(file_path);             //递归删除文件夹
                    RemoveDirectory(file_path.c_str());     //只能删除空的文件夹
                }
            } else {
                LOGD("delete file [%s].", file_path.c_str());
                DeleteFile(file_path.c_str());
            }
        } while (_findnext(hFile, &file_info) == 0);
        _findclose(hFile);
    } else {
        LOGE("dir_path is not exist.");
        return -1;
    }
    RemoveDirectory(dir_path.c_str());
    return 0;
}

int handle_udev_main()
{
    int ret = 0;
    string cmd = "";
    vector <string> files_path;
    Trie* udev_tree = nullptr;
    string pvid = "";
    vector<JSON_DATA_STRUCT> json_data;
    cJSON* json_obj = nullptr;

    // 1.解压缩文件到temp文件夹
    ret = UnzipFile(DATA_FILE_PATH, TEMP_DIR);
    if (ret != 0) {
        goto FAILED;
    }

    // 2.获取json文件并拷贝到data文件夹中
    ret = GetFileRelaPath(TEMP_DIR, files_path);
    if (ret != 0) {
        goto FAILED;
    }
    LOGI("zip file's relative path size [%I64d].", files_path.size());
    //ret = UnzipFileSinglethread(files_path, JSON_DATA_DIR);
    ret = UnzipFileMultithread(files_path, JSON_DATA_DIR);
    if (ret != 0) {
        goto FAILED;
    }

    // 3.处理json文件
    files_path.clear();
    GetFileRelaPath(JSON_DATA_DIR, files_path);
    for (string file_path : files_path) {
        json_obj = GetJsonObject(file_path.c_str());
        GetJsonData(json_obj, json_data);
    }
    LOGI("untreated json data size [%I64d].", json_data.size());

    // 4、字典树存储
    udev_tree = new Trie();
    for (JSON_DATA_STRUCT udev_data : json_data) {
        pvid = udev_data.vid + udev_data.pid;
        // 转换为小写字母，前期如果做了处理可以省略
        //transform(pvid.begin(), pvid.end(), pvid.begin(), ::tolower);
        udev_tree->Insert(pvid, udev_data);
    }

    // 5、排序去重输出到结构体中
    json_data.clear();
    udev_tree->SortOutput(udev_tree->root, json_data);
    LOGI("treated json data size [%I64d].", json_data.size());

    // 5、保存数据到本地csv表格文件中
    ret = SaveData2Csv(json_data);
    if (ret != 0) {
        goto FAILED;
    }

    // 6.删除中间创建的文件和文件夹
    DeleteDirectory(TEMP_DIR);
    DeleteDirectory(JSON_DATA_DIR);
    return 0;

FAILED:
    LOGE("handle usb device info failed.");
    return -1;
}
