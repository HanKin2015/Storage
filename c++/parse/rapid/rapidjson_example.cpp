/**
* 文 件 名: rapidjson_example.cpp
* 文件描述: 学习rapidjson的使用
* 作    者: HanKin
* 创建日期: 2022.06.20
* 修改日期：2022.06.20
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include "rapidjson/writer.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include <iostream>

/**
* @brief  生成复杂的json串
* @note   网上的教程https://blog.csdn.net/yang332233/article/details/119963185
* @param  无
* @return 无
*/
std::string build_json_msg()
{ 
    rapidjson::Document doc;//生成DOM元素
    doc.SetObject();
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();//生成一个分配器

    //构建键值对
    doc.AddMember("name", "jack", allocator);
    doc.AddMember("age", 18, allocator);
    //====构建数组元素====["a","b"]
    rapidjson::Value array_sub(rapidjson::kArrayType);//创建一个数组类型对象
    array_sub.PushBack("a", allocator);
    array_sub.PushBack("b", allocator);
    //================
    doc.AddMember("sub", array_sub, allocator);
    //====构建数组object===[{"a":A,},{}]
    rapidjson::Value array_json(rapidjson::kArrayType);
    rapidjson::Value obj(rapidjson::kObjectType);//每一个数组里面是一个json格式
    obj.AddMember("a", "A", allocator);
    obj.AddMember("b", "B", allocator);
    array_json.PushBack(obj, allocator);

    rapidjson::Value obj1(rapidjson::kObjectType);//每一个数组里面是一个json格式
    obj1.AddMember("c", "C", allocator);
    obj1.AddMember("d", "D", allocator);
    array_json.PushBack(obj1, allocator);
    //array_json.PushBack(obj1,allocator);
    doc.AddMember("elp", array_json, allocator);

    rapidjson::StringBuffer s;
    rapidjson::Writer<rapidjson::StringBuffer> writer(s);
    doc.Accept(writer);

    return std::string(s.GetString());
}
 
int main()
{
    std::string str_json = build_json_msg();
    std::cout << str_json << std::endl;
 
    std::cout << "hello world"  <<std::endl;
    return 0;
}