#!/bin/bash
#
# 文 件 名: create_coredump.sh
# 文件描述: 此脚本供系统调用，用来生成压缩的coredump(系统自己生成的，是不经过压缩的)
# 备    注: 为了让系统不频繁出core影响系统性能，针对同一进程30min以内不会再次出core
# 作    者: HanKin
# 创建日期: 2024.01.23
# 修改日期：2024.01.23
#           zhangsan@2023.11.14: 新增修改历史模板参考
#           lisi@2024-03-14: 另外一种格式
# 
# Copyright (c) 2023 HanKin. All rights reserved.
#
program=$1
new_core_timestamp=$6
last_core_file=$(ls -1t /var/log/dump/*-${program}-* 2>/dev/null |head -1)
if [ -z "${last_core_file}" ];then
    last_core_timestamp=0
else
    last_core_timestamp=`stat -c %Y ${last_core_file}`
fi

if [ $((last_core_timestamp+1800)) -lt "${new_core_timestamp}" ] ; then
    exec /bin/gzip -f - >"/var/log/dump/core-$1-sig$2-user$3-group$4-pid$5-time$6.gz"
fi