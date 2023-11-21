/*******************************************************************************
* 文 件 名: rapidjson_add_string.cpp
* 文件描述: rapidjson添加字符串
* 作    者: HanKin
* 创建日期: 2023.11.20
* 修改日期：2023.11.20
*
* Copyright (c) 2023 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstring>
#include <iomanip>
#include <sstream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

using namespace rapidjson;

int main()
{
    Document doc;
    doc.SetObject();

    // 十六进制字符串
    const char* hexString = "ABCD";

    // 存储十六进制字符串到 JSON 中
    Value hexValue(rapidjson::kStringType);
    hexValue.SetString(hexString, strlen(hexString), doc.GetAllocator());
    doc.AddMember("hexValue1", hexValue, doc.GetAllocator());
    
    // 存储十六进制字符串到 JSON 中（但是如果不使用StringRef强转不行，GenericStringRef 类是一个用于表示字符串引用的类）
    doc.AddMember("hexValue2", StringRef(hexString), doc.GetAllocator());
    
    int vid = 43981;
    char vid_hex_str[10] = { 0 };
    snprintf(vid_hex_str, sizeof(vid_hex_str), "0x%04X", vid);
    doc.AddMember("hexValue3", StringRef(vid_hex_str), doc.GetAllocator());
    snprintf(vid_hex_str, sizeof(vid_hex_str), "0x%05X", vid);   // 多了这一行结果就会存在问题，输出0x0ABC
    
    hexValue.SetString(vid_hex_str, strlen(vid_hex_str), doc.GetAllocator());
    doc.AddMember("hexValue4", hexValue, doc.GetAllocator());
    snprintf(vid_hex_str, sizeof(vid_hex_str), "0x%06X", vid);   // 这里不会影响hexValue方法添加字符串，但会影响hexValue3为0x00AB

    // 输出 JSON
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    doc.Accept(writer);
    std::cout << buffer.GetString() << std::endl;

    std::string message = buffer.GetString();
    message += "\n";
    FILE *fp = fopen("s.json", "w");
    if (fp) {
        int ret = fwrite(message.c_str(), sizeof(char), message.length(), fp);
        if (ret < 0) {
            printf("write to file failed.\n");
        }
    } else {
        printf("m_outfile stream invalid, write file failed!\n");
        return -1;
    }
    return 0;
}
