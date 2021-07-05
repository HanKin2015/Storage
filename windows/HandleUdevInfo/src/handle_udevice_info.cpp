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
                int idx = file_path.find_last_of('.');
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
 * @brief 获取json文件并拷贝到data文件夹中
 * @note 
 * @param path [in] 数据文件夹路径
 * @return 文件存在返回true，反之false
 */
bool IsExist(string file_path)
{
    return (_access(file_path.c_str(), F_OK) != -1);
}

#include <thread>
std::thread::id main_thread_id = std::this_thread::get_id();
void hello()
{
    std::cout << "Hello Concurrent World\n";
    if (main_thread_id == std::this_thread::get_id())
        std::cout << "This is the main thread.\n";
    else
        std::cout << "This is not the main thread.\n";
}

void pause_thread(int n) {
    std::this_thread::sleep_for(std::chrono::seconds(n));
    std::cout << "pause of " << n << " seconds ended\n";
}

/*
 * cd "d:\Github\Storage\c++\udev\" && g++ handle_udevice_info.cpp json_interface.cpp cJSON.c -o handle_udevice_info && "d:\Github\Storage\c++\udev\"handle_udevice_info
 */
void study_thread()
{
    std::thread t(hello);
    std::cout << t.hardware_concurrency() << std::endl;//可以并发执行多少个(不准确)
    std::cout << "native_handle " << t.native_handle() << std::endl;//可以并发执行多少个(不准确)
    t.join();
    std::thread a(hello);
    a.detach();
    std::thread threads[5];                         // 默认构造线程

    std::cout << "Spawning 5 threads...\n";
    for (int i = 0; i < 5; ++i)
        threads[i] = std::thread(pause_thread, i + 1);   // move-assign threads
    std::cout << "Done spawning threads. Now waiting for them to join:\n";
    for (auto& thread : threads)
        thread.join();
    std::cout << "All threads joined!\n";
}

int main(int argc, char *argv[])
{
    // 1.利用7z程序解压缩文件到temp文件夹
    string cmd = ".\\tools\\7zx64.exe x -y " + DATA_FILE_PATH + " -o" + TEMP_DIR;
    //system(cmd.c_str());
	
    // 2.获取json文件并拷贝到data文件夹中
    clock_t start = clock(); 
    //GetJsonToData(TEMP_DIR.c_str());
    printf("[GetJsonToData Function] exec time is %lf s.\n\n", (double)(clock() - start) / CLOCKS_PER_SEC);
    
    // 3.删除中间创建的文件和文件夹
    cmd = "rd /s /q " + TEMP_DIR;
    //system(cmd.c_str());

    // 4.处理json文件
    cJSON* json_obj = GetJsonObject(".\\data\\json\\11.22.33.44-2021.03.11.15.01.41.json");
    vector<JSON_DATA_STRUCT> json_data;
    GetJsonData(json_obj, json_data);
    printf("json data size = %lu\n", json_data.size());

    LOGE("hello world!");
    LOGI("hello world!");
    LOGW("hello world!");

    study_thread();
    return 0;
}

