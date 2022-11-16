#!/bin/bash

if [ -f "libusbredirparser.so.1.0.0" ]; then
     mv libusbredirparser.so.1.0.0 libusbredirparser.so.1
fi

if [ -f "libspice-server.so.1.9.0" ]; then
     mv libspice-server.so.1.9.0 libspice-server.so.1
fi
#参数判断
if [ $# -ne 1 ]
then
    echo "usage test_qemu.sh vmid"
    exit 1
fi

#虚拟机vmid参数
vmid=$1 

#替换lib文件
#:<<'
#newPath=$(pwd)
#LD_LIBRARY_PATH=${newPath}:${LD_LIBRARY_PATH}
#echo $LD_LIBRARY_PATH
#'

#export LD_PRELOAD="./libusbredirparser.so.1" 
#export LD_PRELOAD="./libspice-server.so.1"

#替换qemu文件
qm stop $vmid

chmod a+x qemu-system-x86_64
ln -sf /sf/data/local/hj/qemu-system-x86_64 /sf/bin/kvm

#获取虚拟机开机命令
cmd=$(qm showcmd $vmid) 
$cmd

#恢复其他虚拟机qemu文件位置
ln -sf /sf/bin/qemu-system-x86_64 /sf/bin/kvm
