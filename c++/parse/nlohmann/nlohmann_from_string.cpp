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
#define USB_DEVICE_SESSIONS "sessions"

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
        std::string session_id = "";
        nlohmann::json sessions = mapInfo[USB_DEVICE_SESSIONS].get<nlohmann::json>();
        if (sessions.size() > 0) {
            // 当前只支持单会话，取第一个session即可
            session_id = sessions[0][USB_DEVICE_ID].get<std::string>();
        }

        printf("there are %d devices, session id %s\n", devices.size(), session_id.data());
        for (const auto& item : devices) {
            printf("pid: %04x\n", item[USB_DEVICE_PID].get<int>());
            if (item.is_object()) {
                printf("name: %s\n", item[USB_DEVICE_NAME].get<std::string>().data());
                printf("pid: %04x\n", item[USB_DEVICE_PID].get<int>());
                printf("size: %d\n", item[USB_DEVICE_MAP_ALLOWED_SESSION_IDS].size());

                nlohmann::json map_allowed_session_ids = item[USB_DEVICE_MAP_ALLOWED_SESSION_IDS].get<nlohmann::json>();
                // 将 session_id 转换为 JSON 字符串
                nlohmann::json session_id_json = session_id;
                if (map_allowed_session_ids.contains(session_id_json)) {
                    printf("allow map\n");
                } else {
                    printf("not allow map\n");
                }

                // 使用 std::find 查找元素
                auto it = std::find(map_allowed_session_ids.begin(), map_allowed_session_ids.end(), session_id);
                if (it != map_allowed_session_ids.end()) {
                    printf("allow map\n");
                } else {
                    printf("not allow map\n");
                }

                bool isAllowed = false;
                for (const auto& allowed_id : map_allowed_session_ids) {
                    if (allowed_id.get<std::string>() == session_id) {
                        isAllowed = true;
                        break;
                    }
                }
                if (isAllowed) {
                    printf("allow map\n\n");
                } else {
                    printf("not allow map\n\n");
                }
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
[root@ubuntu0006:~] #./a.out
[
    {
        "bind_target_id": "",
        "errmsg": "",
        "errno": 0,
        "id": 1793,
        "map_allowed_session_ids": [
            "4",
            "123",
            "1"
        ],
        "map_status": 3,
        "mapped_session_id": "4",
        "name": "OnlyDisk",
        "pid": 14081,
        "vid": 3544
    },
    {
        "bind_target_id": "",
        "errmsg": "",
        "errno": 0,
        "id": 66561,
        "map_allowed_session_ids": [],
        "map_status": 0,
        "name": "USB 10/100/1000 LAN",
        "pid": 33107,
        "vid": 3034
    },
    {
        "bind_target_id": "",
        "errmsg": "",
        "errno": 0,
        "id": 67585,
        "map_allowed_session_ids": [],
        "map_status": 0,
        "name": "USB Keyboard",
        "pid": 8484,
        "vid": 6700
    },
    {
        "bind_target_id": "",
        "errmsg": "",
        "errno": 0,
        "id": 133121,
        "map_allowed_session_ids": [],
        "map_status": 0,
        "name": "Gaming Mouse",
        "pid": 9522,
        "vid": 2362
    }
]
there are 4 devices, session id 4
pid: 3701
name: OnlyDisk
pid: 3701
size: 3
not allow map
allow map
allow map

pid: 8153
name: USB 10/100/1000 LAN
pid: 8153
size: 0
not allow map
not allow map
not allow map

pid: 2124
name: USB Keyboard
pid: 2124
size: 0
not allow map
not allow map
not allow map

pid: 2532
name: Gaming Mouse
pid: 2532
size: 0
not allow map
not allow map
not allow map
*/
