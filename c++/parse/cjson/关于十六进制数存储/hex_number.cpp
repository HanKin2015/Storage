/*******************************************************************************
* 文 件 名: hex_number.cpp
* 文件描述: 十六进制数存储
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

    // 十六进制数
    uint16_t hexValue = 0xABCD;
    
    // 将十六进制数转换为字符串形式
    std::stringstream stream;
    stream << std::hex << std::setw(4) << std::setfill('0') << hexValue;
    //std::string hexString = "0x" + stream.str();
    std::string hexString = stream.str();   // 有没有0x前缀对转换没有影响
    
    // 将十六进制字符串转换为整数
    int hexValue2;
    std::stringstream ss;
    ss << std::hex << hexString;
    ss >> hexValue2;
    std::cout << "转换后的整数值为: " << hexValue2 << std::endl;
    
    // 将十六进制字符串转换为整数
    int hexValue3 = std::stoi(hexString, 0, 16);
    std::cout << "转换后的整数值为: " << hexValue3 << std::endl;

    // 存储十六进制数到 JSON 中
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    writer.StartObject();
    writer.Key("hexValue");
    std::string str = std::to_string(hexValue);
    std::cout << str << std::endl;
    writer.String(hexString.c_str());  // 将十六进制数转换为字符串存储
    writer.EndObject();

    // 输出 JSON
    std::cout << buffer.GetString() << std::endl;

    return 0;
}
