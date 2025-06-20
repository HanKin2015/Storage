/*******************************************************************************
* 文 件 名: nlohmann_example4.cpp
* 文件描述: 但是nlohmann 3.11.0在项目中无法使用，只能使用2.1.1版本
* 备    注: 
* 作    者: HanKin
* 创建日期: 2025.06.19
* 修改日期：2025.06.19
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include "json.hpp"
#include <cstring>

int main()
{
    std::string infoString(R"({"devices":[{"bind_target_id":"","errmsg":"","errno":0,"id":1793,"map_allowed_session_ids":["4", "123", "1"],"map_status":3,"mapped_session_id":"4","name":"OnlyDisk","pid":14081,"vid":3544},{"bind_target_id":"","errmsg":"","errno":0,"id":66561,"map_allowed_session_ids":[],"map_status":0,"name":"USB 10/100/1000 LAN","pid":33107,"vid":3034},{"bind_target_id":"","errmsg":"","errno":0,"id":67585,"map_allowed_session_ids":[],"map_status":0,"name":"USB Keyboard","pid":8484,"vid":6700},{"bind_target_id":"","errmsg":"","errno":0,"id":133121,"map_allowed_session_ids":[],"map_status":0,"name":"Gaming Mouse","pid":9522,"vid":2362}],"sessions":[{"id":"4","support_map_bind":true}]})");
    size_t length = infoString.length();

	try {
		nlohmann::json mapInfo = nlohmann::json::parse(infoString.data(), infoString.data() + length);
        nlohmann::json devices = mapInfo["devices"].get<nlohmann::json>();
        std::string str = JSON_DUMP_FORMAT_UTF8_REPLACE(devices);
        printf("%s\n", str.c_str());

        for (const auto& item : devices) {
            // is_null()\is_string()\contains()都不行
            if (item.find("mapped_session_id") != item.end()) {
                printf("%s\n", item["mapped_session_id"].get<std::string>().data());
            }
            printf("%llu\n", item["id"].get<uint64_t>());
        }
	} catch (const std::invalid_argument &e) {
        printf("invalid argument, %s\n", e.what());
        return -1;
    } catch (const std::exception &excep) {
        printf("parse json failed, %s\n", excep.what());
        return -1;
    }
    return 0;
}
/*

*/
