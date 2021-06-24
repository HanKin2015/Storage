#!/bin/bash
#
# 替换测试lib和qemu文件
#
# 用法: ./replace_lib_qemu.sh vmid
#
# 使用前注意: 
#   1. 需要安装expect, apt install expect
#   2. 放置在/sf/data/local/hj/目录下
#
# Author: hejian
# Date  : 2021.04.07
#
# Update: 2021.05.31
#   1.增加aarch64判断，支持国产化服务器
#   2.增加查询虚拟机vmid
#
# Copyright (c) 2021 HanKin. All rights reserved.
#

alias cq='cd /usr/share/perl5/VTP/'
alias vq='vim /usr/share/perl5/VTP/QemuServer.pm'
alias ch='cd /sf/data/local/hj/'
alias cl='cd /sf/log/today/'
