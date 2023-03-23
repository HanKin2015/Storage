#!/vendor/bin/sh
#
# 文 件 名: limit_file_size.sh
# 文件描述: 限制文件大小，备份一个100MB大小的文件，如果当前文件超过100MB则删除备份
# 作    者: HanKin
# 创建日期: 2023.01.07
# 修改日期：2023.01.07
# 
# Copyright (c) 2023 HanKin. All rights reserved.
#

# 可能是busybox的问题
alias busybox='/system/bin/busybox'
alias awk='busybox awk'

USB_DATA_FILE_BAK_PATH="/sdcard/usb_data_file.bak"
USB_DATA_FILE_PATH="/sdcard/usb_data_file.txt"
LIMIT_FILE_SIZE_LOG_PATH="/sdcard/log.txt"
MAX_FILE_SIZE=$((100*1024))

# 启动抓取USB数据包脚本
chmod +x /vendor/bin/grab_usb_data.sh
/vendor/bin/grab_usb_data.sh &

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
    
    # 睡眠5秒
    sleep 5
done