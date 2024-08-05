#!/bin/bash
#
# 文 件 名: limit_file_size.sh
# 文件描述: 限制文件大小，备份一个50MB大小的文件，如果当前文件超过50MB则删除备份
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

USB_DATA_FILE_BAK_PATH="/var/log/usb_data_file.bak"
USB_DATA_FILE_PATH="/var/log/usb_data_file.txt"
MAX_FILE_SIZE=$((50*1024))

sleep 20

# 启动抓取USB数据包脚本
echo "start grab_usb_data.sh"
chmod +x /usr/local/bin/grab_usb_data.sh
/usr/local/bin/grab_usb_data.sh &

i=0
count=24
while true
do
    # 判断文件大小是否超过100M
    current_size=$(du -s ${USB_DATA_FILE_PATH} | awk '{print $1}')
    #echo ${current_size} ${MAX_FILE_SIZE}

    if [ ${current_size} -gt ${MAX_FILE_SIZE} ]; then
        # 删除备份文件
        if [ -f ${USB_DATA_FILE_BAK_PATH} ]; then
            rm -f ${USB_DATA_FILE_BAK_PATH}
        fi
        
        # 将当前文件转换为备份文件
        cp -f ${USB_DATA_FILE_PATH} ${USB_DATA_FILE_BAK_PATH}
        
        # 清空文件内容
        >  ${USB_DATA_FILE_PATH}
        
        # 重新启动抓取USB数据包脚本
        #kill -9 $(pidof grab_usb_data.sh)
        #./grab_usb_data.sh &
    fi
    
    if [ -f ${USB_DATA_FILE_PATH} ];then
        if [ $i -lt $count ];then
            i=$((i+1))
        else
            echo -e "\ntime $(date "+%G-%m-%d %H:%M:%S")" >> ${USB_DATA_FILE_PATH}
            i=0
        fi
    fi
    
    # 睡眠5秒
    sleep 5
done