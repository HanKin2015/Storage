/**
* 文 件 名: rapidxml_example.cpp
* 文件描述: 学习rapidxml的使用
* 作    者: HanKin
* 创建日期: 2022.06.19
* 修改日期：2022.06.20
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <iostream>
#include <sstream>
#include <string.h>
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"

using namespace rapidxml;

/**
* @brief  创建xml文件
* @note   网上的教程https://blog.csdn.net/qq_36333986/article/details/124799767
* @param  无
* @return 无
*/
void crateXml()
{
    xml_document<> doc;
    xml_node<>* rot = doc.allocate_node(rapidxml::node_pi, doc.allocate_string("xml version='1.0' encoding='utf-8'"));
    doc.append_node(rot);
    xml_node<>* node = doc.allocate_node(node_element, "config", "information");
    xml_node<>* color = doc.allocate_node(node_element, "color", NULL);
    doc.append_node(node);
    node->append_node(color);
    color->append_node(doc.allocate_node(node_element, "red", "0.1"));
    color->append_node(doc.allocate_node(node_element, "green", "0.1"));
    color->append_node(doc.allocate_node(node_element, "blue", "0.1"));
    color->append_node(doc.allocate_node(node_element, "alpha", "1.0"));

    xml_node<>* size = doc.allocate_node(node_element, "size", NULL);
    size->append_node(doc.allocate_node(node_element, "x", "640"));
    size->append_node(doc.allocate_node(node_element, "y", "480"));
    node->append_node(size);

    xml_node<>* mode = doc.allocate_node(rapidxml::node_element, "mode", "screen mode");
    mode->append_attribute(doc.allocate_attribute("fullscreen", "false"));
    node->append_node(mode);

    std::string text;
    rapidxml::print(std::back_inserter(text), doc, 0);

    std::cout << text << std::endl;

    std::ofstream out("config.xml");
    out << doc;
}

/**
* @brief  根据字符串创建xml文件
* @note   网上的教程https://blog.csdn.net/qq_36333986/article/details/124799767
* @param  无
* @return 无
*/
void createXml2()
{
    xml_document<> doc; //是解析器
    char a[] = "<top>"//假设单独传, 就不能加上xml的头部信息，
               //否则会报错
        "<name>tangqiang</name>"
        "<age>22</age>"
        "</top>";
    char* p = a;
    doc.parse<0>(p);

    xml_node<>* node = doc.first_node();//去顶级结点
    std::cout << (node->name()) << std::endl;
    node = node->first_node();
    while (node) {
        std::cout << node->name() << ":" << node->value() << std::endl;//name() value()返回的字符串不会去掉首尾的空白字符
        node = node->next_sibling();
    }

    std::ofstream out("test.xml");//ofstream 默认时，假设文件存在则会覆盖原来的内容，不存在则会新建
    out << doc;//doc 这样输出时在目标文件里不会有xml 头信息---<?xml version='1.0' encoding='utf-8' >
    out.close();
}

