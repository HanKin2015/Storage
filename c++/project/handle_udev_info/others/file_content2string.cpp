/*
 * file_content2string.cpp
 * 将文件全部内容读取到一个string字符串中
 * 
 * 两种方法
 * 
 * date  : 2021.06.11
 * author: hankin 
 * 
 * Copyright (c) 2021 hankin. All rights reserved.
 *
 */

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>

using namespace std;

void func1()
{
    fstream fs("./data_file_content2string");    // 创建个文件流对象并打开文件
    stringstream ss;        // 字符串流对象
    ss << fs.rdbuf();       // 将文件流中的字符输入到字符串流中
    string str = ss.str();  //获取流中的字符串
    cout << str << endl;
    return ;
}

void func2()
{
    string file_path = "./data_file_content2string";

    // 1.打开文件
    FILE* fp = fopen(file_path.c_str(), "rb+");
    if(!fp) {
        printf("open file failed!\n");
        return ;
    }
    
    // 2.获取文件内容长度
    fseek(fp, 0, SEEK_END);
    int content_len = ftell(fp);
    if(content_len == 0) {
        printf("file no content!\n");
        return ;
    }
    
    // 3.获取文件内容到字符串中
    fseek(fp, 0, SEEK_SET);
    char* content = (char*) malloc (sizeof(char) * content_len);
    int ret = fread(content, 1, content_len, fp);
    fclose(fp);

    cout << content << endl;
    return ;
}

int main(int argc, char *argv[])
{
    func2();   
    return 0;
}