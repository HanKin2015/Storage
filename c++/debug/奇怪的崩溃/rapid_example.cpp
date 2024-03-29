/**
* 文 件 名: rapid_example.cpp
* 文件描述: 学习rapidjson和rapidxml结合使用
* 备    注: 解析xml文件，保存数据为json格式
* 作    者: HanKin
* 创建日期: 2022.06.21
* 修改日期：2022.06.21
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <iostream>
#include <sstream>
#include <string.h>
#include "rapidjson/writer.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"

/**
* @brief  从xml文件读取
* @note   
* @param  file_path [in] 文件路径
* @return 返回xml文件内容
*/
std::string read_xml_from_file(const char *file_path)
{
    std::ifstream ifs(file_path);
    std::string content((std::istreambuf_iterator<char>(ifs)),
                 (std::istreambuf_iterator<char>()));
    //std::cout << content << std::endl;
    ifs.close();
    return content;
}

/**
* @brief  解析xml配置文件
* @note   
* @param  confxml [in] xml配置文件内容
* @return true解析成功 false解析失败
*/
bool parse_confxml(const char *confxml)
{
    char *policies = const_cast<char *>(confxml);
    
    rapidxml::xml_document<> doc;
    doc.parse<0>(policies);

    rapidxml::xml_node<>* node = doc.first_node();
    std::cout << (node->name()) << std::endl;
    node = node->first_node("USBDeviceMap");
    node = node->first_node("WhiteList");
    for(rapidxml::xml_node<> *iter = node->first_node("Dev"); iter != NULL; iter = iter->next_sibling()) {
        rapidxml::xml_attribute<char> *id = iter->first_attribute("ID");
        std::string vpid = id->value();
        int pos = vpid.find(":");
        std::string vid = vpid.substr(0, pos);
        std::string pid = vpid.substr(pos);
        rapidxml::xml_attribute<char> *desc = iter->first_attribute("Desc");
        std::cout << vid << ":" << pid << " " << desc->value() << std::endl;
    }

    std::ofstream out("test.xml");//ofstream 默认时，假设文件存在则会覆盖原来的内容，不存在则会新建
    out << doc;//doc 这样输出时在目标文件里不会有xml 头信息---<?xml version='1.0' encoding='utf-8' >
    out.close();
    return true;
}

int main(int argc, char *argv[])
{
    const char *file_path = "config.xml";

    std::string confxml = read_xml_from_file(file_path);
    
    int confxml_length = confxml.length();
    char *policies = NULL;
    policies = (char *)malloc(confxml_length*sizeof(char)+1);
    if (policies == NULL) {
        std::cout << "policies is NULL" << std::endl;
    }
    strncpy(policies, confxml.c_str(), confxml_length);
    
    (void)parse_confxml(policies);
    return 0;
}










