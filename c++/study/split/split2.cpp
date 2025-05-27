/*******************************************************************************
* 文 件 名: split2.cpp
* 文件描述: split函数实现
* 备    注: 
* 作    者: HanKin
* 创建日期: 2024.05.15
* 修改日期：2024.05.15
*
* Copyright (c) 2024 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdint>

//字符串分割函数
std::vector<std::string> split(std::string str, std::string pattern)
{
    std::string::size_type pos;
    std::vector<std::string> result;
    str += pattern;//扩展字符串以方便操作
    size_t str_size = str.size();

    for (int i = 0; i < (int)str_size; i++) {
        pos = str.find(pattern, i);
        if (pos < str_size) {
            std::string s = str.substr(i, pos - i);
            result.push_back(s);
            i = pos + pattern.size() - 1;
        }
    }
    return result;
}

void initDefaultBindInfo(std::string usb_path_list)
{
    std::vector<std::string> usb_paths = split(usb_path_list, "/");
    int usb_path_cnt = usb_paths.size();
    for (uint16_t i = 0; i < usb_path_cnt; i++) {
        std::vector<std::string> bus_ports = split(usb_paths[i], "-");
        assert(bus_ports.size() == 2);

        int bus_num = strtol(bus_ports[0].c_str(), NULL, 10);
        uint64_t bind_id = bus_num;
        std::vector<std::string> ports = split(bus_ports[1], ".");
        assert(ports.size() > 0);
        int port_cnt = ports.size();
        for (int j = 0; j < port_cnt; j++) {
            int prot_num = strtol(ports[j].c_str(), NULL, 10);
            bind_id |= ((uint64_t)prot_num << (8 + j * 8));
        }

        uint16_t channel_id = i;
        printf("add channel default bind info. channel_id=%" PRIu16
            " bind_id= %" PRIu64 "\n", channel_id, bind_id);
    }
}

int main()
{
    char usb_path_list[] = "1-1.1/1-1.2/1-1.3/1-1.4.1/1-1.4.3/1-1.4.4";
    initDefaultBindInfo(usb_path_list);
    return 0;
}
/*
[root@ubuntu0006:~/cmake] #./a.out
add channel default bind info. channel_id=0 bind_id= 65793
add channel default bind info. channel_id=1 bind_id= 131329
add channel default bind info. channel_id=2 bind_id= 196865
add channel default bind info. channel_id=3 bind_id= 17039617
add channel default bind info. channel_id=4 bind_id= 50594049
add channel default bind info. channel_id=5 bind_id= 67371265
*/