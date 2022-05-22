#!/bin/bash
#
# 文 件 名: calc_upan_rate.sh
# 文件描述: 计算U盘读写速率(只考虑一个U盘情况)
# 备    注: 虽然文件不同,但是dd命令基本上是写入速度高于读取速度,更换成cp命令后读不规则文件则正常
# 数    据: dd_write=6.13MB/s dd_read=4.16MB/s cp_write=3.32MB/s cp_read=5.74MB/s
# 作    者: HeJian
# 创建日期: 2021.09.14
# 修改日期：2021.09.14
# 
# Copyright (c) 2021 HeJian. All rights reserved.
#

# 获取U盘默认挂载路径
upan_mount_path=`mount | grep udisk | awk '{print $3}'`
echo ${upan_mount_path}

# 获取U盘文件系统设备
upan_file_sys_udev=`mount | grep udisk | awk '{print $1}'`
echo ${upan_file_sys_udev}

# 获取U盘的PVID
pvid=`lsusb -v | grep -B 40 'Mass Storage' | grep 'Bus 0' | awk '{print $6}'`
echo ${pvid}

# 获取U盘自身协议
bcdusb=`lsusb -d ${pvid} -v | grep bcdUSB | awk 'NR==1{print $2}'`
echo ${bcdusb}

# 重复操作次数
retry_cnt=3
cnt=0

# 写入128M数据
file_size=379

while [ ${cnt} -lt ${retry_cnt} ]
do
    ((cnt++))
    #dd if=/dev/zero of=${upan_mount_path}/calc_upan_write_rate bs=128M count=1 oflag=sync

    begin_time=`date +%s`
    cp /home/test.zip ${upan_mount_path}/
    end_time=`date +%s`
    echo ${end_time} ${begin_time}
    echo "scale=2; ${file_size} / (${end_time} - ${begin_time})" | bc

    umount ${upan_mount_path}
    if [ ! -d ${upan_mount_path} ]
    then
        mkdir -p ${upan_mount_path}
    fi
    mount ${upan_file_sys_udev} ${upan_mount_path}
done

# 读取128M数据
for i in $(seq 1 3)
do
    #echo ${i}
    #dd if=${upan_mount_path}/calc_upan_write_rate of=/home/calc_upan_read_rate bs=128M count=1 oflag=sync

    begin_time=`date +%s`
    cp ${upan_mount_path}/test.zip /home/
    end_time=`date +%s`
    echo ${end_time} ${begin_time}
    echo "scale=2; ${file_size} / (${end_time} - ${begin_time})" | bc

    umount ${upan_mount_path}
    if [ ! -d ${upan_mount_path} ]
    then
        mkdir -p ${upan_mount_path}
    fi
    mount ${upan_file_sys_udev} ${upan_mount_path}
done

# 删除创建的文件夹
umount ${upan_mount_path}
if [ -d ${upan_mount_path} ]
then
    rm -rf ${upan_mount_path}
fi








