#!/bin/bash
#
# 文 件 名: calc_upan_read_write_speed_v2.sh
# 文件描述: 计算U盘读写速率(只考虑一个U盘情况)
# 数    据: 基于去年的calc_upan_read_write_speed.sh文件进行修改升级使用
# 作    者: HanKin
# 创建日期: 2022.10.11
# 修改日期：2022.10.11
# 
# Copyright (c) 2022 HanKin. All rights reserved.
#

# 获取U盘默认挂载路径
upan_mount_path=`mount | grep udisk | awk '{print $3}'`
echo "U盘挂载目录: ${upan_mount_path}"

# 获取U盘文件系统设备
upan_file_sys_udev=`mount | grep udisk | awk '{print $1}'`
echo "U盘的文件系统: ${upan_file_sys_udev}"

# 获取U盘的PVID
#cat /sys/kernel/debug/usb/devices | grep -B 5 'usb-storage' | grep Vendor | awk '{print $2,$3}'
vpid=`lsusb -v | grep -B 40 'Mass Storage' | grep 'Bus 0' | awk '{print $6}'`
echo "U盘的vpid: ${vpid}"

# 获取U盘自身协议
bcdusb=`lsusb -d ${vpid} -v | grep bcdUSB | awk 'NR==1{print $2}'`
echo "U盘的USB协议: ${bcdusb}"

# 重复操作次数
retry_cnt=3

# 测试次数
test_cnt=0

# 测试的文件路径
file_name="outlook2016.exe"
file_path="/home/${file_name}"
echo "文件路径: ${file_path}"

# 测试文件大小
file_size=`ls -l ${file_path} | awk '{print $5}'`
file_size=`echo "scale=2; ${file_size} / 1024 / 1024" | bc`
echo "文件大小: ${file_size} MB"

echo ""
echo "开始进行写入文件:"
while [ ${test_cnt} -lt ${retry_cnt} ]
do
    ((test_cnt++))
    begin_time=`date +%s`
    cp ${file_path} ${upan_mount_path}/
    end_time=`date +%s`
    copy_speed=`echo "scale=2; ${file_size} / (${end_time} - ${begin_time})" | bc`
    echo "开始时间: ${begin_time}"
    echo "结束时间: ${end_time}"
    echo "拷贝速度: ${copy_speed} MB/s"

    sleep 2
    umount ${upan_mount_path}
    if [ ! -d ${upan_mount_path} ]
    then
        mkdir -p ${upan_mount_path}
    fi
    mount ${upan_file_sys_udev} ${upan_mount_path}
    echo ""
done

echo ""
echo "开始进行读取文件:"
while [ ${test_cnt} -ge 0 ]
do
    ((test_cnt--))
    begin_time=`date +%s`
    cp ${upan_mount_path}/${file_name} /home/
    end_time=`date +%s`
    copy_speed=`echo "scale=2; ${file_size} / (${end_time} - ${begin_time})" | bc`
    echo "开始时间: ${begin_time}"
    echo "结束时间: ${end_time}"
    echo "拷贝速度: ${copy_speed} MB/s"

    sleep 2
    umount ${upan_mount_path}
    if [ ! -d ${upan_mount_path} ]
    then
        mkdir -p ${upan_mount_path}
    fi
    mount ${upan_file_sys_udev} ${upan_mount_path}
    echo ""
done

# 删除创建的文件夹
umount ${upan_mount_path}
if [ -d ${upan_mount_path} ]
then
    rm -rf ${upan_mount_path}
fi
