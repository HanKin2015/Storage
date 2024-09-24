/**
* 文 件 名: reflex_map.cpp
* 文件描述: C++通过map实现反射（表示demo看不懂）
* 作    者: HanKin
* 创建日期: 2022.07.07
* 修改日期：2022.07.07
*
* Copyright (c) 2022 HanKin. All rights reserved.
*/

#include <iostream>
#include <string>
#include <map>
using namespace std;
 
#define BASE_CLASS Test
#define GLOBAL_FUN_MAP FunMap<BASE_CLASS>::get_fun_map()
#define DEFINE_CLASS(class_name, fun_name) \
    class_name(std::string) \
    {\
        GLOBAL_FUN_MAP.regist(#fun_name, class_name::fun_name);\
    }\
    class_name(){}\
    static class_name class_name##_;\
    static BASE_CLASS* fun_name()\
    {\
        return new class_name;\
    }
#define REGIST_CLASS(class_name) \
    class_name class_name::class_name##_(#class_name);
 
template <class T>
class FunMap
{
    typedef T* (*FUN)(void);
    map<std::string, FUN> fun_map_;
    public:
    void regist(string fun_name, FUN fun)
    {
        fun_map_[fun_name] = fun;  
    }
 
    T* get(const string fun_name)
    {
        if (fun_map_.end() != fun_map_.find(fun_name))
        {
            return fun_map_[fun_name](); 
        }
        else
        {
            return NULL;
        }
    }
 
    static FunMap<T>& get_fun_map()
    {
        static FunMap<T> fun_map;
        return fun_map;
    }
};
 
class Test
{};
 
class Test1 : public Test
{
public:
    DEFINE_CLASS(Test1, test1)  // 第一个参数为类名，第二个参数为字符串名
};
 
class Test2 : public Test
{
public:
    DEFINE_CLASS(Test2, test2)
};

// 参数为类名
REGIST_CLASS(Test1)
REGIST_CLASS(Test2)
 
int main()
{
    GLOBAL_FUN_MAP.get("test1");   
    GLOBAL_FUN_MAP.get("test2");   
    GLOBAL_FUN_MAP.get("11111111");
}
/*
虽然看不懂，但是能运行，可是没有任何输出
*/