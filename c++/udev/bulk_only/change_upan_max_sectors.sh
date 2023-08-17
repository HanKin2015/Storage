#!/bin/bash
#
# 文 件 名: change_upan_max_sectors.sh
# 文件描述: U盘插入后修改块大小
# 作    者: HanKin
# 创建日期: 2022.11.16
# 修改日期：2022.11.16
# 
# Copyright (c) 2022 HanKin. All rights reserved.
#

while true
do
    #ret=`udevadm monitor | grep -q scsi_device`
    echo 2048 > /sys/devices/pci0000:00/0000:00:02.0/0000:01:18.7/usb2/2-13/2-13:1.0/host0/target0:0:0/0:0:0:0/max_sectors
    if [ $? == 0 ]
    then
        echo 'success'
        break
    fi
done

#/devices/pci0000:00/0000:00:02.0/0000:01:18.7/usb2/2-13/2-13:1.0/host0/target0:0:0/0:0:0:0/scsi_device/0:0:0:0 (scsi_device)

#/devices/pci0000:00/0000:00:02.0/0000:01:18.7/usb2/2-13/2-13:1.0/host0/target0:0:0/0:0:0:0/block/sda/sda4


#/sys/devices/pci0000:00/0000:00:02.0/0000:01:18.7/usb2/2-13/2-13:1.0/host0/target0:0:0/0:0:0:0/max_sectors

