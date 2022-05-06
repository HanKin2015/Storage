#!/bin/bash
#
# 学习字符串截断、正则表达式
#
# 用法: ./stress_IO.sh
#
# Author: hejian
# Date  : 2021.04.07
#
# Copyright (c) 2021 HanKin. All rights reserved.
#

FULLVERSION="HANKIN5.4.10"

# 版本号，R版本中间必须没有空格
FULLVERSION="HJ5.4.10"
LANG=zh_CN
VERSION=$(echo "${FULLVERSION}" | tr -d '. ')

VERSION_STRING=$(echo $VERSION | tr -d "a-zA-Z")
VERSION_NUM_CNT=$(echo "${VERSION_STRING}" | wc -L)
if [ "${VERSION_NUM_CNT}" -eq 2 ]; then
        VERSION_STRING="${VERSION_STRING}"0
fi
if [ "${VERSION_NUM_CNT}" -lt 2 ]; then
    echo "ERROR" "version: $VERSION"
    exit 1
fi
VERSION_BASE="${VERSION_STRING:0:1}"."${VERSION_STRING:1:1}"."${VERSION_STRING:2:2}"

echo $VERSION_BASE
