/**
* 文 件 名: read_file.cpp
* 文件描述: 读取文件内容
* 作    者: HanKin
* 创建日期: 2022.08.12
* 修改日期：2022.08.12
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include <cstring>
using namespace std;
 
/**
* @brief  读取文件内容
* @note   使用ifstream打开文件，后面使用四种方式读取内容
* @param  file_path [in] 文件路径
* @return 无
*/
static void read_file_by_ifstream(const char *file_path) 
{
    printf("---------- %s ----------\n", __FUNCTION__);
    assert(file_path);

    //1、创建流对象
    ifstream ifs;

    //2、打开文件并且判断是否打开成功
    ifs.open(file_path, ios::in) ;
    if (!ifs.is_open()) {
        cout << "文件打开失败" << endl;
        return;
    }

    char buf[BUFSIZ] = { 0 };
    //3、读数据
    //第一种
    memset(buf, 0, BUFSIZ);
    while (ifs >> buf) {
        cout << buf << "*" << endl;
    }

    //第二种
    memset(buf, 0, BUFSIZ);
    while (ifs.getline(buf, sizeof(buf))) {
        cout << buf << "*" << endl;
    }
    
    //第三种
    string str;
    while (getline(ifs, str)){
        cout << str << "*" << endl;
    }

    //第四种
    char c;
    while ((c = ifs.get()) != EOF) { // EOF end of file
        cout << c;
    }

    //5、关闭文件
    ifs.close();
}
 
int main(int argc, char *argv[])
{
    const char *file_path = "./b.txt";
    
    read_file_by_ifstream(file_path);
    return 0;
}