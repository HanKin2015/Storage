/**
* 文 件 名: deal_linux_net_udev.cpp
* 文件描述: 收集Linux内核网卡驱动中的usb网卡名单
* 结    果: 失败告终，有换行，一行的结束符不固定
* 作    者: HanKin
* 创建日期: 2021.11.23
* 修改日期：2021.11.23
*
* Copyright (c) 2021 HanKin. All rights reserved.
*/

#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <map>
using namespace std;

void study_istringstream()
{
    printf("\n==============%s:%d==============\n", __FUNCTION__, __LINE__);
    
    std::string file_path = "gs_usb.c";
    map<string, string> dict;
 
    ifstream fp;
    fp.open(file_path.c_str());
 
    std::string str_line, str_split;
    std::istringstream iss;
    int line_idx = 1;
    while (getline(fp, str_line)) {
        iss.str(str_line);
        string str = iss.str();
        
        if (str.find("#define") != -1) {    // find return -1 or index
            cout << "line number: " << line_idx << endl;
            cout << "原字符串: " << str << endl;
            //while (iss >> str_split) {
            //    cout << str_split << endl;
            //}
            string head, key, value;
            iss >> head >> key >> value;
            cout << head << key << value << endl;
            dict[key] = value;
            cout << endl;
        }
        
        if (str.find("USB_DEVICE") != -1) {
            cout << "line number: " << line_idx << endl;
            cout << "原字符串: " << str << endl;
            
            int lpos = str.find("(");
            int rpos = str.find(")");
            cout << str.substr(lpos, rpos - lpos) << endl;
            cout << endl;
        }

        iss.clear();
        iss.str("");
        line_idx++;
    }
}

int main()
{
    study_istringstream();
    return 0;
}