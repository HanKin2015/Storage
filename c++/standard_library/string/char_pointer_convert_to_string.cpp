/**
* 文 件 名: char_pointer_convert_to_string.cpp
* 文件描述: char指针转string指定长度
* 作    者: HanKin
* 创建日期: 2024.08.14
* 修改日期：2024.08.14
*
* Copyright (c) 2024 HanKin. All rights reserved.
*/
#include <iostream>
#include <cstdio>
#include <cstring>

int main()
{
    char str[] = "123456";
    int len = strlen(str);
    std::cout << len << std::endl;  // 6
    std::string ret = std::string((char *)str, len);
    std::cout << ret << std::endl;  // 123456
    return 0;
}
