/*******************************************************************************
* 文 件 名: nlohmann_example3.cpp
* 文件描述: nlohmann::json的简单应用
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.06.04
* 修改日期：2025.06.04
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <unordered_map>

struct AutomapConf {
    bool starting_automap;
    bool running_automap;
};
#define JSON_KEY_STARTING_AUTOMAP "starting_automap"
#define JSON_KEY_RUNNING_AUTOMAP "running_automap"

/**
 * @brief m_automaps转化成json对象
 *  {
 *  "default:debian":
 *              {
 *                  "starting_automap": 1,
 *                  "running_automap": 1
 *              },
 *  "10.57.12.13:zs": {
 *                  "starting_automap": 1,
 *                  "running_automap": 0
 *              }
 *  }
 * @return nlohmann::json
 */
nlohmann::json to_json()
{
    printf("\n----- %s:%d -----\n", __FUNCTION__, __LINE__);
    nlohmann::json json;

    std::unordered_map<std::string, AutomapConf> automaps;
    automaps["default:debian"] = {.starting_automap = true, .running_automap = true};
    automaps["default:linux"] = {false, false};

    for (const auto& automap : automaps) {
        nlohmann::json obj = {
            {JSON_KEY_STARTING_AUTOMAP, automap.second.starting_automap},
            {JSON_KEY_RUNNING_AUTOMAP, automap.second.running_automap},
        };
        json[automap.first] = obj;
    }

    std::string json_str = json.dump(4, ' ', false, nlohmann::json::error_handler_t::replace);
    printf("json: %s\n", json_str.c_str());
    return json;
}

/**
 * @brief 从json读取数据到m_automaps中
 *  {
 *  "default:debian":
 *              {
 *                  "starting_automap": 1,
 *                  "running_automap": 1
 *              },
 *  "10.57.12.13:zs": {
 *                  "starting_automap": 1,
 *                  "running_automap": 0
 *              }
 *  }
 * @param json
 * @return int
 * @exception 可能抛出json解析错误异常
 */
int from_json(nlohmann::json json)
{
    printf("\n----- %s:%d -----\n", __FUNCTION__, __LINE__);
    std::unordered_map<std::string, AutomapConf> automaps;
    for (const auto& item : json.items()) {
        std::string key = item.key();
        nlohmann::json value = item.value();
        
        if (value.contains(JSON_KEY_STARTING_AUTOMAP) && value.contains(JSON_KEY_RUNNING_AUTOMAP)) {
            AutomapConf conf{value[JSON_KEY_STARTING_AUTOMAP].get<bool>(), value[JSON_KEY_RUNNING_AUTOMAP].get<bool>()};
            automaps[key] = conf;
        } else {
            std::string value_str = value.dump(4, ' ', false, nlohmann::json::error_handler_t::replace);
            printf("key=%s value=%s is invalid\n", key.c_str(), value_str.c_str());
            continue;
        }
    }
    printf("automaps size = %lu\n", automaps.size());
    for (const auto& automap : automaps) {
        printf("%s: %d %d\n", automap.first.c_str(), automap.second.starting_automap, automap.second.running_automap);
    }
    return 0;
}

bool query_json(nlohmann::json json, std::string key)
{
    printf("\n----- %s:%d -----\n", __FUNCTION__, __LINE__);
    if (json.contains(key)) {
        nlohmann::json value = json.at(key);
        std::string value_str = value.dump(4, ' ', false, nlohmann::json::error_handler_t::replace);
        printf("key=%s value=%s\n", key.c_str(), value_str.c_str());
        if (value.contains("starting_automap")) {
            printf("starting_automap = %d\n", value["starting_automap"].get<int>());
        }
        if (value.contains("running_automap")) {
            printf("running_automap = %d\n", value["running_automap"].get<int>());
        }
        return true;
    }
    printf("key=%s is not found\n", key.c_str());
    return false;
}

int main()
{
    nlohmann::json new_json = to_json();
    // 将 JSON 写入文件
    std::ofstream out_file("example.json");
    if (out_file.is_open()) {
        out_file << new_json.dump(4); // 使用 4 个空格缩进格式化输出
        out_file.close();
        std::cout << "JSON 写入文件成功！" << std::endl;
    } else {
        std::cerr << "无法打开文件进行写入！" << std::endl;
    }

    query_json(new_json, "default:debian");
    query_json(new_json, "default:hj");

    std::ifstream in_file("example.json");
    if (in_file.is_open()) {
        nlohmann::json json;
        in_file >> json;   // 读取 JSON 数据
        in_file.close();

        // 输出读取的 JSON
        std::cout << "读取的 JSON 内容：" << std::endl;
        std::cout << json.dump(4) << std::endl; // 使用 4 个空格缩进格式化输出
        from_json(json);
    } else {
        std::cerr << "无法打开文件进行读取！" << std::endl;
    }
    return 0;
}
/*
[root@ubuntu0006:~] #./a.out
读取的 JSON 内容：
{
    "default:debian": {
        "running_automap": 1,
        "starting_automap": 1
    },
    "default:linux": {
        "running_automap": 1,
        "starting_automap": 1
    }
}

----- from_json:62 -----
read item from file. key=default:debian value={
    "running_automap": 1,
    "starting_automap": 1
}
read item from file. key=default:linux value={
    "running_automap": 1,
    "starting_automap": 1
}
automaps size = 2

----- to_json:26 -----
json: {
    "default:debian": {
        "running_automap": 1,
        "starting_automap": 1
    },
    "default:linux": {
        "running_automap": 0,
        "starting_automap": 0
    }
}
JSON 写入文件成功！

----- query_json:78 -----
key=default:debian value={
    "running_automap": 1,
    "starting_automap": 1
}
starting_automap = 1
running_automap = 1

----- query_json:78 -----
key=default:hj is not found
*/
