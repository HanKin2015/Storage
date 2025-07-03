#!/bin/sh
#
# 文 件 名: set-e_hole.sh
# 文件描述: set -e命令埋坑
# 作    者: HanKin
# 创建日期: 2025.06.30
# 修改日期：2025.06.30
# 
# Copyright (c) 2025 HanKin. All rights reserved.
#

set -x

# 文件不存在
grep -q "hj" /home/hello
if [ $? -eq 0 ];then
    echo "file /home/hello has 'hj' string"
else
    echo "file /home/hello has no 'hj' string"
fi

set -e

# 文件存在，但是内容不存在
grep -q "hj" /var/log/update_install.log
if [ $? -eq 0 ];then
    echo "file /var/log/update_install.log has 'hj' string"
else
    echo "file /var/log/update_install.log has no 'hj' string"
fi

# 正确的方式
if grep -qE "jessie|stretch" /etc/os-release; then
    echo "os is jessie or stretch"
else
    echo "os is not jessie or stretch"
fi
