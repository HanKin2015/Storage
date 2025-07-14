#ifndef STRING_UTILS_H
#define STRING_UTILS_H

#include <string>
#include <vector>

namespace StringUtils {

// 字符串分割函数
std::vector<std::string> split(const std::string& str, char delimiter);

// 字符串修剪函数（去除首尾空格）
std::string trim(const std::string& str);

// 字符串反转函数
std::string reverse(const std::string& str);

} // namespace StringUtils

#endif // STRING_UTILS_H    