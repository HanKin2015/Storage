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
#include <cstdio>
#include <cassert>
#include <unistd.h>
#include "rapidjson/writer.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"
#define BUFFER_LENGTH 64

/**
* @brief  从xml文件读取
* @note   
* @param  file_path [in] 文件路径
* @return 返回xml文件内容
*/
static std::string read_xml_from_file(const char *file_path)
{
    assert(file_path);
    
    if (access(file_path, F_OK)) {
        printf("file_path[%s] is not exists!\n", file_path);
    } else {
        printf("file_path[%s] is exists!\n", file_path);
    }
    
    std::ifstream ifs(file_path);
    std::string content((std::istreambuf_iterator<char>(ifs)),
                 (std::istreambuf_iterator<char>()));
    //std::cout << content << std::endl;
    ifs.close();
    return content;
}

/**
* @brief  解析xml文件中指定节点
* @note   
* @param  root [in] 根节点
* @param  node_name [in] 节点名称
* @return 解析内容
*/
static rapidjson::Value parse_node(rapidxml::xml_node<> *root_node, std::string node_name,
    rapidjson::Document::AllocatorType& allocator)
{
    assert(root_node);

    rapidjson::Value array_json(rapidjson::kArrayType);

    rapidxml::xml_node<> *node = root_node->first_node(node_name.c_str());
    if (node == nullptr) {
        printf("[USBFILTER] get node <%s> failed\n", node_name.c_str());
        return array_json;
    }
    for(rapidxml::xml_node<> *iter = node->first_node("Dev"); iter != nullptr; iter = iter->next_sibling()) {
        rapidxml::xml_attribute<char> *vpid = iter->first_attribute("ID");
        rapidxml::xml_attribute<char> *desc = iter->first_attribute("Desc");

        char vid[BUFFER_LENGTH] = { 0 };
        char pid[BUFFER_LENGTH] = { 0 };
        sscanf(vpid->value(), "%[^:]:%s", vid, pid);

        rapidjson::Value usb_filter_info(rapidjson::kObjectType);
        rapidjson::Value temp;
        temp.SetString(vid, allocator);
        usb_filter_info.AddMember("vid", temp, allocator);
        temp.SetString(pid, allocator);
        usb_filter_info.AddMember("pid", temp, allocator);
        temp.SetString(desc->value(), allocator);
        usb_filter_info.AddMember("desc", temp, allocator);
        array_json.PushBack(usb_filter_info, allocator);
    }
    return array_json;
}

/**
* @brief  解析xml配置文件
* @note   
* @param  policies [in] xml配置文件内容
* @return true解析成功 false解析失败
*/
std::string parse_policies(char *policies)
{
    if (policies == nullptr) {
        printf("[USBFILTER] policies is NULL\n");
        return "";
    }
    printf("policies[%lu]: %s\n", strlen(policies), policies);
    
    rapidxml::xml_document<> xml_doc;
    (void)xml_doc.parse<0>(policies);
    rapidxml::xml_node<> *root_node = xml_doc.first_node();
    if (root_node == nullptr) {
        printf("[USBFILTER] get <Conf> node failed\n");
        return "";
    }
    rapidxml::xml_node<> *remote_app_node = root_node->first_node("RemoteApp");
    if (remote_app_node == nullptr) {
        printf("[USBFILTER] get <RemoteApp> node failed\n");
        return "";
    }
    rapidxml::xml_node<> *usb_device_map_node = remote_app_node->first_node("USBDeviceMap");
    if (usb_device_map_node == nullptr) {
        printf("[USBFILTER] get <USBDeviceMap> node failed\n");
        return "";
    }

    rapidjson::Document json_doc;
    json_doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = json_doc.GetAllocator();
    rapidjson::Value policies_json(rapidjson::kObjectType);
    policies_json.AddMember("white_list", parse_node(usb_device_map_node, "WhiteList", allocator), allocator);
    policies_json.AddMember("black_list", parse_node(usb_device_map_node, "BlackList", allocator), allocator);
    json_doc.AddMember("policies", policies_json, allocator);
    
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    json_doc.Accept(writer);
    return std::string(buffer.GetString());
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
    
    std::string policies_json = parse_policies(policies);
    std::cout << policies_json << std::endl;
    return 0;
}