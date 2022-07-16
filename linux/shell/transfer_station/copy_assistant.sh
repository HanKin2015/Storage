#!/bin/bash
#
# 文 件 名: copy_assistant.sh
# 文件描述: 拷贝助手，使用expect命令进行免密scp拷贝，解决无法安装expect命令服务器的问题
# 注    意: 需要安装expect库
# 作    者: HanKin
# 创建日期: 2022.06.16
# 修改日期：2022.06.18
# 
# Copyright (c) 2022 HanKin. All rights reserved.
#

# 源地址、用户名、密码
SOURCE_IP='1.7.9.254'
SOURCE_USER='root'
SOURCE_PWD='hankin'

# 目标地址、用户名、密码
TARGET_IP='12.2.16.140'
TARGET_USER='root'
TARGET_PWD='hankin@123'

# 批量拷贝二进制文件到同一个目录
SOURCE_BINARY_FILES_PATH=(
    #"/root/hejian/linux-client/src/client/client"
    "/root/hejian/linux-client/src/session/output/session"
    #"/root/hejian/linux-client/src/session/spice-0.12.5/session"
)

# 批量拷贝执行库文件到同一个目录
SOURCE_LIBARY_FILES_PATH=(
    "/root/hejian/linux-client/src/usbmagic/libusbmagic/libusbmagic.so"
    "/root/hejian/linux-client/src/usbip/libusbip/libusbip.so"
    "/root/hejian/linux-client/src/usbmagic/libs/libevent/build/lib/libevent-2.1.so.7"
)

for SOURCE_BINARY_FILE_PATH in ${SOURCE_BINARY_FILES_PATH[*]}
do
    SOURCE_FILE_NAME=`echo ${SOURCE_BINARY_FILE_PATH} | awk -F'/' '{print $NF}'`
    
    # 拷贝到本地
    expect -c "
    spawn scp ${SOURCE_USER}@${SOURCE_IP}:${SOURCE_BINARY_FILE_PATH} .
    expect \"password:\"
    send \"${SOURCE_PWD}\r\"
    expect eof
    "

    echo "md5: `md5sum ${SOURCE_FILE_NAME}`"

    # 拷贝到测试机
    expect -c "
    spawn scp ${SOURCE_FILE_NAME} ${TARGET_USER}@${TARGET_IP}:/usr/local/hankin/client/bin/
    expect \"password:\"
    send \"${TARGET_PWD}\r\"
    expect eof
    "

    echo ''
done

for SOURCE_LIBARY_FILE_PATH in ${SOURCE_LIBARY_FILES_PATH[*]}
do
    SOURCE_FILE_NAME=`echo ${SOURCE_LIBARY_FILE_PATH} | awk -F'/' '{print $NF}'`
    
    # 拷贝到本地
    expect -c "
    spawn scp ${SOURCE_USER}@${SOURCE_IP}:${SOURCE_LIBARY_FILE_PATH} .
    expect \"password:\"
    send \"${SOURCE_PWD}\r\"
    expect eof
    "

    echo "md5: `md5sum ${SOURCE_FILE_NAME}`"

    # 拷贝到测试机
    expect -c "
    spawn scp ${SOURCE_FILE_NAME} ${TARGET_USER}@${TARGET_IP}:/usr/local/hankin/client/lib/
    expect \"password:\"
    send \"${TARGET_PWD}\r\"
    expect eof
    "

    echo ''
done

echo "scp done"