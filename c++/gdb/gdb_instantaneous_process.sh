#!/bin/bash
#
# 文 件 名: gdb_instantaneous_process.sh
# 文件描述: gdb调试瞬间一闪而过的进程
# 作    者: HanKin
# 创建日期: 2022.10.11
# 修改日期：2025.03.04
# 
# Copyright (c) 2025 HanKin. All rights reserved.
#

# 检查 gdb 是否已安装
if command -v gdb >/dev/null 2>&1; then
    echo "gdb 已安装"
else
    echo "gdb 未安装，正在安装..."

    # 检测操作系统类型
    if [ -f /etc/debian_version ]; then
        # Debian/Ubuntu 系统
        sudo apt update
        sudo apt install -y gdb
    elif [ -f /etc/redhat-release ]; then
        # Red Hat/CentOS 系统
        sudo yum install -y gdb
    else
        echo "不支持的操作系统，请手动安装 gdb"
        exit 1
    fi

    echo "gdb 安装完成"
fi

PROCESS_ABSPATH=$1
PROCESS_NAME=$(basename "${PROCESS_ABSPATH}")
while true
do
    pid=`pidof ${PROCESS_NAME}`
    if [ -n "${pid}" ]
    then
        echo ${pid}
        gdb ${PROCESS_ABSPATH} -p ${pid}
        break
    else
        echo "there is not a ${PROCESS_NAME} process"
    fi
done