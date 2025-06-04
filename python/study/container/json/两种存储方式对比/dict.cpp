#include <iostream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp> // 使用 nlohmann/json 库处理 JSON

using json = nlohmann::json;

class VDCManager {
public:
    // 存储 VDC 信息
    std::vector<json> vdc_list;

    // 添加或更新 VDC 和用户信息
    void addOrUpdateVDC(const std::string& vdc, const std::string& user, int starting_automap, int running_automap) {
        // 查找 VDC 是否存在
        auto it = std::find_if(vdc_list.begin(), vdc_list.end(), [&vdc](const json& obj) {
            return obj["vdc"] == vdc;
        });

        if (it == vdc_list.end()) {
            // 如果不存在，创建新的 VDC
            json new_vdc = {
                {"vdc", vdc},
                {"automap", json::array()}
            };
            new_vdc["automap"].push_back({
                {"user", user},
                {"starting_automap", starting_automap},
                {"running_automap", running_automap}
            });
            vdc_list.push_back(new_vdc);
        } else {
            // 如果 VDC 存在，查找用户
            auto& automap = (*it)["automap"];
            auto user_it = std::find_if(automap.begin(), automap.end(), [&user](const json& obj) {
                return obj["user"] == user;
            });

            if (user_it != automap.end()) {
                // 如果用户存在，更新用户信息
                (*user_it)["starting_automap"] = starting_automap;
                (*user_it)["running_automap"] = running_automap;
            } else {
                // 如果用户不存在，添加新的用户信息
                automap.push_back({
                    {"user", user},
                    {"starting_automap", starting_automap},
                    {"running_automap", running_automap}
                });
            }
        }
    }

    // 打印当前 VDC 信息
    void printVDCs() {
        for (const auto& vdc : vdc_list) {
            std::cout << "VDC: " << vdc["vdc"] << std::endl;
            for (const auto& user : vdc["automap"]) {
                std::cout << "  User: " << user["user"] << ", Starting: " << user["starting_automap"] << ", Running: " << user["running_automap"] << std::endl;
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
