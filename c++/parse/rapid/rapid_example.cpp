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

typedef struct USB_FILTER_INFO {
    char vpid[4096];
    char desc[4096];
} usb_filter_info;

/**
* @brief  保存为json格式
* @note   
* @param  white_infos [in] 白名单内容
* @param  black_infos [in] 黑名单内容
* @return 无
*/
rapidjson::Value list_array(rapidjson::Document::AllocatorType& allocator, std::vector<usb_filter_info> infos)
{
    rapidjson::Value array_json(rapidjson::kArrayType);
    
    int info_size = infos.size();
    //for (auto info : infos) {
    for (int i = 0; i < info_size; i++) {
        std::string vpid = infos[i].vpid;
        int pos = vpid.find(":");
        if (pos == std::string::npos) {
            std::cout << "not found : symbol" << std::endl;
            return array_json;
        }
        std::string vid = vpid.substr(0, pos);
        std::string pid = vpid.substr(pos+1);

        rapidjson::Value json(rapidjson::kObjectType);
        //rapidjson::Value index(rapidjson::kNumberType);
        //index.SetInt(i);
        //json.AddMember("index", index, allocator);
        //std::cout << vid.c_str() << ' ' << pid.c_str() << std::endl;
        rapidjson::Value temp;
        temp.SetString(vid.c_str(), allocator);
        json.AddMember("vid", temp, allocator);
        temp.SetString(pid.c_str(), allocator);
        json.AddMember("pid", temp, allocator);
        temp.SetString(infos[i].desc, allocator);
        json.AddMember("desc", temp, allocator);
        array_json.PushBack(json, allocator);
    }
    return array_json;
}

/**
* @brief  保存为json格式
* @note   
* @param  white_infos [in] 白名单内容
* @param  black_infos [in] 黑名单内容
* @return 无
*/
void save_json(std::vector<usb_filter_info> white_infos, std::vector<usb_filter_info> black_infos)
{
    rapidjson::Document doc;
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();
    rapidjson::Value policies_json(rapidjson::kObjectType);
    
    policies_json.AddMember("white_list", list_array(allocator, white_infos), allocator);
    policies_json.AddMember("black_list", list_array(allocator, black_infos), allocator);
    doc.AddMember("policies", policies_json, allocator);
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);
    std::string json = std::string(buffer.GetString());
    std::cout << json << std::endl;
    return;
}

/**
* @brief  解析xml文件中指定节点
* @note   
* @param  root [in] 根节点
* @param  node_name [in] 节点名称
* @return 解析内容
*/
std::vector<usb_filter_info> parse_node(rapidxml::xml_node<> *root, std::string node_name)
{
    std::vector<usb_filter_info> infos;
    
    rapidxml::xml_node<> *node = root->first_node(node_name.c_str());
    for(rapidxml::xml_node<> *iter = node->first_node("Dev"); iter != NULL; iter = iter->next_sibling()) {
        rapidxml::xml_attribute<char> *id = iter->first_attribute("ID");
        rapidxml::xml_attribute<char> *desc = iter->first_attribute("Desc");
        std::cout << id->value() << " " << desc->value() << std::endl;
        usb_filter_info info;
        memset(info.vpid, 0, sizeof(info.vpid));
        strncpy(info.vpid, id->value(), strlen(id->value()));
        memset(info.desc, 0, sizeof(info.desc));
        strncpy(info.desc, desc->value(), strlen(desc->value()));
        //std::cout << sizeof(info) << ' ' << sizeof(info.desc) << ' ' << strlen(desc->value()) << std::endl;
        infos.push_back(info);
    }
    return infos;
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
    //std::cout << (node->name()) << std::endl;
    node = node->first_node("USBDeviceMap");

    std::vector<usb_filter_info> white_infos = parse_node(node, "WhiteList");
    std::vector<usb_filter_info> black_infos = parse_node(node, "BlackList");

    std::ofstream out("test.xml");//ofstream 默认时，假设文件存在则会覆盖原来的内容，不存在则会新建
    out << doc;//doc 这样输出时在目标文件里不会有xml 头信息---<?xml version='1.0' encoding='utf-8' >
    out.close();
    
    save_json(white_infos, black_infos);
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
    memset(policies, 0, confxml_length*sizeof(char)+1);
    strncpy(policies, confxml.c_str(), confxml_length);
    
    (void)parse_confxml(policies);
    return 0;
}










