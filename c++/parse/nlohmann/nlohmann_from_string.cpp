/*******************************************************************************
* 文 件 名: nlohmann_from_string.cpp
* 文件描述: 从字符串中转换json
* 备    注: 数组，列表
* 作    者: HanKin
* 创建日期: 2025.06.19
* 修改日期：2025.06.19
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
#include <iostream>
#include <nlohmann/json.hpp>
#include <cstring>
#include <list>

#define JSON_DUMP_FORMAT_UTF8_REPLACE(_json) \
    ((_json).dump(4, ' ', false, nlohmann::json::error_handler_t::replace))
#define USB_DEVICES "devices"
#define USB_DEVICE_NAME "name"
#define USB_DEVICE_VID "vid"
#define USB_DEVICE_PID "pid"
#define USB_DEVICE_ID "id"
#define USB_DEVICE_MAP_ALLOWED_SESSION_IDS "map_allowed_session_ids"
#define USB_DEVICE_MAPPED_SESSION_ID "mapped_session_id"
#define USB_DEVICE_MAP_STATUS "map_status"

int main()
{
    std::string infoString(R"({"devices":[{"bind_target_id":"","errmsg":"","errno":0,"id":1793,"map_allowed_session_ids":["4", "123", "1"],"map_status":3,"mapped_session_id":"4","name":"OnlyDisk","pid":14081,"vid":3544},{"bind_target_id":"","errmsg":"","errno":0,"id":66561,"map_allowed_session_ids":[],"map_status":0,"name":"USB 10/100/1000 LAN","pid":33107,"vid":3034},{"bind_target_id":"","errmsg":"","errno":0,"id":67585,"map_allowed_session_ids":[],"map_status":0,"name":"USB Keyboard","pid":8484,"vid":6700},{"bind_target_id":"","errmsg":"","errno":0,"id":133121,"map_allowed_session_ids":[],"map_status":0,"name":"Gaming Mouse","pid":9522,"vid":2362}],"sessions":[{"id":"4","support_map_bind":true}]})");
    size_t length = infoString.length();

	nlohmann::json mapInfo;
	try {
		mapInfo = nlohmann::json::parse(infoString.data(), infoString.data() + length);
        nlohmann::json devices = mapInfo[USB_DEVICES].get<nlohmann::json>();
        std::string str = JSON_DUMP_FORMAT_UTF8_REPLACE(devices);
        printf("%s\n", str.c_str());

        printf("there are %d devices\n", devices.size());
        for (const auto& item : devices) {
            printf("pid: %04x\n", item[USB_DEVICE_PID].get<int>());
            if (item.is_object()) {
                printf("name: %s\n", item[USB_DEVICE_NAME].get<std::string>().data());
                printf("pid: %04x\n", item[USB_DEVICE_PID].get<int>());
                printf("size: %d\n", item[USB_DEVICE_MAP_ALLOWED_SESSION_IDS].size());
            } else {
                printf("Item is not an object\n");
            }
        }
	} catch (nlohmann::json::parse_error &e) {
        printf("json parse error, message:%s, eid=%d, byte position:%zu\n",
            e.what(), e.id, e.byte);
        return -1;
    } catch (const std::exception &excep) {
        printf("parse json failed, %s\n", excep.what());
        return -1;
    }
    return 0;
}
/*

*/
