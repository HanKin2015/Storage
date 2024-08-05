#!/bin/bash
#
# 文 件 名: pid_example.sh
# 文件描述: PID文件（Process ID file）是一种用于进程间通信和同步的简单机制。它通常用于记录正在运行的进程的进程ID（PID），以便其他进程可以查找和与之通信
# 作    者: HanKin
# 创建日期: 2024.08.05
# 修改日期：2024.08.05
# 
# Copyright (c) 2024 HanKin. All rights reserved.
#

PID_FILE="/run/pid_example.pid"

create_pid_file() {
    echo $$ > "$PID_FILE"
}

remove_pid_file() {
    if [ -f "$PID_FILE" ]; then
        rm "$PID_FILE"
    fi
}

process() {
    create_pid_file
    echo "Process started"
    while true; do
        sleep 1
    done
}

judge() {
    if [ -f "$PID_FILE" ]; then
        pid=$(cat "$PID_FILE")
        echo "found Process with PID: $pid, will kill it"
        kill -SIGUSR1 "$pid"
    fi
}

# 前置判断检查
judge

# 启动进程
process

# 清理工作
remove_pid_file
