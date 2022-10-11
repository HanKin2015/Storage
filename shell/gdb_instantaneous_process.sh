#!/bin/bash
#
# 文 件 名: gdb_instantaneous_process.sh
# 文件描述: gdb调试瞬间一闪而过的进程
# 作    者: HanKin
# 创建日期: 2022.10.11
# 修改日期：2022.10.11
# 
# Copyright (c) 2022 HanKin. All rights reserved.
#

while true
do
    pid=`pidof vdi_session`
    if [ -n "${pid}" ]
    then
        echo ${pid}
        gdb /usr/local/hankin/vdiclient/bin/vdi_session -p ${pid}
        break
    else
        echo 'there is not a excepted process'
    fi
done
