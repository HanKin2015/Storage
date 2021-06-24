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

/*
 * @brief 将cjson文件所有内容输出到一个字符串中
 * @param [IN]	json_file_path  json文件路径
 */
void GetFileContentToString(const char* json_file_path)
{
    fstream fs( "file.txt" );  // 创建个文件流对象,并打开"file.txt"
    stringstream ss;           // 创建字符串流对象
    ss << fs.rdbuf();          // 把文件流中的字符输入到字符串流中
    string str = ss.str();     // 获取流中的字符串
}