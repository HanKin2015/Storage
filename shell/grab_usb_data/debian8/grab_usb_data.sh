#!/bin/bash
#
# 文 件 名: grab_usb_data.sh
# 文件描述: 抓取USB数据包
# 作    者: HanKin
# 创建日期: 2023.03.11
# 修改日期：2023.03.11
# 
# Copyright (c) 2023 HanKin. All rights reserved.
#

# USB数据存储路径
USB_DATA_FILE_PATH="/other/usb_data_file.txt"

# USB设备VPID
UDEV_VID_PID="093a:2510"
UDEV_VID_PID="163c:0a2b"

# 加载usbmon驱动
#insmod /system/lib/modules/usbmon.ko
modprobe usbmon

# 获取总线编号
bus_number=$(lsusb | grep ${UDEV_VID_PID} | awk '{print $2}')
echo ${bus_number}

# 去掉总线编号前缀0
bus_number_nozero=$(echo -e $bus_number | sed -r 's/0*([0-9])/\1/')
echo ${bus_number_nozero}

# 获取端口编号
port_number=$(lsusb | grep ${UDEV_VID_PID} | awk '{print $4}')
echo ${port_number}

# 记录当前开始的抓取时间，方便后面分析
date >> ${USB_DATA_FILE_PATH}

cmd='cat /sys/kernel/debug/usb/usbmon/${bus_number_nozero}u | grep "${bus_number_nozero}:${port_number}" >> ${USB_DATA_FILE_PATH}'
echo ${cmd}

# 抓取USB数据包
cat /sys/kernel/debug/usb/usbmon/${bus_number_nozero}u | grep "${bus_number_nozero}:${port_number}" >> ${USB_DATA_FILE_PATH}