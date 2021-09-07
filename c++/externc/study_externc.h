/**
 * 文 件 名: study_externc.h
 * 文件描述: json文件解析接口
 * 作    者: HJ
 * 创建日期: 2021.08.23
 * 修改日期：2021.08.23
 *
 * Copyright (c) 2021 HJ. All rights reserved.
 */

#pragma once

#include <stdio.h>
#include <string.h>
#include <vector>
#include <iostream>

#ifdef __cplusplus
extern "C" {
#endif

// json文件数据结构体
struct udev_info {
    std::string vid;     // 厂商id
    std::string pid;     // 产品id
    std::string rev;     // 版本
    std::string man_str; // 厂商字符串描述符
    std::string pro_str; // 产品字符串描述符
};

typedef udev_info JSON_DATA_STRUCT;

int main(int argc, char **argv);

#ifdef __cplusplus
}
#endif
