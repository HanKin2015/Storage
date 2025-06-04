#include <iostream>
#include <string>
#include <map>
#include <nlohmann/json.hpp> // 使用 nlohmann/json 库处理 JSON

using json = nlohmann::json;

class VDCManager {
public:
    // 存储 VDC 信息
    std::map<std::string, json> vdc_map;

    // 添加或更新 VDC 和用户信息
    void addOrUpdateVDC(const std::string& vdc, const std::string& user, int starting_automap, int running_automap) {
        // 检查 VDC 是否存在
        if (vdc_map.find(vdc) == vdc_map.end()) {
            // 如果不存在，创建新的 VDC
            vdc_map[vdc] = json::object();
        }

        // 检查用户是否存在
        if (vdc_map[vdc].contains(user)) {
            // 如果用户存在，更新用户信息
            vdc_map[vdc][user]["starting_automap"] = starting_automap;
            vdc_map[vdc][user]["running_automap"] = running_automap;
        } else {
            // 如果用户不存在，添加新的用户信息
            vdc_map[vdc][user] = {
                {"starting_automap", starting_automap},
                {"running_automap", running_automap}
            };
        }
    }

    // 打印当前 VDC 信息
    void printVDCs() {
        for (const auto& [vdc, users] : vdc_map) {
            std::cout << "VDC: " << vdc << std::endl;
            for (const auto& [user, info] : users.items()) {
                std::cout << "  User: " << user << ", Starting: " << info["starting_automap"] << ", Running: " << info["running_automap"] << std::endl;
            }
        }
    }
};

int main() {
    VDCManager manager;

    // 添加或更新 VDC 和用户信息
    manager.addOrUpdateVDC("10.57.12.13", "hj", 1, 0);
    manager.addOrUpdateVDC("10.57.12.13", "jh", 1, 1);
    manager.addOrUpdateVDC("10.57.12.14", "hh", 0, 0);
    manager.addOrUpdateVDC("10.57.12.13", "hj", 0, 1); // 更新用户信息

    // 打印当前 VDC 信息
    manager.printVDCs();

    return 0;
}
