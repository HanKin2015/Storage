#!/bin/bash

# 获取U盘默认挂载路径
upan_mount_path=`mount | grep udisk | awk '{print $3}'`
echo ${upan_mount_path}

# 获取U盘用户设置的名字
#upan_name_index=`awk -v arg=${upan_mount_path} 'BEGIN{match(arg, /.*\//);print RLENGTH;}'`
#upan_name=${upan_mount_path:${upan_name_index}}
#echo ${upan_name_index} ${upan_name}
upan_name=${upan_mount_path##*/}
echo ${upan_name}

vid=`cat /sys/kernel/debug/usb/devices | grep -B 7 'usb-storage' | grep Vendor | awk -F '=| ' '{print $4}'`
pid=`cat /sys/kernel/debug/usb/devices | grep -B 7 'usb-storage' | grep Vendor | awk -F '=| ' '{print $6}'`
echo ${vid}:${pid}

pvid=`lsusb -v | grep -B 40 'Mass Storage' | grep 'Bus 0' | awk '{print $6}'`
bcdusb=`lsusb -d ${pvid} -v | grep bcdUSB | awk 'NR==1{print $2}'`
echo ${pvid} ${bcdusb}

dd if=/dev/zero of=${upan_mount_path}/calc_upan_write_rate bs=128M count=1 oflag=sync

dd of=/home/hankin/calc_upan_read_rate if=${upan_mount_path}/calc_upan_write_rate bs=128M count=1 oflag=sync