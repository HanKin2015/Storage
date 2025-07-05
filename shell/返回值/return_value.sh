#!/bin/sh
#
# 文 件 名: return_value.sh
# 文件描述: 返回值探究
# 备    注: 
# 作    者: HanKin
# 创建日期: 2025.06.30
# 修改日期：2025.06.30
# 
# Copyright (c) 2025 HanKin. All rights reserved.
#

set -x

# 文件不存在（$?输出为1）
grep -q "hj" /home/hello
if [ $? -eq 0 ];then
    echo "file /home/hello has 'hj' string"
else
    echo "file /home/hello has no 'hj' string"
fi

# 文件存在，但是内容不存在（$?输出为1）
grep -q "hj" /var/log/update_install.log
if [ $? -eq 0 ];then
    echo "file /var/log/update_install.log has 'hj' string"
else
    echo "file /var/log/update_install.log has no 'hj' string"
fi

# 正确的方式（$?输出为1，但是打印了os is not jessie or stretch）
if grep -qE "jessie|stretch" /etc/os-release; then
    echo "os is jessie or stretch"
else
    echo "os is not jessie or stretch"
fi

# $?输出为1后执行后面的语句
grep -qE "jessie|stretch" /etc/os-release || {
    echo "os is not jessie or stretch"
}

# $?输出为0后不执行后面的语句
grep -qE "jessie|stretch|debian" /etc/os-release || {
    echo "os is not jessie or stretchssssssss"
}