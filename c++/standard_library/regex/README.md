# 正则表达式

## 1、std::string仅由字母数字字符（a-z、A-Z、0-9）和下划线（_）组成
```
bool isValidString(const std::string& str) {
    // 定义正则表达式：仅包含字母数字和下划线
    std::regex validPattern("^[a-zA-Z0-9_]+$");
    return std::regex_match(str, validPattern);
}
```



