#!/bin/bash
#
# 文 件 名: pgrep_example.sh
# 文件描述: 
# 作    者: HanKin
# 创建日期: 2024.08.05
# 修改日期：2024.08.05
# 
# Copyright (c) 2024 HanKin. All rights reserved.
#

process() {
    echo "Process started"
    while true; do
        sleep 1
    done
}

# 基本上满足需求，但有一个bug就是等待重试的时候会把后面运行的进程一并杀死
is_running() {
    local running_status
    local wait_times
    wait_times=0
    # 获取当前脚本的文件名
    filename=$(basename "$0")
    is_running_count=$(pgrep -c ${filename})
    echo "${filename} is_running_count = ${is_running_count}"
    while [ "$is_running_count" -gt 1 ] # 自身本来就会有一个进程
    do
        wait_times=$((wait_times+1))
        sleep 2
        is_running_count=$(pgrep -c ${filename})
        # 避免脚本长时间阻塞。
        if [ "${wait_times}" -gt 2 ]
        then
            echo "wait ${filename} runnig too long, will kill them"
            # 太暴力了，会把自己给杀死(注意有些进程不使用SIGKILL信号杀不死)
            #pgrep ${filename} | xargs kill -SIGKILL
            #pgrep ${filename} | xargs -I {} kill -SIGKILL {}
            pgrep ${filename} | grep -v $$ | xargs kill -SIGKILL
            wait_times=0
        fi
    done
}

# 前置判断检查
is_running

# 启动进程
process
