#!/bin/bash
#
# 编译环境拷贝二进制文件到Linux物理机上面
#
# 用法: ./stress_IO.sh
#
# 使用前注意: 
#   1. 需要安装expect, apt install expect
#   2. 放置在/sf/data/local/hj/目录下
#
# Author: hejian
# Date  : 2021.04.07
#
# Copyright (c) 2021 HanKin. All rights reserved.
#

#FULLVERSION="VDI5.4.2"
FULLVERSION=$1
VERSION=$(echo "${FULLVERSION}" | tr -d '. ')

echo "VERSION: $VERSION"

VERSION_STRING=$(echo $VERSION | awk -F"S|R" '{print $1}' | tr -d "a-zA-Z")
VERSION_NUM_CNT=$(echo "${VERSION_STRING}" | wc -L)
if [ "${VERSION_NUM_CNT}" -eq 2 ]; then
        VERSION_STRING="${VERSION_STRING}"0
fi
if [ "${VERSION_NUM_CNT}" -lt 2 ]; then
    echo "ERROR" "version: $VERSION"
    exit 1
fi

echo "VERSION_STRING: $VERSION_STRING"

VERSION_BASE="${VERSION_STRING:0:1}"."${VERSION_STRING:1:1}"."${VERSION_STRING:2:2}"

echo "VERSION_BASE: $VERSION_BASE"
