# 使用开源的rapidxml和rapidjson库开发

## 1、rapidxml库存在问题
开源的rapidxml_print.hpp文件需要修改，直接编译会报错函数未声明使用。
```
In file included from rapidxml_example.cpp:14:0:
rapidxml/rapidxml_print.hpp: In instantiation of ‘OutIt rapidxml::internal::print_node(OutIt, const rapidxml::xml_node<Ch>*, int, int) [with OutIt = std::back_insert_iterator<std::__cxx11::basic_string<char> >; Ch = char]’:
rapidxml/rapidxml_print.hpp:390:36:   required from ‘OutIt rapidxml::print(OutIt, const rapidxml::xml_node<Ch>&, int) [with OutIt = std::back_insert_iterator<std::__cxx11::basic_string<char> >; Ch = char]’
rapidxml_example.cpp:43:50:   required from here
rapidxml/rapidxml_print.hpp:115:37: error: ‘print_children’ was not declared in this scope, and no declarations were found by argument-dependent lookup at the point of instantiation [-fpermissive]
                 out = print_children(out, node, flags, indent);
                                     ^
rapidxml/rapidxml_print.hpp:169:22: note: ‘template<class OutIt, class Ch> OutIt rapidxml::internal::print_children(OutIt, const rapidxml::xml_node<Ch>*, int, int)’ declared here, later in the translation unit
         inline OutIt print_children(OutIt out, const xml_node<Ch> *node, int flags, int indent)
                      ^
rapidxml/rapidxml_print.hpp:120:41: error: ‘print_element_node’ was not declared in this scope, and no declarations were found by argument-dependent lookup at the point of instantiation [-fpermissive]
                 out = print_element_node(out, node, flags, indent);
                                         ^
```
调整函数使用顺序即可。

## 2、两者结合使用效果
运行结果：
```
[root@ubuntu0006:/media/hankin/vdb/TransferStation/rapid] #./a.out
1234:4321 keyborad
1bC4:4321 ukey
AF34:4Ym1 iphone
af34:ge21 mouce
GTFD:dser display
{"policies":{"white_list":[{"index":0,"vid":"1234","pid":"4321","desc":"keyborad"},{"index":1,"vid":"1bC4","pid":"4321","desc":"ukey"},{"index":2,"vid":"AF34","pid":"4Ym1","desc":"iphone"}],"black_list":[{"index":0,"vid":"af34","pid":"ge21","desc":"mouce"},{"index":1,"vid":"GTFD","pid":"dser","desc":"display"}]}}
```

## 3、rapidjson存储直接是浅拷贝
```
错误的演示：
json.AddMember("vid", rapidjson::StringRef(vid.c_str()), allocator);
json.AddMember("pid", rapidjson::StringRef(pid.c_str()), allocator);
json.AddMember("desc", rapidjson::StringRef(infos[i].desc), allocator);
输出结果会出现莫名其妙的乱码。

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
```