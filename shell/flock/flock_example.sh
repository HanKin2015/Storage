#!/bin/bash
#
# 文 件 名: flock_example.sh
# 文件描述: 当前文件需要进入后台执行，如使用&或者nohup命令
# 备    注: exec 是一个Shell内建命令，用于执行文件重定向和文件描述符操作
# 作    者: HanKin
# 创建日期: 2024.08.03
# 修改日期：2024.08.03
# 
# Copyright (c) 2024 HanKin. All rights reserved.
#

LOCK_FILE="/run/lock/flock_example.lock"

# <> 是文件描述符操作符，用于将文件描述符与文件进行读写操作
exec 200<>$LOCK_FILE
flock -n 200 || {
    echo "flock failed{${LOCK_FILE}, maybe another user is doing the same thing，please wait.."
    flock 200
    # 获取锁之后立即关闭文件描述符200
    exec 200>&-
}

# 解锁, 如果不手动解锁，则进程结束后，自动解锁
unlock()
{
    exec 200<>${LOCK_FILE}
    flock -u 200
}

for i in {1..10}
do
    # sleep 命令接受的参数可以是一个整数或带有时间单位的字符串
    sleep 1s
    echo ${i}
done

echo "done"

# 删除锁文件(这一步是错误的，会导致后面并发，虽然lock文件依然存在，这个暂时没有办法避免)
#rm "$LOCKFILE"