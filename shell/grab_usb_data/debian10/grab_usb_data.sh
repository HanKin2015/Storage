#!/bin/bash
#
# 文 件 名: grab_usb_data.sh
# 文件描述: 抓取USB数据包
# 作    者: HanKin
# 创建日期: 2023.03.11
# 修改日期：2024.08.05
# 
# Copyright (c) 2024 HanKin. All rights reserved.
#

# 预防多开
filename=$(basename "$0")
truncated_filename="${filename:0:15}"
is_running_count=$(pgrep -c ${truncated_filename})
echo "${truncated_filename} is_running_count = ${is_running_count}"
if [ "$is_running_count" -gt 1 ] # 自身本来就会有一个进程
then
    echo "there are anathoer progress with running, will kill them"
    pgrep ${truncated_filename} | grep -v $$ | xargs kill -SIGKILL
fi

# USB数据存储路径
USB_DATA_FILE_PATH="/var/log/usb_data_file.txt"

# USB设备VPID
UDEV_LIST=("0c45:0415" "0ac8:3500" "0c15:6aab")
UDEV_COUNT=${#UDEV_LIST[@]}

# 找到当前使用的摄像头（有且只有一个）
i=0
while [ $i -lt $UDEV_COUNT ]
do
    UDEV=$(lsusb | grep ${UDEV_LIST[$i]})
    if [ -n "$UDEV" ];then
        UDEV_VID_PID=${UDEV_LIST[$i]}
        break
    fi
    i=$((i+1))
done

if ! [ -n "$UDEV_VID_PID" ];then
    echo "not found device" >> ${USB_DATA_FILE_PATH}
    echo "not found device and exit 1"
    exit 1
fi
echo ${UDEV_VID_PID} >> ${USB_DATA_FILE_PATH}

# 加载usbmon驱动
#insmod /system/lib/modules/usbmon.ko
modprobe usbmon

# 获取总线编号 /dev/bus/usb/002/006: 1bcf:2281 DHZJ-FAY-211204 BN100-WC (null)
bus_number=$(lsusb | grep ${UDEV_VID_PID} | awk '{print $2}')
echo ${bus_number}

# 去掉总线编号前缀0
bus_number_nozero=$(echo -e $bus_number | sed -r 's/0*([0-9])/\1/')
echo ${bus_number_nozero} >> ${USB_DATA_FILE_PATH}

# 获取端口编号
port_number=$(lsusb | grep ${UDEV_VID_PID} | awk '{print $4}')
echo ${port_number} >> ${USB_DATA_FILE_PATH}

# 记录当前开始的抓取时间，方便后面分析
echo "---- begin capture ----" >> ${USB_DATA_FILE_PATH}
date >> ${USB_DATA_FILE_PATH}

cmd="cat /sys/kernel/debug/usb/usbmon/${bus_number_nozero}u | grep '${bus_number_nozero}:${port_number}' --line-buffered >> ${USB_DATA_FILE_PATH}"
echo ${cmd}

# eval命令可以解析并执行存储在变量中的命令。在这种情况下，$cmd将被替换为你保存的命令，并被执行
eval ${cmd}

# 抓取USB数据包（解决打包脚本有部分抓包数据保留在缓冲区的问题）
cat /sys/kernel/debug/usb/usbmon/${bus_number_nozero}u | grep "${bus_number_nozero}:${port_number}" --line-buffered >> ${USB_DATA_FILE_PATH}