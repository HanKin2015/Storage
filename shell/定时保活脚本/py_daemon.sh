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

# python脚本路径
PYTHON_SCRIPT_NAME='k.py'
PYTHON_SCRIPT_PATH="/root/cmake/${PYTHON_SCRIPT_NAME}"

# 启动python脚本
start_python_sctipt()
{
    nohup python ${PYTHON_SCRIPT_PATH} &
}

# 获取进程ID
get_pid()
{
    echo $(ps aux | grep ${PYTHON_SCRIPT_NAME} | grep -v grep | awk '{print $2}')
}

# 检查并重启进程
check_and_restart()
{
    local pid=$(get_pid)
    echo "${PYTHON_SCRIPT_PATH} file start pid is ${pid}"

    if [ -z "$pid" ]; then
        echo "Process not running. Starting process..."
        start_python_sctipt
        return
    fi

    # 获取VIRT和句柄数量
    local virt=$(ps -o vsize= -p $pid)
    local handles=$(ls /proc/$pid/fd | wc -l)

    echo "VIRT: $virt KB, Handles: $handles"

    # 检查条件（如果VIRT超过了5g或者句柄数量超过了600就杀死重新拉起）
    if [ "$virt" -gt $((5 * 1024 * 1024)) ] || [ "$handles" -gt 600 ]; then
        echo "Conditions met. Restarting process..."
        kill -9 $pid
        start_python_sctipt
        local pid=$(get_pid)
        echo "${PYTHON_SCRIPT_PATH} file restart pid is ${pid}"
    else
        echo "Process is running within limits."
    fi
}

# 执行检查和重启
check_and_restart
