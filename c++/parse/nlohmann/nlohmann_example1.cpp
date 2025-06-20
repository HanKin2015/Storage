/*******************************************************************************
* 文 件 名: nlohmann_example1.cpp
* 文件描述: 只需要一个头文件就能使用？答案是的
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
#define JSON_DUMP_FORMAT_UTF8_REPLACE(_json) \
    ((_json).dump(4, ' ', false, nlohmann::json::error_handler_t::replace))

int main()
{
    std::string infoString(R"({"devices":[{"bind_target_id":"","errmsg":"","errno":0,"id":1793,"map_allowed_session_ids":["4", "123", "1"],"map_status":3,"mapped_session_id":"4","name":"OnlyDisk","pid":14081,"vid":3544},{"bind_target_id":"","errmsg":"","errno":0,"id":66561,"map_allowed_session_ids":[],"map_status":0,"name":"USB 10/100/1000 LAN","pid":33107,"vid":3034},{"bind_target_id":"","errmsg":"","errno":0,"id":67585,"map_allowed_session_ids":[],"map_status":0,"name":"USB Keyboard","pid":8484,"vid":6700},{"bind_target_id":"","errmsg":"","errno":0,"id":133121,"map_allowed_session_ids":[],"map_status":0,"name":"Gaming Mouse","pid":9522,"vid":2362}],"sessions":[{"id":"4","support_map_bind":true}]})");
    size_t length = infoString.length();

	try {
		nlohmann::json mapInfo = nlohmann::json::parse(infoString.data(), infoString.data() + length);
        nlohmann::json devices = mapInfo["devices"].get<nlohmann::json>();
        std::string str = JSON_DUMP_FORMAT_UTF8_REPLACE(devices);
        printf("%s\n", str.c_str());
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
