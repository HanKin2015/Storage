#!/bin/bash
#
# 文 件 名: file_transfer_assistant.sh
# 文件描述: 文件中转助手或者拷贝助手，使用expect命令进行免密scp拷贝，解决无法安装expect命令服务器的问题，可能两个服务器之间无法进行之间传输问题
# 注    意: 需要安装expect库
# 作    者: HanKin
# 创建日期: 2022.11.28
# 修改日期：2022.11.28
# 
# Copyright (c) 2022 HanKin. All rights reserved.
#

# 源地址、用户名、密码
SOURCE_IP='1.7.9.254'
SOURCE_PORT=22
SOURCE_USER='root'
SOURCE_PWD='hankin'

# 目标地址、用户名、密码
TARGET_IP='12.2.16.140'
TARGET_PORT=22
TARGET_USER='root'
TARGET_PWD='hankin@123'

# 源文件路径
SOURCE_FILES_PATH=(
    #'/root/hejian/linux-client/src/client/client'
    '/root/hejian/linux-client/src/session/output/session'
    #'/root/hejian/linux-client/src/session/spice-0.12.5/session'
)

# 目标文件路径
TARGET_FILES_PATH='/etc/share/'

# ---------------- 以上内容需要进行调整修改 ----------------

for SOURCE_BINARY_FILE_PATH in ${SOURCE_FILES_PATH[*]}
do
    SOURCE_FILE_NAME=`echo ${SOURCE_BINARY_FILE_PATH} | awk -F'/' '{print $NF}'`
    
    # 拷贝到本地
    expect -c "
    spawn scp -P ${SOURCE_PORT} ${SOURCE_USER}@${SOURCE_IP}:${SOURCE_BINARY_FILE_PATH} .
    expect \"password:\"
    send \"${SOURCE_PWD}\r\"
    expect eof
    "

    echo "MD5: `md5sum ${SOURCE_FILE_NAME}`"

    # 拷贝到测试机
    expect -c "
    spawn scp -P ${TARGET_PORT} ${SOURCE_FILE_NAME} ${TARGET_USER}@${TARGET_IP}:${TARGET_FILES_PATH}
    expect \"password:\"
    send \"${TARGET_PWD}\r\"
    expect eof
    "

    echo ''
done

echo "scp done"