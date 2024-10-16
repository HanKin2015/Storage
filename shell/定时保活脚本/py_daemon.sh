#!/bin/bash
#
# 文 件 名: py_daemon.sh
# 文件描述: python脚本守护进程
# 备    注: python脚本存在内存泄露，需要时刻监督keep-alive
# 作    者: HanKin
# 创建日期: 2024.10.12
# 修改日期：2024.10.12
#           zhangsan@2023.11.14: 新增修改历史模板参考
#           lisi@2024-03-14: 另外一种格式
# 
# Copyright (c) 2024 HanKin. All rights reserved.
#
#!/bin/bash

# 获取进程ID
get_pid() {
    echo $(ps aux | grep 'k.py' | grep -v grep | awk '{print $2}')
}

# 检查并重启进程
check_and_restart() {
    local pid=$(get_pid)

    if [ -z "$pid" ]; then
        echo "Process not running. Starting process..."
        nohup python t.py &
        return
    fi

    # 获取VIRT和句柄数量
    local virt=$(ps -o vsize= -p $pid)
    local handles=$(ls /proc/$pid/fd | wc -l)

    echo "VIRT: $virt KB, Handles: $handles"

    # 检查条件
    if [ "$virt" -gt $((5 * 1024 * 1024)) ] || [ "$handles" -gt 600 ]; then
        echo "Conditions met. Restarting process..."
        kill -9 $pid
        nohup python t.py &
    else
        echo "Process is running within limits."
    fi
}

# 执行检查和重启
check_and_restart
