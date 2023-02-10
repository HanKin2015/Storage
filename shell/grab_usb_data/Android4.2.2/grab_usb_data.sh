#!/system/bin/sh
#
# 文 件 名: grab_usb_data.sh
# 文件描述: 抓取USB数据包
# 作    者: HanKin
# 创建日期: 2023.01.07
# 修改日期：2023.02.09
# 
# Copyright (c) 2023 HanKin. All rights reserved.
#

alias busybox='/sbin/busybox'
alias awk='busybox awk'
alias sed='busybox sed'

# USB数据存储路径
USB_DATA_FILE_PATH="/sdcard/usb_data_file.txt"

# USB设备VPID
UDEV_VID_PID="1bcf:2281"

# 加载usbmon驱动
insmod /system/lib/modules/usbmon.ko

# 获取总线编号 /dev/bus/usb/002/006: 1bcf:2281 DHZJ-FAY-211204 BN100-WC (null)
bus_number=$(lsusb | grep ${UDEV_VID_PID} | awk '{print $1}' | awk -F'/' '{print $5}')

# 去掉总线编号前缀0
bus_number_nozero=$(echo -e $bus_number | sed -r 's/0*([0-9])/\1/')
#echo ${bus_number_nozero}

# 获取端口编号
port_number=$(lsusb | grep ${UDEV_VID_PID} | awk '{print $1}' | awk -F'/' '{print $6}')
#echo ${port_number}

# 记录当前开始的抓取时间，方便后面分析
date >> ${USB_DATA_FILE_PATH}

# 抓取USB数据包
cat /sys/kernel/debug/usb/usbmon/${bus_number_nozero}u | grep ${port_number} >> ${USB_DATA_FILE_PATH}