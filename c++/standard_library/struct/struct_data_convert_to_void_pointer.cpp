/*******************************************************************************
* 文 件 名: struct_data_convert_to_void_pointer.cpp
* 文件描述: 结构体数据转换为void指针进行数据隐藏
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.06.20
* 修改日期：2025.06.20
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <functional>

struct AutomapConf {
    bool starting_automap; 
    bool running_automap; 
};

void test(const char *user_id, int opt_type, void *conf)
{
    // 使用lambda表达式打印
    std::function<void()> func = [user_id, opt_type, conf]() {
        AutomapConf *automap_conf = (AutomapConf *)conf;
        printf("lambda query %d %d\n", automap_conf->starting_automap, automap_conf->running_automap);
    };
    func();
    
    // 查询是否正常传递
    AutomapConf *automap_conf = (AutomapConf *)conf;
    printf("query %d %d\n", automap_conf->starting_automap, automap_conf->running_automap);
    
    // 是否更改源数据
    AutomapConf am_conf = {true, true};
    *automap_conf = am_conf;
    return;
}

int main(int argc, const char **args)
{
    if (argc < 3) {
        throw std::runtime_error("need more parameters");
    }
    bool starting_automap = (strncmp(args[1], "true", strlen("true")) == 0);
    bool running_automap = (strncmp(args[2], "true", strlen("true")) == 0);
    printf("input %d %d\n", starting_automap, running_automap);
    
    AutomapConf automap_conf = {starting_automap, running_automap};

    test("defaule", 2, &automap_conf);
    
    printf("modify %d %d\n", automap_conf.starting_automap, automap_conf.running_automap);
    return 0;
}
