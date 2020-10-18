#!/bin/bash

# 变量定义
path=`pwd`
echo $path

# 用法说明
usage()
{
	cat << EOT
		Usage: $0 [options] [directroy]
		Options:
			-i	install
			-u	update
			-h	help(usage) and exit
		Examples:
			$0 -i dir
	EOT
}
