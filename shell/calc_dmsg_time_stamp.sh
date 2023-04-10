#!/bin/bash

# 获取系统启动时间
BOOT_TIME=$(date -d "$(uptime -s)" +%s)

# 将 dmesg 中的时间戳转换为日期时间
dmesg | awk '{print $1" "$2}' | while read timestamp; do
    # 提取秒数和纳秒数
    sec=$(echo $timestamp | cut -d '.' -f 1)
    nsec=$(echo $timestamp | cut -d '.' -f 2)

    # 计算日期时间
    date_time=$(date -d "@$((BOOT_TIME + sec))" "+%Y-%m-%d %H:%M:%S")
    printf "%s.%09d %s\n" "$date_time" "$nsec" "$(echo $timestamp | cut -d ' ' -f 3-)"
done
