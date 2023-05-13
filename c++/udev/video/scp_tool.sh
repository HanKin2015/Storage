#!/bin/bash
#
# 文 件 名: scp_tool.sh
# 文件描述: 文件中转助手或者拷贝助手，使用expect命令进行免密scp拷贝
# 注    意: 需要安装expect库
# 作    者: HanKin
# 创建日期: 2023.05.13
# 修改日期：2023.05.13
#
# Copyright (c) 2023 HanKin. All rights reserved.
#

# 目标地址、用户名、密码
TARGET_IP='12.12.16.81'
TARGET_PORT=22
TARGET_USER='root'
TARGET_PWD='123456'
SOURCE_FILE_NAME='a.out'
TARGET_FILES_PATH='/home/'

expect -c "
spawn scp -P ${TARGET_PORT} ${SOURCE_FILE_NAME} ${TARGET_USER}@${TARGET_IP}:${TARGET_FILES_PATH}
expect \"password:\"
send \"${TARGET_PWD}\r\"
expect eof
"

echo "scp done"
