/**
* 文 件 名: parse_string_without_split.cpp
* 文件描述: 高效解析字符串
* 作    者: HanKin
* 创建日期: 2023.07.10
* 修改日期：2023.07.10
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <iostream>
#include <sstream>
#include <map>
#include <cassert>
#include <vector>

static bool parse_string()
{
    std::string str = "Ep=82 NoTransfers=250 BytesPerTransfer=4294967295;Ep=87 NoTransfers=255 BytesPerTransfer=4294967295;Ep=02 NoTransfers=215 BytesPerTransfer=4294967290";
    std::stringstream ss(str);

    std::string sub_str;
    while (std::getline(ss, sub_str, ';')) {
        std::stringstream sub_ss(sub_str);
        std::string key, value;
        std::map<std::string, std::string> kv_map;
        while (std::getline(sub_ss, key, '=') && std::getline(sub_ss, value, ' ')) {
            kv_map[key] = value;
        }

        // 处理每个子串中的键值对
        std::cout << "Ep=" << kv_map["Ep"] << ", NoTransfers=" << kv_map["NoTransfers"] << ", BytesPerTransfer=" << kv_map["BytesPerTransfer"] << std::endl;
    }
    return true;
}

static void parse_param(const char *param_str, std::vector<std::map<std::string, std::string> > &param)
{
    assert(param_str);
    
    param.clear();
    std::stringstream ss(param_str);

    std::string sub_str;
    while (std::getline(ss, sub_str, ';')) {
        std::stringstream sub_ss(sub_str);
        std::string key, value;
        std::map<std::string, std::string> kv_map;
        while (std::getline(sub_ss, key, '=') && std::getline(sub_ss, value, ' ')) {
            kv_map[key] = value;
        }

        // 处理每个子串中的键值对
        std::cout << "Ep=" << kv_map["Ep"] << ", NoTransfers=" << kv_map["NoTransfers"] << ", BytesPerTransfer=" << kv_map["BytesPerTransfer"] << std::endl;
        param.push_back(kv_map);
    }
    return;
}

// <Dev ID="0c45:1d7d" Desc="usb kx-2 sound card" Quirk="2" Ep="82" Aligned="8192" ></Dev>
// ID="0c45:1d7d" Desc="usb kx-2 sound card" Quirk="2" Param="Ep=82 NoTransfers=250 BytesPerTransfer=4294967295;Ep=87 NoTransfers=255 BytesPerTransfer=4294967295;Ep=02 NoTransfers=215 BytesPerTransfer=4294967290"
int main()
{
    parse_string();
    
    const char str[] = "Ep=82 NoTransfers=250 BytesPerTransfer=4294967295;Ep=87 NoTransfers=255 BytesPerTransfer=4294967295;Ep=02 NoTransfers=215 BytesPerTransfer=4294967290";
    std::vector<std::map<std::string, std::string> > param;
    printf("param size = %lu\n", param.size());
    (void)parse_param(str, param);
    printf("param size = %lu\n", param.size());
    for (std::map<std::string, std::string> kv_map : param) {
        std::cout << "Ep=" << kv_map["Ep"] << ", NoTransfers=" << kv_map["NoTransfers"] << ", BytesPerTransfer=" << kv_map["BytesPerTransfer"] << std::endl;
    }
    return 0;
}