void create_usb_list_xml(const char *file_path)
{
    xml_document<> doc;
    xml_node<> *rot = doc.allocate_node(rapidxml::node_pi, doc.allocate_string("xml version='1.0' encoding='utf-8'"));
    doc.append_node(rot);
    
    xml_node<> *node  = doc.allocate_node(node_element, "Conf", "information");
    xml_node<> *color = doc.allocate_node(node_element, "color", NULL);
    doc.append_node(node);
    node->append_node(color);
    color->append_node(doc.allocate_node(node_element, "red", "0.1"));
    color->append_node(doc.allocate_node(node_element, "green", "0.1"));
    color->append_node(doc.allocate_node(node_element, "blue", "0.1"));
    color->append_node(doc.allocate_node(node_element, "alpha", "1.0"));

    xml_node<> *size = doc.allocate_node(node_element, "size", NULL);
    size->append_node(doc.allocate_node(node_element, "x", "640"));
    size->append_node(doc.allocate_node(node_element, "y", "480"));
    node->append_node(size);

    xml_node<> *mode = doc.allocate_node(rapidxml::node_element, "mode", "screen mode");
    mode->append_attribute(doc.allocate_attribute("fullscreen", "false"));
    node->append_node(mode);
    
    // 应用节点
    xml_node<> *app_node = doc.allocate_node(rapidxml::node_element, "RemoteApp", NULL);
    node->append_node(app_node);
    
    // USB名单
    xml_node<> *udev_map = doc.allocate_node(rapidxml::node_element, "USBDeviceMap", NULL);
    app_node->append_node(udev_map);
    xml_node<> *white_list = doc.allocate_node(rapidxml::node_element, "WhiteList", NULL);
    udev_map->append_node(white_list);
    xml_node<> *black_list = doc.allocate_node(rapidxml::node_element, "BlackList", NULL);
    udev_map->append_node(black_list);
    
    // 白名单
    xml_node<> *white_list_dev1 = doc.allocate_node(rapidxml::node_element, "Dev", NULL);
    white_list_dev1->append_attribute(doc.allocate_attribute("ID", "1234:4321"));
    white_list_dev1->append_attribute(doc.allocate_attribute("Desc", "keyborad"));
    white_list->append_node(white_list_dev1);
    xml_node<> *white_list_dev2 = doc.allocate_node(rapidxml::node_element, "Dev", NULL);
    white_list_dev2->append_attribute(doc.allocate_attribute("ID", "1bC4:4321"));
    white_list_dev2->append_attribute(doc.allocate_attribute("Desc", "ukey"));
    white_list->append_node(white_list_dev2);
    xml_node<> *white_list_dev3 = doc.allocate_node(rapidxml::node_element, "Dev", NULL);
    white_list_dev3->append_attribute(doc.allocate_attribute("ID", "AF34:4Ym1"));
    white_list_dev3->append_attribute(doc.allocate_attribute("Desc", "iphone"));
    white_list->append_node(white_list_dev3);
    
    // 黑名单
    xml_node<> *black_list_dev1 = doc.allocate_node(rapidxml::node_element, "Dev", NULL);
    black_list_dev1->append_attribute(doc.allocate_attribute("ID", "af34:ge21"));
    black_list_dev1->append_attribute(doc.allocate_attribute("Desc", "mouce"));
    black_list->append_node(black_list_dev1);
    xml_node<> *black_list_dev2 = doc.allocate_node(rapidxml::node_element, "Dev", NULL);
    black_list_dev2->append_attribute(doc.allocate_attribute("ID", "GTFD:dser"));
    black_list_dev2->append_attribute(doc.allocate_attribute("Desc", "display"));
    black_list->append_node(black_list_dev2);

    // 转换成string打印
    std::string text;
    rapidxml::print(std::back_inserter(text), doc, 0);
    std::cout << text << std::endl;

    // 保存到文件
    std::ofstream out(file_path);
    out << doc;
    out.close();
    return;
}

/**
* @brief  从xml文件读取
* @note   
* @param  file_path [in] 文件路径
* @return 返回xml文件内容
*/
std::string read_xml_from_file(const char *file_path)
{
    // 遇到空格就歇逼了
    //std::string str;
    //std::ifstream in(file_path);
    //in >> str;
    //std::cout << str << std::endl;
    //in.close();
    
    std::ifstream ifs(file_path);
    std::string content((std::istreambuf_iterator<char>(ifs)),
                 (std::istreambuf_iterator<char>()));
    std::cout << content << std::endl;
    ifs.close();
    
    std::ifstream t(file_path); 
    std::stringstream buffer;  
    buffer << t.rdbuf();  
    std::string contents(buffer.str());
    std::cout << contents << std::endl;
    t.close();
    return content;
}

void parse_confxml(const char *confxml)
{
    char *policies = const_cast<char *>(confxml);
    
    xml_document<> doc;
    doc.parse<0>(policies);

    xml_node<> *root_node = doc.first_node();
    std::cout << (root_node->name()) << std::endl;
    root_node = root_node->first_node("RemoteApp");
    root_node = root_node->first_node("USBDeviceMap");
    xml_node<> *node = root_node->first_node("WhiteList");
    for(rapidxml::xml_node<> *iter = node->first_node("Dev"); iter != NULL; iter = iter->next_sibling()) {
        // name() value()返回的字符串不会去掉首尾的空白字符
        rapidxml::xml_attribute<char> *vpid = iter->first_attribute("ID");
        rapidxml::xml_attribute<char> *desc = iter->first_attribute("Desc");
        std::cout << vpid->value() << ":" << desc->value() << std::endl;
    }

    std::ofstream out("test.xml");//ofstream 默认时，假设文件存在则会覆盖原来的内容，不存在则会新建
    out << doc;//doc 这样输出时在目标文件里不会有xml 头信息---<?xml version='1.0' encoding='utf-8' >
    out.close();
    return;
}

int main(int argc, char *argv[])
{
    const char *file_path = "config.xml";
    (void)create_usb_list_xml(file_path);
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
