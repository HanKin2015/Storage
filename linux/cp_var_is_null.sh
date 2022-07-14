#!/bin/bash
#
# 文 件 名: cp_:?_:-.sh
# 文件描述: cp命令居然可以给文件夹重命名，以及:?和:-符号的使用
# 作    者: HanKin
# 创建日期: 2022.07.07
# 修改日期：2022.07.07
# 
# Copyright (c) 2022 HanKin. All rights reserved.
#

cat >&2 <<EOF
[root@ubuntu0006:/media/hankin/vdb/TransferStation/cp] #ll
总用量 20
drwxr-xr-x 5 root root 4096 7月   7 17:46 ./
drwxr-xr-x 5 root root 4096 7月   7 14:58 ../
drwxr-xr-x 5 root root 4096 7月   7 11:25 lib/
drwxr-xr-x 6 root root 4096 7月   7 17:47 usb/
[root@ubuntu0006:/media/hankin/vdb/TransferStation/cp] #ll lib
总用量 20
drwxr-xr-x 5 root root 4096 7月   7 11:25 ./
drwxr-xr-x 5 root root 4096 7月   7 17:46 ../
drwxr-xr-x 2 root root 4096 7月   7 11:25 a/
drwxr-xr-x 2 root root 4096 7月   7 11:25 b/
drwxr-xr-x 2 root root 4096 7月   7 11:25 c/

usb文件夹已存在，拷贝的是lib文件夹
[root@ubuntu0006:/media/hankin/vdb/TransferStation/cp] #cp -arf lib usb
[root@ubuntu0006:/media/hankin/vdb/TransferStation/cp] #ll usb/
总用量 12
drwxr-xr-x 3 root root 4096 7月   7 17:46 ./
drwxr-xr-x 4 root root 4096 7月   7 11:25 ../
drwxr-xr-x 5 root root 4096 7月   7 11:25 lib/

usc文件夹不存在，拷贝的是lib文件夹下的内容，即相当于重命名文件夹
[root@ubuntu0006:/media/hankin/vdb/TransferStation/cp] #cp -arf lib usc
[root@ubuntu0006:/media/hankin/vdb/TransferStation/cp] #ll usc/
总用量 20
drwxr-xr-x 5 root root 4096 7月   7 11:25 ./
drwxr-xr-x 5 root root 4096 7月   7 17:46 ../
drwxr-xr-x 2 root root 4096 7月   7 11:25 a/
drwxr-xr-x 2 root root 4096 7月   7 11:25 b/
drwxr-xr-x 2 root root 4096 7月   7 11:25 c/

usb文件夹已存在，需要这样拷贝
[root@ubuntu0006:/media/hankin/vdb/TransferStation/cp] #cp -arf lib/* usb
[root@ubuntu0006:/media/hankin/vdb/TransferStation/cp] #ll usb/
总用量 24
drwxr-xr-x 6 root root 4096 7月   7 17:47 ./
drwxr-xr-x 5 root root 4096 7月   7 17:46 ../
drwxr-xr-x 2 root root 4096 7月   7 11:25 a/
drwxr-xr-x 2 root root 4096 7月   7 11:25 b/
drwxr-xr-x 2 root root 4096 7月   7 11:25 c/
drwxr-xr-x 5 root root 4096 7月   7 11:25 lib/

usd文件夹不存在，安装上面的拷贝方式会报错
[root@ubuntu0006:/media/hankin/vdb/TransferStation/cp] #cp -arf lib/* usd
cp: 目标'usd' 不是目录
EOF

STEAMROOT="A"

#DEL_PATH="${STEAMROOT:?}/"*
#echo ${DEL_PATH}

DEL_PATH="${STEAMROOT:-tt}/"*
echo ${DEL_PATH}

echo "end"