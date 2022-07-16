#!/bin/bash
#
# 功能：管理日志文件大小
# 时间: 2021/3/10
#

folder_path="/var/log/usb_record_info/"
cd $folder_path

# 自UTC时间，当前所经过的秒数
curren_date_second=$(date -d `date +%Y%m%d` +%s)

# 压缩文件夹
folders_name=`ls -l $folder_path | awk '/^d/ {print $NF}'`
for folder_name in $folders_name
do
    # 将文件夹日期转换为秒数
    date_second=$(date -d $folder_name +%s)
    if [ $date_second -lt $curren_date_second ]
    then
        tar -zcf ${folder_name}.tar.gz $folder_name --remove-files
    fi
done

# 判断文件夹大小是否超过200M
current_size=`du -s $folder_path | awk '{print $1}'`
max_size=$((200*1024))
while [ $current_size -gt $max_size ]
do
    oldest_file_name=`ls -lrt | awk 'NR==2' | awk '{print $NF}'`
    rm -rf $oldest_file_name
    current_size=`du -s $folder_path | awk '{print $1}'`
done