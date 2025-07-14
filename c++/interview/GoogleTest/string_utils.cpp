#include "string_utils.h"
#include <sstream>
#include <algorithm>

namespace StringUtils {

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    
    return tokens;
}

std::string trim(const std::string& str) {
    std::string result = str;
    
    // 去除前导空格
    result.erase(result.begin(), 
                 std::find_if(result.begin(), result.end(), 
                             [](unsigned char c) { return !std::isspace(c); }));
    
    // 去除尾随空格
    result.erase(std::find_if(result.rbegin(), result.rend(), 
                             [](unsigned char c) { return !std::isspace(c); }).base(), 
                 result.end());
    
    return result;
}

std::string reverse(const std::string& str) {
    return std::string(str.rbegin(), str.rend());
}

} // namespace StringUtils    