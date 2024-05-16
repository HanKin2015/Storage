/*******************************************************************************
* 文 件 名: ini_interface.cpp
* 文件描述: 解析ini文件
* 备    注: 
* 作    者: HanKin
* 创建日期: 2024.05.15
* 修改日期：2024.05.15
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <map>
#include <string>
 
std::string trim(const std::string& str) {
    std::string temp(str);
    // 去除开头的空格
    temp.erase(temp.begin(), std::find_if(temp.begin(), temp.end(), [](unsigned char ch) { return !std::isspace(ch); }));
    // 去除结尾的空格
    temp.erase(std::find_if(temp.rbegin(), temp.rend(), [](unsigned char ch) {return !std::isspace(ch); }).base(), temp.end());
    return temp;
}

class IniReader {
public:
    IniReader(const std::string& filename) {
        std::ifstream file(filename);
        std::string line;
        std::string section;
        if (file.is_open()) {
            while (std::getline(file, line)) {
                line = trim(line);
                if (line.empty() || line[0] == ';' || line[0] == '#') {
                    // 忽略空行和注释
                    continue;
                }
                if (line[0] == '[') {
                    // 处理段落
                    auto endPos = line.find(']');
                    if (endPos != std::string::npos) {
                        section = trim(line.substr(1, endPos - 1));
                    }
                } else {
                    // 处理键值对
                    auto delimPos = line.find('=');
                    if (delimPos != std::string::npos) {
                        auto key = trim(line.substr(0, delimPos));
                        auto value = trim(line.substr(delimPos + 1));
                        data[section][key] = value;
                    }
                }
            }
            file.close();
        }
    }

    std::string operator[](const std::string& sectionAndKey) const {
        auto sectionEnd = sectionAndKey.find(':');
        std::string section = sectionAndKey.substr(0, sectionEnd);
        std::string key = sectionAndKey.substr(sectionEnd + 1);
        auto it = data.find(section);
        if (it != data.end()) {
            auto it2 = it->second.find(key);
            if (it2 != it->second.end()) {
                return it2->second;
            }
        }
        return "";
    }

private:
    std::map<std::string, std::map<std::string, std::string>> data;
};
 
int main() {
    IniReader iniReader("automated_configuration.ini");
    std::cout << "resolutions: " << iniReader["setting:resolutions"] << std::endl;
    std::cout << "interval: " << iniReader["setting:interval"] << std::endl;
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #g++ a.cpp -std=c++11
[root@ubuntu0006:~/cmake] #./a.out
resolutions: 640x480,320x240
interval: 1000
*/