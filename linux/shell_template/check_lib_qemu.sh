#!/bin/bash

#参数判断
if [ $# -ne 1 ]
then
    echo "usage test_qemu.sh vmid"
    exit 1
fi

#虚拟机vmid参数
vmid=$1 

#获取进程pid
pid=`ps -ef| grep kvm| grep $vmid | grep -v grep | awk '{print $2}'`

#检查lib文件是否成功
#lib_is_sucess=`cat /proc/$pid/maps | grep libusbredirparser.so.1`
cat /proc/$pid/maps | grep libusbredirparser.so.1

#检查qemu文件是否替换成功
#qemu_is_sucess=`cat /proc/$pid/maps | grep qemu`
cat /proc/$pid/maps | grep qemu-system-x86_64  

#echo $lib_is_sucess
#echo $qemu_is_sucess

cat /proc/$pid/maps | grep libspice-server.so.1 
