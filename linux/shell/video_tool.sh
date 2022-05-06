#!/bin/bash
#
# 文 件 名: video_tool.sh
# 文件描述: 操作摄像头工具合集
# 作    者: HanKin
# 创建日期: 2021.08.05
# 修改日期：2021.08.05
# 
# Copyright (c) 2021 HanKin. All rights reserved.
#

# 1.全局变量
shell_name=$0
shell_version='1.0'
create_date='2021-08-05'


# 2.版本信息
function VersionInfo()
{
    echo "version: ${shell_version} (last modified at ${create_date})"
}

# 3.用法
function Usage()
{
    cat<<EOF
Usage: ${shell_name} [options]

Version ${shell_version}
Options:
-d | --device name   Video device name
-h | --help          Print this message
-m | --mmap          Use memory mapped buffers [default]
-r | --read          Use read() calls
-u | --userp         Use application allocated buffers
-o | --output        Outputs stream to stdout
-f | --format        Force format to 640x480 YUYV
-c | --count         Number of frames to grab [%i]
EOF
}

# 4.参数解析
# 5.参数实现方法

# 解析用户传递的参数
while getopts "hVafN" arg
do
    case $arg in
        h)
            Usage
            exit 0
            ;;
        V)
            VersionInfo
            exit 0
            ;;
        a)
            # 通过v4l2查看摄像头设备
            v4l2-ctl --list-devices
            ;;
        f)
            # 查看/dev/video0中所有格式及分辨率
            v4l2-ctl -d0 --list-formats-ext
            ;;
        N)
            echo "nothing to do, ignor it"
            ;;
        ?)  #当有不认识的选项的时候arg为?
            echo "unkonw argument"
            Usage
            exit 1
            ;;
    esac
done







































