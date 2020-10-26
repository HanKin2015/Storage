#!/bin/bash

# 变量定义
path=`pwd`
echo "path=${path}"

# 版本信息
version()
{
	echo "version: 1.0"
}

# 用法说明
usage()
{
	cat << EOF
Usage: $0 [options] [directroy]
Options:
	-h, 	显示帮助信息
	-V,	显示当前脚本版本信息
	-f file,	从文件读取ip地址
Examples:
	$0 -f ip_addr.txt
EOF
}

cat ip_addr.txt | while read ip_addr
do
    echo $ip_addr
	loss_packets=`ping -c 1 $ip_addr | grep '0 received' | wc -l`
	echo $loss_packets
	if loss_packets == 0;then
		echo "ping $ip_addr is fail" >> result.txt
	else
		echo "ping $ip_addr is success" >> result.txt
	fi
done








